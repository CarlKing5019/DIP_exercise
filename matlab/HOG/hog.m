clear all;
clc;

img=imread('1.jpg');
figure
imshow(img),title('ԭͼ');
figure
img=rgb2gray(img);
imshow(img),title('�Ҷ�ͼ')
[m, n]=size(img);
img=sqrt(double(img));      %٤��У��
figure
imshow(uint8(img)),title('gamma����֮��')

%���������Ե
fy=[-1 0 1];        %������ֱģ��
fx=fy';             %����ˮƽģ��
Iy=imfilter(img,fy,'replicate');    %��ֱ��Ե
figure,imshow(Iy),title('��ֱ��Ե,�ݶ�');
Ix=imfilter(img,fx,'replicate');    %ˮƽ��Ե
figure,imshow(Ix),title('ˮƽ��Ե,�ݶ�');
Ied=sqrt(Ix.^2+Iy.^2);              %��Եǿ��
Iphase=Iy./Ix;              %��Եб�ʣ���ЩΪinf,-inf,nan������nan��Ҫ�ٴ���һ�£�����������ֵ


%��������cell
step=16;                %step*step��������Ϊһ����Ԫ 16*16=256����
orient=9;               %����ֱ��ͼ�ķ������  9������40�ȷֱ���
jiao=360/orient;        %ÿ����������ĽǶ���
Cell=cell(1,1);              %���еĽǶ�ֱ��ͼ,cell�ǿ��Զ�̬���ӵģ�����������һ��
ii=1;                      
jj=1;
for i=1:step:m-step   %�зֿ�           %��������m/step���������������i=1:step�ֿ鴦�������û��϶����б߽�ЧӦ�ģ��ܲ�����
    ii=1;
    for j=1:step:n-step      %�зֿ飬ע��ͬ��
        tmpx=Ix(i:i+step-1,j:j+step-1);      %�������x�ݶ�
        tmped=Ied(i:i+step-1,j:j+step-1);     %ǿ��
        tmped=tmped/sum(sum(tmped));        %�ֲ���Եǿ�ȹ�һ��,����ֵ��������һ��
        tmpphase=Iphase(i:i+step-1,j:j+step-1);   %��λ������ֵ
        Hist=zeros(1,orient);               %��ǰstep*step���ؿ�ͳ�ƽǶ�ֱ��ͼ,����cell���浽cell��
        for p=1:step      %��ÿ���ĽǶ������
            for q=1:step
                if isnan(tmpphase(p,q))==1  %0/0��õ�nan�����������nan������Ϊ0
                    tmpphase(p,q)=0;
                end
                ang=atan(tmpphase(p,q));    %atan�����[-90 90]��֮��
                ang=mod(ang*180/pi,360);    %ȫ��������-90��270 �������Ǹ�ȡ�����
                if tmpx(p,q)<0              %����x����ȷ�������ĽǶȣ�������������x�������λ��Ҫ������ȷ�������ĽǶȵ�
                    if ang<90               %����ǵ�һ����
                        ang=ang+180;        %�Ƶ���������
                    end
                    if ang>270              %����ǵ�������
                        ang=ang-180;        %�Ƶ��ڶ�����
                    end
                end        
                ang=ang+0.0000001;          %��ֹangΪ0���ţ�ȫ����Ϊ����ĽǶȡ�
                Hist(ceil(ang/jiao))=Hist(ceil(ang/jiao))+tmped(p,q)*1;   
                %ceil����ȡ����ʹ�ñ�Եǿ�ȼ�Ȩ�������Ȩ�Ļ�Ӧ�þ���1�������Ǽ�Ȩ���ģ�Ҳ����˵��ǿ��Խ����ֱ��ͼ�еĹ��׾�Խ��
            end
        end
        Hist=Hist/sum(Hist);    %����ֱ��ͼ��һ��
        Cell{ii,jj}=Hist;       %����Cell��
        ii=ii+1;                %���Cell��y����ѭ������
    end
    jj=jj+1;                    %���Cell��x����ѭ������
end

%��������feature,2*2��cell�ϳ�һ��block,û����ʽ����block
[m ,n]=size(Cell);
feature=cell(1,(m-1)*(n-1));
for i=1:m-1
   for j=1:n-1           
        f=[];
        f=[f Cell{i,j}(:)' Cell{i,j+1}(:)' Cell{i+1,j}(:)' Cell{i+1,j+1}(:)'];  %�ĸ���Ԫ�ϳ�һ��
        %�������Ļ����кܶ��ص��ġ�
        feature{(i-1)*(n-1)+j}=f;         %����Ҳ�����������ı�����������������������
   end
end

%���˽�����feature��Ϊ����
%������Ϊ����ʾ��д��
l=length(feature);
f=[];
for i=1:l
    f=[f;feature{i}(:)'];  
end 
figure
mesh(f)