img=imread('1.jpg');
size_factor=0.6:0.1:1.5;   %ȡ��ͬ�ĳߴ硣
img_gray=rgb2gray(img);
[pos,target_sz]=getPos_Size(img); 
feature_x=cell(1);
  %cell���Զ�̬���ӣ��ȷ�һ��
for i=1:10
   sz=size_factor(i)*target_sz;
   %sz=target_sz*img_scale;
   img_sc=img_gray(pos(1)-floor(sz(1)/2):pos(1)+floor(sz(1)/2),pos(2)-floor(sz(2)/2):pos(2)+floor(sz(2)/2));
   subplot(5,4,i*2-1),imshow(img_sc);
   img_resize=imresize(img_sc,target_sz);
   %imshow(img_resize);
   feature=hog(img_resize);
   feature_x{i}=cell2mat(feature);
   subplot(5,4,i*2);
   plot(feature_x{i});
end
dif=cell(1);
for i=1:10
    dif{i}=sum(abs(feature_x{i}-feature_x{5}));
end
figure,plot(cell2mat(dif)),title('hog������');
%����yonghog���������߶ȸ���ѽ
    