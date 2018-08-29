function dest = multiScaleSharpen( src, Radius)
%%�����˹�������˲������Ч������������ͼҲ��һ��  ԭ��https://www.cnblogs.com/ImageVision/archive/2012/08/15/2640679.html


H1 = fspecial('gaussian', [5,5], 2);      %5*5�ĸ�˹�˲�ģ��


% figure;imshow(B3), title('B3');
 
D1=src-B1;
D2=B1-B2;
D3=B2-B3;
%%
w1=0.5;
w2=0.5;
w3=0.25;
dest=(1-w1.*sign(D1)).*D1+w2*D2+w3*D3+src;
% figure;imshow(dest), title('dest');
end