clear all;  
I = zeros(120,180);  
I(11:80,16:75) = 1;  
I(56:105,86:135) = 1;  
I(26:55,141:170) = 1;  
figure,imshow(I);  


se = ones(50,50);   
figure,imshow(se);  
  
%���л����б任  
Ie1 = imerode(I,se);    
figure,imshow(Ie1),title('A-D')  
  


W=ones(58,58);
W(5:54,5:54)=0;
figure,imshow(W);title('W-D')

Ic = 1 - I;     
figure,imshow(Ic),title('ԭͼȡ��');

a=imerode(Ic,W);
figure,imshow(a),title('ԭͼ������W-D��ʴ');

T=a&Ie1;
figure,imshow(T),title('ǰ����������');