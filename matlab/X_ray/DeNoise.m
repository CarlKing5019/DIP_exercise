img_path='C:\Users\zhxing\Desktop\X��\X��2\img\';
Dir=dir([img_path,'\*.bmp']);

Dir_sz=size(Dir);
for i=1:Dir_sz(1)

img=imread([img_path,Dir(i).name]);
subplot(Dir_sz(1)/4,2,2*(i-1)+1),imshow(img),title('ԭͼ');
img=double(img);    %ת����double֮�󷽱㴦��

img_f=FFT(img);
subplot(Dir_sz(1)/4,2,2*(i-1)+2),imshow(uint8(img_f),[]),title('Ƶ��');         %��Ƶ���������Ƶ�������ر�ɾ���

%%  ȥ���㷨  ����ͨ��ֵ   ������Ӧ��ֵ  

%% һ. 3*3����ֵ�˲�����ȥ���󲿷ֵĽ�������
img_midFilter=medfilt2(img,[3,3]);
img_midFilter=medfilt2(img_midFilter,[3,3]);
%figure;
%subplot(3,1,1),imshow(uint8(img)),title('ԭͼ');
%subplot(3,1,2),imshow(uint8(img_midFilter)),title('��ֵ�˲�');

% dest=multiScaleSharpen(img_midFilter,5);
% subplot(3,1,3),imshow(uint8(dest)),title('��߶ȶԱȶ���ǿ');


%% ����Ӧ��ֵ�˲���Ч��Ӧ��Ҳ�ǲ���ġ�
img_adptmidian=adpmedian(img,3);
%subplot(3,1,3),imshow(uint8(img_adptmidian)),title('����Ӧ��ֵ�˲�');

end


%% ������ֱ��ͼ���⻯��ǿ�Աȶ�,����������ǿʵ�����ǲ���ȡ�ģ���ΪͼƬ���д����ı������������������ͼƬ����ʧ��
% img_histeq=histeq(uint8(img_midFilter));
% figure,imshow(uint8(img_histeq)),title('hist_eq');


%% ������˹��ǿЧ���ǳ�һ�㡣
% L_8=[1,1,1;1,-8,1;1,1,1];        %������˹���ӣ�������ǿͼ��
% img_laplace=imfilter(img,L_8);
% img_lap=img+(-1)*img_laplace;
% figure
% subplot(2,1,1),imshow(uint8(img_laplace)),title('������˹�����˲�ͼ��');
% subplot(2,1,2),imshow(uint8(img_lap)),title('������˹������ǿ');

