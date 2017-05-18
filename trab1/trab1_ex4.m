pkg load image

lion = imread("lion.png");
woman = imread("woman.png");

avg = fspecial("average");
gauss = fspecial("gaussian");
lap = fspecial("laplacian");
sobel = fspecial("sobel");

lion_avg = imfilter(lion, avg);
lion_gauss = imfilter(lion, gauss);
lion_lap = imfilter(lion, lap);
lion_sobel = imfilter(lion, sobel);

woman_avg = imfilter(woman, avg);
woman_gauss = imfilter(woman, gauss);
woman_lap = imfilter(woman, lap);
woman_sobel = imfilter(woman, sobel);

lion_comb_avg = [lion lion_avg];
imwrite(lion_comb_avg, "lion_comb_avg.png");
lion_comb_gauss = [lion lion_gauss];
imwrite(lion_comb_gauss, "lion_comb_gauss.png");
lion_comb_lap = [lion lion_lap];
imwrite(lion_comb_lap, "lion_comb_lap.png");
lion_comb_sobel = [lion lion_sobel];
imwrite(lion_comb_sobel, "lion_comb_sobel.png");

woman_comb_avg = [woman woman_avg];
imwrite(woman_comb_avg, "woman_comb_avg.png");
woman_comb_gauss = [woman woman_gauss];
imwrite(woman_comb_gauss, "woman_comb_gauss.png");
woman_comb_lap = [woman woman_lap];
imwrite(woman_comb_lap, "woman_comb_lap.png");
woman_comb_sobel = [woman woman_sobel];
imwrite(woman_comb_sobel, "woman_comb_sobel.png");