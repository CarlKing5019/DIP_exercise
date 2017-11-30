//��ֵͼ����Ҳ���������

#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat srcImage = imread("contour.bmp", 0);   //�Ҷ�ģʽ����
	imshow("ԭͼ", srcImage);
	Mat dstImage = Mat::zeros(srcImage.size(), CV_8UC3);
	//����ͨ����dstimage�ϻ����ɫ����
	srcImage = srcImage > 128;   //ȡ��ֵ����128��һ����
	imshow("��ֵ֮���ͼ��", srcImage);

	//cout << srcImage(Range(1, 100), Range(1, 20)) << endl;
	//�����뿴��ȡ��ֵ֮�����ʲô���������ȫ��255��0��Ҳ����2ֵͼ��
	vector<vector<Point>>  contours;
	vector<Vec4i> hierarchy;
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	int index = 0;          //���������releaseģʽ�����������ڴ���ʳ�ͻ�����⣬debugģʽ��������
	for (;index >= 0;index = hierarchy[index][0])
	{
		Scalar color(255,255,255);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);

	}
	imshow("����", dstImage);

	cout << contours[5];
	//�Լ���ͼ����һ��,contours������ݵĽṹ�������ġ�
	//����1--����2--����3--������Ȼ��ÿ����������һ����������������Ԫ���ǵ㣬��Щ���������͹���������
	waitKey(0);
	return 0;
}
