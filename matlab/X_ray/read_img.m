
img_path='C:\Users\zhxing\Desktop\X��\X��3\';
write_path='C:\Users\zhxing\Desktop\X��\X��3\img\';
img_dir=dir([img_path,'*.out']);   
num_img=length(img_dir);


%% ��ȡ----------------------------
for j=1:num_img


f=fopen([img_path img_dir(j).name],'r'); 
f_2=fread(f);              %�����ƶ�������
sz=size(f_2)
fclose(f);
if(sz(1)==207360)
    img_8=f_2(1:end);
end
% if j==1
%     
% elseif j==6
%     img_8=f_2(1:end);
% else
% img_8=f_2(1:end);         %ͷ�ļ�ȥ��  
% end


% [,sort_img]=sort(img_8);                    %����
% index_min=floor(double(sz(1)/2)*0.002);     %ȥ�����ǧ��֮��
% index_max=floor(double(sz(1)/2)*0.998);     %ȥ��������ǧ��֮����ʵ����������������,ȥ��֮��������죩
% max_98=sort_img(index_max);                 %������ǧ��֮������Сֵ
% min_02=sort_img(index_min);                 %���ǧ��֮���е����ֵ

img_shape=reshape(img_8,[720,288]);         %�ع�ͼ��
img_shape=img_shape';                       %reshapeĬ���ǰ��д洢�ģ�����ת��һ��
img=img_shape;
imshow(img,[]);
img=uint8(img);
imwrite(img,[write_path,img_dir(j).name(1:end-4),'.bmp']);

           %д����Ƶ
j                                     %����
end 
