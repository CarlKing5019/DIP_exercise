%һ�����ͼ�λ�ɫ���ο�Ľű����õ���򵥵�ͨ��������ͶӰ

img=imread('1.jpg');
%����ͨ��
img_red=double(img(:,:,1));
img_yel=double(img(:,:,2));
img_blu=double(img(:,:,3));

%���ӻ�һ�¼������
img_r_y=img_red-img_yel;
figure(1),imshow(img_r_y,[]),title('red-yel');
sum_col=sum(img_r_y);
figure(2),subplot(2,1,1),plot(sum_col,'o');
sum_row=sum((img_r_y)');
subplot(2,1,2),plot(sum_row,'+');

%����ȡ����������������Ҫ���������
[x,row_sort]=sort(sum_col);
row_s=min(row_sort(end),row_sort(end-1));
row_l=max(row_sort(end),row_sort(end-1));

[y,col_sort]=sort(sum_row);
col_s=min(col_sort(end),col_sort(end-1));
col_l=max(col_sort(end),col_sort(end-1));


%��ԭͼ�Ͽ��ӻ�
figure(3),imshow(img),title('ԭͼ');
hold on;
rectangle('position',[row_s,col_s,row_l-row_s,col_l-col_s,],'edgecolor','g','linewidth',2);

