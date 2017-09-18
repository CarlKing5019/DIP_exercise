%FOI(frames of interest)��ȡ���򣬻���ǰ�������ֵ��֮��õ�������ȡ
%2017/9/18

clear all;
thresh=0.1;          %�ж��Ƿ�Ϊ�ؼ�֡����ֵ��������ݲ�ͬ����Ƶ����Ҫ��΢��
path0='Escalator.avi';
path1='Escalator_fore.avi';
video0 = VideoReader(path0);  
video1 = VideoReader(path1);                  %��ȡ��Ƶ
frame_n=video1.NumberOfFrames;               %��Ƶ֡��

Area=zeros(1,frame_n);      %����ֱ��ͼ�Ĳ�ֵ.ÿһ֡��������

for i=1:frame_n                          %������Ƶ
    current=read(video1,i);               %��ȡ֡    
    subplot(2,1,1);
    imshow(current);
    title('ǰ��');
    current_gray=rgb2gray(current);
    current_bw=logical(current_gray);      %��ֵ��,��Ϊ������õ�ǰ��������ֵ��֮��ģ�����Ͳ���im2bw�ˣ�ֱ���߼����Ϳɡ�
   
    Area_LTY=regionprops(current_bw,'Area');   %���������ͨ����������
    LTY_num=size(Area_LTY);                         %��ͨ�����
    
    if(isempty(Area_LTY))            %�����������ͨ���ֱ��������ǰ֡��ѭ��
        continue;
    end
    for j=1:LTY_num
    Area(i)=Area(i)+ Area_LTY(j).Area;              %������ھͰ��������������
    end
    subplot(2,1,2);
    plot(Area)
    title('���'); 
end


Area=Area/max(Area);      %��һ�������Լ���ֵѡ��
plot(Area);                       %��һ���Ժ��ֱ��ͼ֮��
index=find(Area>thresh);          %�ҵ�������ֵ������֡�ı��

index_size=size(index);               %FOI��֡��

object1=VideoWriter('Escalator_FIO_area.avi');    %��ת���ɵ���Ƶ����
open(object1);
%��ʾ��ȡ������֡���������avi��Ƶ�����Կ���������Щ�������Ѿ�����Ч��
for i=1:1:index_size(2)
    frame_index=read(video0,index(i));
    writeVideo(object1, frame_index);
    imshow(frame_index); 
end
close(object1);
