%FOI(frames of interest)��ȡ���򣬻���ֱ��ͼ���ƶ�ƥ��
%FOI��ȡ�ǰ�����������һ�������õ�����

clear all;
thresh=0.4;          %�ж��Ƿ�Ϊ�ؼ�֡����ֵ��������ݲ�ͬ����Ƶ����Ҫ��΢��
path='C:\Users\zhxing\Desktop\cv_tracking\����3-���ǰ����Ƶ\curtain\Curtain.avi';
video = VideoReader(path);                  %��ȡ��Ƶ
frame_n=video.NumberOfFrames;               %��Ƶ֡��
video_bg=[];                 %����һ��ͼ�������洢����
s=[];                        %ȡ��ֵ��������


%%%%%%%%%%��������������ص����ֵ��
for i=1:frame_n/10            %ȡȫ�����е�1/10��֡������ģ����
                             
    video_frame=read(video,i);
    video_frame=rgb2gray(video_frame);      %�Ҷ�ͼ��

    video_frame_g=medfilt2(video_frame);    %��ֵ�˲����˵���Ƶ
    
    s=[s,double(video_frame_g(:))];        %��ÿ��ֵ����һ�����������������һ��  ��640*480��*֡��  ��С�ľ���
    i                                 %��ʾ����
end

s=s';                               %Ҫת�ã���Ϊmedian����������е���ֵ
siz=size(video_frame_g);             %��С
video_bg=median(s);                  % ���ͼ����м�ֵ
video_bg=reshape(video_bg,siz);       %�ع�ͼ��
video_bg=uint8(video_bg);             %ת����8�׻Ҷ�
subplot(2,2,1);
imshow(video_bg);                    %��ʾ��ֵͼ��Ҳ���ǽ�ģ�õ��ı���
title('����');
hist_bg=imhist(video_bg,8);         %����ȡ���ǰ˶�ֱ��ͼ������Ϊ32
subplot(2,2,2);
bar(hist_bg);
title('����ֱ��ͼ');

hist_cha=zeros(1,frame_n);      %����ֱ��ͼ�Ĳ�ֵ.ÿһ֡��������

for i=1:frame_n                              %ֱ����ÿһ֡�ͱ������
    current=read(video,i);                 
    current=rgb2gray(current);
    hist_bg_frame=imhist(current,8);
    hist_cha(i)=sum(abs(hist_bg_frame-hist_bg));       %��ֱ��ͼ��࣬�����õ���򵥵Ķ�Ӧbin�Ĳ�ľ���ֵ֮��
    subplot(2,2,3);
    imshow(current);
    title('��ǰ��Ƶ');
    subplot(2,2,4);
    plot(hist_cha);
    title('��ǰ֡�뱳��ֱ��ͼ���');             %�����Ǿ���ֵ���������ֵ
end

hist_cha=hist_cha/max(hist_cha);      %��һ�������Լ���ֵѡ��
plot(hist_cha);                       %��һ���Ժ��ֱ��ͼ֮��
index=find(hist_cha>thresh);          %�ҵ�������ֵ������֡�ı��

index_size=size(index);               %FOI��֡��

object1=VideoWriter('Curtain_FIO.avi');    %��ת���ɵ���Ƶ����
open(object1);
%��ʾ��ȡ������֡���������avi��Ƶ�����Կ���������Щ�������Ѿ�����Ч��
for i=1:1:index_size(2)
    frame_index=read(video,index(i));
    writeVideo(object1, frame_index);
    imshow(frame_index); 
end
close(object1);
