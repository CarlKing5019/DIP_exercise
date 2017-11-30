#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_srcGrayImage, g_dstImage;
//ԭͼ  �Ҷ�ͼ Ŀ��ͼ

Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;    //������λ�ò���
//canny��ز���

Mat g_Sobel_x, g_Sobel_y;
Mat g_Sobel_xAbs, g_Sobel_yAbs;
int g_sobelSize = 1;
//Sobel��ر���

Mat g_Scharr_x, g_Scharr_y;
Mat g_Scharr_xAbs, g_Scharr_yAbs;
//scharr��ر���

static void on_Canny(int, void*);
static void on_Sobel(int, void*);  
void Scharr();


int main()
{
	g_srcImage = imread("zx.jpg");
	imshow("ԭͼ", g_srcImage);
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼ", g_srcGrayImage);

	//g_dstImage.create(g_srcImage.size(), g_srcImage.type()); 
	//�����п��ޣ��������õ���ʱ����Զ������ڴ�ռ䡣

	namedWindow("canny");
	namedWindow("sobel");

	createTrackbar("canny_size", "canny", &g_cannyLowThreshold, 50, on_Canny);
	createTrackbar("sobel_size", "sobel", &g_sobelSize, 3, on_Sobel);
	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();
	

	waitKey();
	return 0;
}


static void on_Canny(int, void *)
{	
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));  //�Ƚ���
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*2.5);
	//��Ե���õ��Ҷ�ͼ��
	g_dstImage = Scalar::all(0);   //��ȫ��0����Ϊ����Ҫ���뿽��
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);  
	//��canny��ԵΪ���뿽�����ݵ�ԭͼ���õ����ǲ�ɫ�ı�Ե��
	imshow("canny", g_dstImage);  //��ʾͼ��
}

static void on_Sobel(int, void*)
{
	Sobel(g_srcImage, g_Sobel_x, g_srcImage.depth(), 1, 0,g_sobelSize*2+1);
	convertScaleAbs(g_Sobel_x, g_Sobel_xAbs);   //ȡ����ֵ����һ����0-255
	//x����
	Sobel(g_srcImage, g_Sobel_y, g_srcImage.depth(), 1, 0, g_sobelSize * 2 + 1);
	convertScaleAbs(g_Sobel_y, g_Sobel_yAbs); //ȡ����ֵ����һ����0-255
	//y����

	addWeighted(g_Sobel_xAbs,0.5, g_Sobel_yAbs,0.5,0, g_dstImage);
	imshow("sobel", g_dstImage);
	//�ϲ��ݶȲ���ʾ���
}


void Scharr()
{
	Scharr(g_srcImage, g_Scharr_x,g_srcImage.depth(), 1, 0);   //x�����ݶ�
	convertScaleAbs(g_Scharr_x, g_Scharr_xAbs);

	Scharr(g_srcImage, g_Scharr_y, g_srcImage.depth(), 1, 0);   //y�����ݶ�
	convertScaleAbs(g_Scharr_y, g_Scharr_yAbs);

	addWeighted(g_Scharr_xAbs, 0.5, g_Scharr_yAbs, 0.5,0,g_dstImage);  //�ϲ��ݶ�
	imshow("scharr", g_dstImage);
}