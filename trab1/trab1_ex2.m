pkg load image

leme = imread("leme.bmp");

# Gamma 0.6 
leme_gamma = imadjust(leme, [0;1], [0;1], 0.6);
leme_comb = [leme leme_gamma];
imwrite(leme_comb, "leme_comb.png");

# Gamma 0.7 
leme_gamma2 = imadjust(leme, [0;1], [0;1], 0.7);
leme_comb2 = [leme leme_gamma2];
imwrite(leme_comb2, "leme_comb2.png");