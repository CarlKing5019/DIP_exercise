#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//-----------��ȫ�ֱ����������֡�------------------
//          ȫ�ֱ�������
//-------------------------------------------------
int g_nConstractValue;
int g_nBrightValue;
Mat g_scrImage, g_dstImage;

//------------��ȫ�ֺ����������֡�-----------------
//		�Ӻ�������
//------------------------------------------------
static void on_ConstractAndBright(int, void *);


//-----------����������ڡ�----------------------
//	�������  main����
//------------------------------------------------

int main()
{
	g_scrImage = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\cx.jpg");
	g_dstImage = Mat::zeros(g_scrImage.size(), g_scrImage.type());
	g_nBrightValue = 50;
	g_nConstractValue = 50;   //�趨��ʼֵ
	namedWindow("Ч��ͼ����", WINDOW_FREERATIO);
	createTrackbar("�Աȶ�", "Ч��ͼ����", &g_nConstractValue, 200, on_ConstractAndBright);
	createTrackbar("����", "Ч��ͼ����", &g_nBrightValue, 100, on_ConstractAndBright);

	on_ConstractAndBright(g_nConstractValue, 0);
	on_ConstractAndBright(g_nBrightValue, 0);
	waitKey();
	return 0;

}


//------------���������ص�������-----------------
//		�ı�ͼ��ԱȶȺ�����ֵ
//-----------------------------------------------
static void on_ConstractAndBright(int, void *)
{
	namedWindow("ԭʼͼ", 1);   //��������
	for (int x = 0; x < g_scrImage.rows; x++)
	{
		for (int y = 0; y < g_scrImage.cols; y++)
		{
			for (int z = 0; z < 3; z++)
				g_dstImage.at<Vec3b>(x, y)[z] = saturate_cast<uchar>((g_nConstractValue*0.01)*(g_scrImage.at<Vec3b>(x, y)[z]) + g_nBrightValue);
		}		//����ÿ�����ض���ԱȶȺ����Ƚ��е���
	}

	imshow("ԭʼͼ", g_scrImage);
	imshow("Ч��ͼ����", g_dstImage);
}
