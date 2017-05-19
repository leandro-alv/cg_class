pkg load image

coin = imread("Coins.png");

imhist(coin);

lim = 90;

mask = (coin > lim);

coin_lim = (coin.* mask);

coin_comb = [coin coin_lim];
imwrite(coin_comb, "coin_comb_lim.png");