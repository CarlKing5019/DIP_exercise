//�����˲��ۺϲ��Գ���
//author  zhxing
//2017-06-01 
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//---------------------��ȫ�ֱ�����-------------------


int main()
{

	Mat g_inputImage = imread("C:/Users/zh_xing/Desktop/opencv/xyjy.jpg");
	Mat out;
	bilateralFilter(g_inputImage, out, 25, 25 * 2, 25 / 2);
	imshow("asd", out);


	waitKey();
	return 0;



}