function [pos,target_size]=getPos_Size(Image)
imshow(Image);
h=imrect;
pos_infor=getPosition(h);   %��õ������Ͻǵ������Լ���͸�
pos=floor([pos_infor(2)+pos_infor(4)/2,pos_infor(1)+pos_infor(3)/2]);      %�õ�����λ�ã�����ת��������
target_size=[pos_infor(1,4),pos_infor(1,3)];     %�õ�target_size������Ҳ������
end