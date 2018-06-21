%% ��ȡ������ֵ�������Ĳ�������������
% ���Ȱ�����ԭʼͼ��I���ֳ��ĸ���������Ȼ��Ϊÿ��������������֣�
% ������ֵļ��㷽���ǡ������������ص�ƽ��ֵ��ȥ��Щ���صı�׼���
% ѡ��÷���ߵ����򣬲������������Ϊ��С���ĸ��Ӿ��Σ��ظ��������
% ֱ����ѡ�е�����С��ĳ����ǰָ������ֵ��ͼ6�еĺ�ɫ���򲿷־�������
% ��ѡ�����������ⱻѡ���������ѡ��ʹ�þ��� 
% ||(Ir(p),Ig(p),Ib(p))-(255,255,255)|| ��С������ɫ������ r,g,b ����������
% ����Ϊ������Ĳο�ֵ��


%% ����Ϊ��ͨ����ɫͼ�� uint8��ʽ
function A=getA(img)
   img=double(img);             %ת��Ϊdouble
   SZ=size(img);
   row=floor(SZ(1)/2);
   col=floor(SZ(2)/2);
   while(row*col>25)
       %%  ͼ��ֿ�
        up_left=img(1:row,1:col,:);                             %����
        up_right=img(1:row,col:end,:);                          %����
        down_left=img(row:end,1:col,:);                         %����
        down_right=img(row:end,col:end,:);                      %����
        cost1=mean(up_left(:))-sqrt(std(up_left(:)));
        cost2=mean(up_right(:))-sqrt(std(up_right(:)));
        cost3=mean(down_left(:))-sqrt(std(down_left(:)));
        cost4=mean(down_right(:))-sqrt(std(down_right(:)));
        [ ~,index]=max([cost1,cost2,cost3,cost4]);
        switch index
            case 1
                img=up_left;
            case 2
                img=up_right;
            case 3
                img=down_left;
            case 4
                img=down_right;
        end
        SZ=size(img);
        row=floor(SZ(1)/2);
        col=floor(SZ(2)/2);
   end
   A_1=img(:,:,1)-255;
   A_2=img(:,:,2)-255;
   A_3=img(:,:,3)-255;
   A_=A_1.*A_1+A_2.*A_2+A_3.*A_3;
   [x,y]=find(A_==min(A_(:)));
   A=(img(x(1),y(1),:));
end