/*
 * Trabalho 4 de Computação Gráfica
 * Autor: Leandro de Rezende Alves
 * Para instruções leia o readme.txt
*/

#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLsizei screen_width = 800, screen_height = 800;
GLuint textures[3];
char* metal = "./metal.bmp";
char* metal2 = "./metal2.bmp";
int rotShoulder_x, rotShoulder_z = 90.f, rotElbow = -60.f, rotHand_x, rotHand_z = -30.f, rotTweezer = 30.f;
float pan_x = 0.f, pan_y = 0.f;
float zoom = 1.f;
float scale = 1.2;
float step = 1.f;
GLUquadric* quad;
float camera_x = 0.f, camera_y = 0.f, camera_z = 0.f;
float lookAt_x = 0.f, lookAt_y = 0.f, lookAt_z = 0.f;
float theta = 0.f, phi = 0.f, radius = 1.f;
int old_x, old_y;
bool can_rotate = false;

void init(void);

void pan(float dx, float dy);

void zoomCam(float factor);

void updateCam(void);

void keyboard (unsigned char key, int x, int y);

void special(int key, int x, int y);

void mouse(int button, int state, int x, int y);

void mouseMotion(int x, int y);

void initLighting(void);

void error(char* msg);

void loadTexture(GLuint texture, const char *filename);

void setup(void);

void drawCube(float size);

void display(void);

void reshape (GLsizei w, GLsizei h);

void init(void)
{
	glGenTextures(2, textures);

	loadTexture(textures[0], metal2);
	loadTexture(textures[1], metal);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glShadeModel(GL_FLAT);
}

void pan(float dx, float dy)
{
	pan_x += dx / zoom;
	pan_y += dy / zoom;
}

void zoomCam(float factor)
{
	zoom *= factor;
}

void updateCam(void)
{
	camera_x = lookAt_x + radius * cos(phi) * sin(theta);
	camera_y = lookAt_y + radius * sin(phi) * sin(theta);
	camera_z = lookAt_z + radius * cos(theta);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	  case 27:
		exit(0);
	  case 'a':
		rotShoulder_z = (rotShoulder_z + 5) % 360;
		if (rotShoulder_z > 135) rotShoulder_z = 135;
		glutPostRedisplay();
		break;
	  case 'A':
		rotShoulder_z = (rotShoulder_z - 5) % 360;
		if (rotShoulder_z < 45) rotShoulder_z = 45;
		glutPostRedisplay();
		break;
	  case 'q':
		rotShoulder_x = (rotShoulder_x + 5) % 360;
		glutPostRedisplay();
		break;
	  case 'Q':
		rotShoulder_x = (rotShoulder_x - 5) % 360;
		glutPostRedisplay();
		break;
	  case 's':
		rotElbow = (rotElbow + 5) % 360;
		if (rotElbow > 45) rotElbow = 45;
		glutPostRedisplay();
		break;
	  case 'S':
		rotElbow = (rotElbow - 5) % 360;
		if (rotElbow < -135) rotElbow = -135;
		glutPostRedisplay();
		break;
	  case 'd':
		rotHand_z = (rotHand_z + 5) % 360;
		if (rotHand_z > 60) rotHand_z = 60;
		glutPostRedisplay();
		break;
	  case 'D':
		rotHand_z = (rotHand_z - 5) % 360;
		if (rotHand_z < -60) rotHand_z = -60;
		glutPostRedisplay();
		break;
	  case 'e':
		rotHand_x = (rotHand_x + 5) % 360;
		glutPostRedisplay();
		break;
	  case 'E':
		rotHand_x = (rotHand_x - 5) % 360;
		glutPostRedisplay();
		break;
	  case 'f':
		rotTweezer = (rotTweezer + 5) % 360;
		if (rotTweezer > 60) rotTweezer = 60;
		glutPostRedisplay();
		break;
	  case 'F':
		rotTweezer = (rotTweezer - 5) % 360;
		if (rotTweezer < -5) rotTweezer = -5;
		glutPostRedisplay();
		break;
	  default:
	  	break;
	}
}

void special(int key, int x, int y)
{
	switch (key)
	{
	  case GLUT_KEY_LEFT:
		pan(-step, 0.f);
	  	glutPostRedisplay();
	  	break;
	  case GLUT_KEY_RIGHT:
	    pan(step, 0.f);
	    glutPostRedisplay();
	    break;
	  case GLUT_KEY_DOWN:
	    pan(0.f, -step);
	    glutPostRedisplay();
	    break;
	  case GLUT_KEY_UP:
	    pan(0.f, step);
	    glutPostRedisplay();
	    break;
	  default:
	  	break;
	}
}

