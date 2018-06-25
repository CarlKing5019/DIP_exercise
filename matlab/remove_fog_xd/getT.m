%%   img Ϊdouble���uint8ͼ��
%    kernelszΪ�ֿ��С�������Ǿ��ο�
%    A�Ǵ��������ֵ
%    paper<<Optimized contrast enhancement for real-time image and video
%    dehazing>>
%    ʽ 19 


%% ------------------
function T=getT(img,kernelsz,A,eps)      
img=double(img);
se = strel('rectangle',[kernelsz,kernelsz]);
img_c=cell(3);
img_c{1}=(img(:,:,1)-A(1))/(-A(1));         %����ͨ�����任
img_c{2}=(img(:,:,2)-A(2))/(-A(2));
img_c{3}=(img(:,:,3)-A(3))/(-A(3));

img_d=cell(3);
img_d{1}=(img(:,:,1)-A(1))/(255-A(1)+eps);      %����ͨ�����任
img_d{2}=(img(:,:,2)-A(2))/(255-A(2)+eps);
img_d{3}=(img(:,:,3)-A(3))/(255-A(3)+eps);


%��ͨ���ֱ�������ֵ����Сֵ�˲����ֱ��Ӧ���ͺ˸�ʴ���棬��������Ϊmatlab�����ͺ͸�ʴ��ֻ֧����ͨ����
img_erode=cell(3);
img_dilate=cell(3);
img_erode{1}= imerode(img_c{1},se);               %��ʴ
img_erode{2}= imerode(img_c{2},se);
img_erode{3}= imerode(img_c{3},se);

img_dilate{1} = imdilate(img_d{1},se);            %����
img_dilate{2} = imdilate(img_d{2},se);
img_dilate{3} = imdilate(img_d{3},se);

img_e3=cat(3,img_erode{1},img_erode{2},img_erode{3});
img_d3=cat(3,img_dilate{1},img_dilate{2},img_dilate{3});


sz=size(img);
min_=zeros(sz(1),sz(2));
max_=zeros(sz(1),sz(2));
for i=1:sz(1)
    for j=1:sz(2)
        min_(i,j)=min(img_e3(i,j,:));  
        max_(i,j)=max(img_d3(i,j,:));
    end
end

T=min_;
max(min_,max_);

end