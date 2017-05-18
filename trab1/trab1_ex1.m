pkg load image

ein_low_con = imread("Einstein_low_contrast.png");
ein_med_con = imread("Einstein_med_contrast.png");
ein_high_con = imread("Einstein_high_contrast.png");



subplot(1,2,1), imshow(ein_low_con), subplot(1,2,2), imhist(ein_low_con);
subplot(1,2,1), imshow(ein_med_con), subplot(1,2,2), imhist(ein_med_con);
subplot(1,2,1), imshow(ein_high_con), subplot(1,2,2), imhist(ein_high_con);

ein_low_con_adj = imadjust(ein_low_con, [0.3; 0.7], [0; 1]);
subplot(1,2,1), imshow(ein_low_con_adj), subplot(1,2,2), imhist(ein_low_con_adj);