void mouse(int button, int state, int x, int y)
{
	can_rotate = false;
	if (state != GLUT_DOWN)
		return;

	if (button == GLUT_LEFT_BUTTON)
		zoomCam(scale);
	else if (button == GLUT_RIGHT_BUTTON)
		zoomCam(1/scale);
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		old_x = x;
		old_y = y;
		can_rotate = true;
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	if (can_rotate)
	{
		theta += (x - old_x) * 0.01f;
		phi += (y - old_y) * 0.01f;
	}
	old_x = x;
	old_y = y;
	glutPostRedisplay();
}

void initLighting(void)
{
	GLfloat lightposition[] = { -3.f, 5.f, -5.f, 0.f };
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.f, 0.f, 0.f, 0.f);
}

void error(char* msg)
{
	std::cerr << msg << std::endl;
	exit(1);
}

void loadTexture(GLuint texture, const char *filename)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file = fopen(filename, "rb");
	if (!file)
		error("Image could not be opened.");		
	if (fread(header, 1, 54, file) != 54)
		error("Not a correct BMP file.");
	if (header[0] != 'B' || header[1] != 'M')
		error("Not a correct BMP file");

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char [imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void setup(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(zoom, zoom, 1.f);
	glTranslatef (pan_x, pan_y, -5.f);
}

void drawCube(float size)
{
	glColor4f(1.f, 1.f, 1.f, 0.f);

	glBegin(GL_QUADS); //Posterior
	glNormal3f(0.f, 0.f, 1.f);
	glTexCoord2f(0.f, 0.f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); //Frontal
	glNormal3f(0.f, 0.f, -1.f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS); //Lateral esquerda
	glNormal3f(-1.f, 0.f, 0.f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); //Lateral direita
	glNormal3f(1.f, 0.f, 0.f);
	glTexCoord2f(1.f, 0.f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 0.f); glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS); //Superior
	glNormal3f(0.f, 1.f, 0.f);
	glTexCoord2f(0.f, 1.f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.f, 1.f); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS); //Inferior
	glNormal3f(0.f, -1.f, 0.f);
	glTexCoord2f(1.f, 1.f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.f, 1.f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.f, 0.f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.f, 0.f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setup();
	updateCam();
	gluLookAt(camera_x, camera_y, camera_z, lookAt_x, lookAt_y, lookAt_z, 0, 1, 0);

	//Support
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTranslatef(0.f, -2.f, 0.f);
	glPushMatrix();
	glScalef(4.f, 0.4f, 5.f);
	drawCube(1.f);
	glPopMatrix();

	//Arm
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTranslatef(-1.f, 0.2f, 0.f);
	glNormal3f(0.f, 1.f, 0.f);
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 0.2f, 8, 8);
	glRotatef((GLfloat) rotShoulder_z, 0.f, 0.f, 1.f);
	glRotatef((GLfloat) rotShoulder_x, 1.f, 0.f, 0.f);
	glTranslatef(1.f, 0.f, 0.f);
	glPushMatrix();
	glScalef(2.f, 0.4f, 0.5f);
	drawCube(1.f);
	glPopMatrix();

	//Forearm
	glTranslatef(1.f, 0.f, 0.f);
	glNormal3f(0.f, 1.f, 0.f);
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 0.2f, 8, 8);
	glRotatef((GLfloat) rotElbow, 0.f, 0.f, 1.f);
	glTranslatef(1.f, 0.f, 0.f);
	glPushMatrix();
	glScalef(2.f, 0.4f, 0.5f);
	drawCube(1.f);
	glPopMatrix();

	//Hand
	glTranslatef(1.f, 0.f, 0.f);
	glNormal3f(0.f, 1.f, 0.f);
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 0.2f, 8, 8);
	glRotatef((GLfloat) rotHand_z, 0.f, 0.f, 1.f);
	glRotatef((GLfloat) rotHand_x, 1.f, 0.f, 0.f);
	glTranslatef(0.5f, 0.f, 0.f);
	glPushMatrix();
	glScalef(1.f, 0.4f, 0.5f);
	drawCube(1.f);
	glPopMatrix();
	
	//Tweezer
	glTranslatef(0.4f, 0.1f, 0.f);
	glPushMatrix();
	glRotatef((GLfloat) rotTweezer, 0.f, 0.f, 1.f);
	glTranslatef(0.3f, 0.f, 0.f);
	glPushMatrix();
	glScalef(0.6f, 0.1f, 0.2f);
	drawCube(1.f);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(0.0f, -0.2f, 0.f);
	glRotatef((GLfloat) -rotTweezer, 0.f, 0.f, 1.f);
	glTranslatef(0.3f, 0.f, 0.f);
	glPushMatrix();
	glScalef(0.6f, 0.1f, 0.2f);
	drawCube(1.f);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
	glutSwapBuffers();
}

void reshape (GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	screen_width = w;
	screen_height = h;

	glViewport (0, 0, w, h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.f, (GLfloat) w/(GLfloat) h, 1.f, 20.f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_width, screen_height); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	initLighting();
	init();
	glEnable(GL_TEXTURE_2D);
	quad = gluNewQuadric();

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);

	glutMainLoop();

	return 0;
}