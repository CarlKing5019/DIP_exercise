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
Mat g_cannyMat_output;
vector<vector<Point>>  g_contours; //������
vector<Vec4i>  g_hierarchy;

void on_ThreshChange(int, void*);


int main()
{
	g_srcImage = imread("1.jpg");
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
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);
	//canny����Ե
	imshow("canny", g_cannyMat_output);
	findContours(g_cannyMat_output, g_contours, g_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//�ҵ����� ,������debug��������releaseģʽ�����ڴ���ʵĴ���
	vector<Moments>  mu(g_contours.size());   
	//������ż������þ���Ϣ��
	//����ת������ȡ����Monment��ֵ��ʵ���ϰ�����10���أ�����Ϊ��
	//Moments(double m00, double m10, double m01, double m20, double m11,
    //        double m02, double m30, double m21, double m12, double m03 )


	//����ÿһ�����򣬼������Ϣ
	for (int i = 0;i < g_contours.size();i++)
	{
		mu[i] = moments(g_contours[i]);      //�������Ϣ
	}
	
	//�������ľ�
	vector<Point2f>  mc(g_contours.size());  //���ľ࣬�ֱ�x�����y����ģ�ʵ���Ͼ�������
	for (int i = 0;i < g_contours.size();i++)
	{
		mc[i] = Point2f(float(mu[i].m10 / mu[i].m00), float(mu[i].m01 / mu[i].m00));
		//���ľ���󷨣�һ�׾�/��׾�
	}

	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);

	//��ͼ
	for (int i = 0;i < g_contours.size();i++)
	{
		Scalar color(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_contours, i, color, 2, 8, g_hierarchy, 0);         
		//����ı������������i��,���Ʊ�Ե
		circle(drawing, mc[i], 5, color);       //���ﻭ��Բ��ʾ�������ڵ�λ��
	}
	imshow(WINDOW_NAME2, drawing);
	
	cout << "----���������������ȣ�-------" << endl;
	cout << "-----��ǰcanny�����ֵΪ��" << g_nThresh << "-------" << endl;
	for (int i = 0;i < g_contours.size();i++)
	{
		cout << "��" << i << "�����������Ϊ��" << mu[i].m00 << endl;
	}
	
}
