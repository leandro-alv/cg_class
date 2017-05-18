pkg load image

coin = imread("Coins.png");

coin_lim = coin;

for i = 1:rows(coin)
  for j = 1:columns(coin)
    if (coin(i,j) < 128)
      coin_lim(i,j) = 128
    else
      coin_lim(i,j) = coin(i,j)  
    endif
  endfor
endfor

subplot(1,2,1), imshow(coin), subplot(1,2,2), imshow(coin_lim);