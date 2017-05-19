pkg load image

lion = imread("lion.png");
woman = imread("woman.png");

f = [1/9 1/3 1/6 ; 1/4 1/2 1/8 ; 1/7 1/5 1/7];

lion_fil = imfilter(lion, f);
lion_comb = [lion lion_fil];
imwrite(lion_comb, "lion_comb_custom.png");

woman_fil = imfilter(woman, f);
woman_comb = [woman woman_fil];
imwrite(woman_comb, "woman_comb_custom.png");