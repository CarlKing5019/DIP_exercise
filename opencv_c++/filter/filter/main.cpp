//�����˲��ۺϲ��Գ���
//author  zhxing
//2017-06-01 10:24:43

#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//---------------------��ȫ�ֱ�����-------------------
Mat g_inputImage, g_outImage1, g_outImage2, g_outImage3, g_outImage4, g_outImage5;
//���뼰���ͼ��
int g_nBoxFilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;
int g_nMedianBlurValue = 3;
int g_nBilateralValue = 5;
//�˲����˲��˳�ʼ��С

//--------------------��ȫ�ֺ���������--------------------
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);
static void on_MidianBlur(int, void*);      //��ֵ�˲�
static void on_BilateralFilter(int, void*);  //˫���˲�
//�ص�����������������ɹ켣�����Ըı�켣���Ĵ�С


int main()
{
	
	g_inputImage = imread("C:/Users/zh_xing/Desktop/opencv/xyjy.jpg");
	if (!g_inputImage.data)
	{
		cout << "ͼƬ·�������⣬ȷ��ͼƬ·����ȷ�����г���" << endl;
		return 0;
	}

	g_outImage1 = g_inputImage.clone();
	g_outImage2 = g_inputImage.clone();
	g_outImage3 = g_inputImage.clone();
	g_outImage4 = g_inputImage.clone();
	g_outImage5 = g_inputImage.clone();

	namedWindow("ԭͼ����");
	imshow("ԭͼ����", g_inputImage);
	
	
	
	//��������
	namedWindow("�����˲�");
	createTrackbar("�ں�ֵ", "�����˲�", &g_nBoxFilterValue, 30, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	

	namedWindow("��ֵ�˲�");
	createTrackbar("�ں�ֵ", "��ֵ�˲�", &g_nMeanBlurValue, 30, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
	

	namedWindow("��˹�˲�");
	createTrackbar("�ں�ֵ", "��˹�˲�", &g_nGaussianBlurValue, 30, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);
	
	namedWindow("��ֵ�˲�");
	createTrackbar("�����С", "��ֵ�˲�", &g_nMedianBlurValue, 40, on_MidianBlur);
	on_MidianBlur(g_nMedianBlurValue, 0);

	namedWindow("˫���˲�");
	createTrackbar("�����С", "˫���˲�", &g_nBilateralValue, 30, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralValue, 0);      //���Ե�ʱ����仰������ڴ���ʳ����ص����������⣿
	namedWindow("˫��");
	bilateralFilter(g_inputImage, g_outImage5, 10, 20, 5);
	imshow("˫��", g_outImage5);
	cout << "�뻬���������Թ۲��˲����" << endl;

	//��˫�����˲���������ͻ���ִ��󣬵�����Ҳ������ڴ���ʴ��󣬲�֪��ʲôԭ��

	waitKey();
	return 0;

		

}


//---------------------���Ӻ���������------------------------

//-----------------�������˲���------------------------------
static void on_BoxFilter(int, void*)
{
	boxFilter(g_inputImage, g_outImage1, -1,Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
	imshow("�����˲�", g_outImage1);
}

//-----------------����ֵ�˲���-----------------------------
static void on_MeanBlur(int, void*)
{
	blur(g_inputImage, g_outImage2, Size(g_nMeanBlurValue+1, g_nMeanBlurValue+1));
	imshow("��ֵ�˲�", g_outImage2);  //������Size�����˸�1����1��ԭ���Ǿ���˳ߴ粻����0���������ڴ���ʴ���
}

//--------------- -����˹�˲���---------------------------------------
static void on_GaussianBlur(int, void*)
{
	GaussianBlur(g_inputImage, g_outImage3, Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
	imshow("��˹�˲�", g_outImage3);
}

//--------------����ֵ�˲���------------------------------------------
static void on_MidianBlur(int, void*)
{
	medianBlur(g_inputImage, g_outImage4, g_nMedianBlurValue*2+1);
	imshow("��ֵ�˲�", g_outImage4);
}

static void on_BilateralFilter(int, void*)
{
	bilateralFilter(g_inputImage, g_outImage5, g_nBilateralValue, g_nBilateralValue * 2, g_nBilateralValue / 2);
	imshow("˫���˲�", g_outImage5);

}