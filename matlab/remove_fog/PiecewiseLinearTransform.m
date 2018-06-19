%% ͼ��ķֶ����Ա任  
% ���ߣ����  
% ���ڣ�2014.09.23  
% �����������⻯��ͼƬ���ļ���  
% ��������⻯����֮���ͼƬ����  
%%  
function f = PiecewiseLinearTransform(imgFile)  
img = imread(imgFile);  
imshow(img);  
height = size(img, 1);  
width = size(img, 2);  
% ��������ͼ���еķֽ��  
c = 32;  
a = 64;  
d = 128;  
b = 128;  
mf = 256;  
mg = 256;  
% ��ʼ������  
f = uint8(zeros(height, width));  
% ���ݺ��������任��������ж�д���д��Ż�  
for i = 1:height  
    for j = 1:width  
        if (img(i, j) > 0) && (img(i, j) < a)  
            f(i, j) = round((c / a) * img(i, j));  
        elseif (img(i, j) >= a) && (img(i, j) <= b)  
            f(i, j) = round((d / b) * (img(i, j)));  
        elseif (img(i, j) > b)  
            f(i, j) = round((mg / mf) * img(i, j));  
        end  
    end  
end  
figure, imshow(f);  