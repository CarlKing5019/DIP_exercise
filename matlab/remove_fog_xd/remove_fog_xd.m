%% remove fog test code
% zhxing 2018/6/21



%%
function img_dfog=remove_fog_xd(img)
figure,
%imshow(img),title('ԭͼ');
sz=size(img);

kernelsz=(floor(max([sz(1)*0.01,sz(2)*0.01,3])));

dc=dark_channel(img,kernelsz);          %��ȡ��ͨ��ͼ��
A=getA(img);                   %��ȡ������ֵ

for i=1:3
    if(A(1)<240) 
        A(1)=240;  
    end
    if(A(2)<240) 
        A(2)=240;  
    end 
    if(A(3)<240) 
        A(3)=240;  
    end
end



r = kernelsz*4;
eps = 10^-6;
tx=guidedfilter(double(rgb2gray(img))/255,double(dc)/255.0,r,eps);        %�����˲����͸����ͼ
%figure,imshow(tx,[]),title('͸����ͼ')

img=double(img);

Ix1=(img(:,:,1));             %ͨ������
Ix2=(img(:,:,2));
Ix3=(img(:,:,3));

Jx1_=Ix1-A(1)+A(1)*tx;
Jx1=Jx1_./tx;
%figure,imshow(Jx1,[]),title('JX1');


Jx2_=Ix2-A(2)+A(2)*tx;
Jx2=Jx2_./tx;
%figure,imshow(Jx2,[]),title('JX2');

Jx3_=Ix3-A(3)+A(3)*tx;
Jx3=Jx3_./tx;
%figure,imshow(Jx3,[]),title('JX3');

img_dfog=cat(3,Jx1,Jx2,Jx3);


%figure,imshow(uint8(image)),title('defog');

end
%ӳ�䵽0-255


 