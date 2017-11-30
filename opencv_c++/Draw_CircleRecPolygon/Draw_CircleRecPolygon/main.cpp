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

void on_ContoursChange(int, void*);


int main()
{
	g_srcImage = imread("zx.jpg");
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);  //�ҶȻ�
	blur(g_grayImage, g_grayImage, Size(3, 3));         //ƽ��
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("��ֵ", WINDOW_NAME1, &g_nThresh, g_MaxThresh, on_ContoursChange);
	on_ContoursChange(0, 0);

	waitKey();
	return 0;
}

void on_ContoursChange(int, void*)
{
	Mat Threshold_output;
	vector<vector<Point>>  contours;
	vector<Vec4i> hierarchy;

	threshold(g_grayImage, Threshold_output, g_nThresh, 255, THRESH_BINARY);
	//imshow("sd", Threshold_output);
	//��ֵ��
	findContours(Threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,Point(0,0));

	vector<vector<Point>>  contours_poly(contours.size());
	vector<Rect>  BoundRec(contours.size());
	vector<Point2f>  CircleCenter(contours.size());
	vector<float>  CircleRadius(contours.size());
	//����һЩ������������õľ��Σ�������Լ�Բ�����ݡ�


	//����ÿһ�����򣬻�ȡ���Σ�������Լ�Բ�εĲ���
	for (int i = 0;i < contours.size();i++)
	{
		approxPolyDP(contours[i], contours_poly[i], 3, true);  //�����
		BoundRec[i] = boundingRect(contours[i]);         //����
		minEnclosingCircle(contours[i], CircleCenter[i], CircleRadius[i]);
		//Բ
	}

	//��ͼ
	Mat drawing = Mat::zeros(Threshold_output.size(), CV_8UC3);
	for (int i = 0;i < contours.size();i++)
	{
		Scalar color(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0);          //����ı������������i��
		rectangle(drawing, BoundRec[i], color);
		circle(drawing, CircleCenter[i], CircleRadius[i],color);
	}
	imshow(WINDOW_NAME2, drawing);

}