


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;



//-----------����������ڡ�----------------------
//	�������  main����
//------------------------------------------------

int main()
{
	Mat srcImage, dstImage, gray;
	srcImage = imread("1.jpg");   
	imshow("ԭͼ",srcImage);
	cvtColor(srcImage, gray, COLOR_RGB2GRAY);
	imshow("�Ҷ�ͼ", gray);        //�Ҷ�ͼ
	Mat edge;
	blur(gray, edge, Size(3, 3));   //����
	Canny(edge, edge, 3, 9, 3);
	imshow("edge", edge);
	dstImage = Scalar::all(0);      //Ŀ��ͼ������Ϊ0
	srcImage.copyTo(dstImage, edge);
	imshow("��ɫ��Ե", dstImage);         //��Ĥ���ǰѷ���Ŀ�����ȥ
	waitKey();
	return 0;

}







//------------���Ӻ���ԭ�Ͳ��֡�-----------------
//		�Ӻ���ԭ�Ͷ���
//-----------------------------------------------



