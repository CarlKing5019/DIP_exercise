
%% ���������bmpͼ��Ȼ��14λ��ʽ����λ�ں����첢�洢


img_path='C:\Users\zhxing\Desktop\';       
write_path='C:\Users\zhxing\Desktop\img\'
img_dir=dir([img_path,'*.bmp']);   
num_img=length(img_dir);

video=VideoWriter('baji');
video.open();


%% ��ȡ----------------------------
for j=1:num_img


f=fopen([img_path img_dir(j).name],'r'); 
f_2=fread(f);              %�����ƶ�������
fclose(f);

img16=f_2(1143:end);       %ͷ�ļ�ȥ��
sz=size(img16);

img_8=zeros(sz(1)/2,1);            %���ٴ洢�ռ�洢����������
 k=1;
for i=1:2:sz(1)-1
    high=uint16(img16(i+1));       %��8λ
    low=uint16(img16(i));          %��8λ
    h_l=bitshift(high,8)+low;      %��λ���
    img_8(k)=h_l;                  %�洢
    k=k+1;
end

[,sort_img]=sort(img_8);                    %����
index_min=floor(double(sz(1)/2)*0.002);     %ȥ�����ǧ��֮��
index_max=floor(double(sz(1)/2)*0.998);     %ȥ��������ǧ��֮����ʵ����������������,ȥ��֮��������죩
max_98=sort_img(index_max);                 %������ǧ��֮������Сֵ
min_02=sort_img(index_min);                 %���ǧ��֮���е����ֵ

img_shape=reshape(img_8,[320,256]);         %�ع�ͼ��
img_shape=img_shape';                       %reshapeĬ���ǰ��д洢�ģ�����ת��һ��
img_l=lashen(img_shape,max_98,min_02);      %����

imshow(img_l);
imwrite(img_l,[write_path,num2str(j),'.bmp']);
writeVideo(video,img_l);              %д����Ƶ
j                                     %����
end 
video.close();