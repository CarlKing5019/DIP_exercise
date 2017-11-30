//Ѱ�Ҳ����������͹��
#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "ԭʼͼ����"
#define WINDOW_NAME2 "Ч��ͼ����"

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_MaxThresh = 255;
RNG g_rng;
Mat srcImage_copy = g_srcImage.clone();
Mat g_ThresholdImage_output;
vector<vector<Point>> g_contours;
vector<Vec4i>  g_Hierarchy;

void on_ThreshChange(int, void*);

int main()
{
	g_srcImage = imread("zx.jpg");      
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);  //�ҶȻ�
 	blur(g_grayImage, g_grayImage, Size(3, 3));         //ƽ��
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("��ֵ", WINDOW_NAME1, &g_nThresh, g_MaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);


	waitKey();
	return 0;
}


void on_ThreshChange(int, void*)
{
	threshold(g_grayImage, g_ThresholdImage_output, g_nThresh, 255, THRESH_BINARY);
	//��ֵ��
	findContours(g_ThresholdImage_output, g_contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//������
	vector<vector<Point>>   Hull(g_contours.size());
	for (int i = 0;i < g_contours.size();i++)
	{
		convexHull(Mat(g_contours[i]), Hull[i]);
		//Ѱ��������͹��
	}
	Mat drawing = Mat::zeros(g_ThresholdImage_output.size(), CV_8UC3);
	for (int i = 0;i < g_contours.size();i++)
	{
		Scalar color(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_contours, i, color, 1, 8, vector<Vec4i>(), 0);
		//������

		drawContours(drawing, Hull, i, color, 1, 8, vector<Vec4i>(), 0);
		//��͹��
	}
	imshow(WINDOW_NAME2, drawing);

}