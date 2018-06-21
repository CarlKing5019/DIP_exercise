%% remove fog test code
% zhxing 2018/6/21


%%
img=imread('test.jpg');
figure,
imshow(img),title('ԭͼ');

dc=dark_channel(img);          %��ȡ��ͨ��ͼ��
A=getA(img);                   %��ȡ������ֵ

tx=imguidedfilter(dc,img,'NeighborhoodSize',[70,70]);        %�����˲����͸����ͼ

img=double(img);

Ix1=img(:,:,1);             %ͨ������
Ix2=img(:,:,2);
Ix3=img(:,:,3);

Jx1_=Ix1-A(1)+A(1)*tx;
Jx1=Jx1_./tx;
figure,imshow(Jx1,[]),title('JX1');

Jx2_=Ix2-A(2)+A(2)*tx;
Jx2=Jx2_./tx;
figure,imshow(Jx2,[]),title('JX2');

Jx3_=Ix3-A(3)+A(3)*tx;
Jx3=Jx3_./tx;
figure,imshow(Jx3,[]),title('JX3');

image=cat(3,Jx1,Jx2,Jx3);

figure,imshow(uint8(image(:,:,1)));
 