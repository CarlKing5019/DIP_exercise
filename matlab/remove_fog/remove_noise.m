img=imread('1_noise.bmp');
img=double(img);
img_m=adp_median(img,7);    %��ֵ�˲���ȥ����������


H=fspecial('gaussian',3);
img_a=imfilter(img_m,H);       %3*3�ľ�ֵ�˲�


subplot(2,2,1);
imshow(img,[]);

subplot(2,2,2);
imshow(img_m,[]);

subplot(2,2,3);
imshow(img_a,[]);

subplot(2,2,4);
