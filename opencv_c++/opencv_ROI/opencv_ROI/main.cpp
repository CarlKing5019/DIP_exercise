//������ROI����
//zhxing


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//-----------��ȫ�ֱ����������֡�------------------
//          ȫ�ֱ�������
//-------------------------------------------------


//------------��ȫ�ֺ����������֡�-----------------
//		�Ӻ�������
//------------------------------------------------




//-----------����������ڡ�----------------------
//	�������  main����
//------------------------------------------------

int main()
{
	Mat img = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\chunxia.jpg");
	Mat logo= imread("C:\\Users\\zh_xing\\Desktop\\opencv\\logo.jpg");
	Mat img_roi = img(Rect(100, 100, logo.cols, logo.rows));
	//Mat img_roi = img(Rect(100, 100, logo.cols, logo.rows)).clone();
	//����Rect��������Ȥ����,����ֱ�Ӵ����ĸ���Ȥ�����Ǻ�ԭͼ��ص�.
	//�������clone��������ͽ�����һ���µľ����޸�������󲻻�ı�ԭͼ�ġ�
	
	img_roi=Mat::zeros(img_roi.rows, img_roi.cols, CV_8UC3);   
	//����������ֱ�Ӳ���img_roiҲ���ԭͼ�����Ӱ��
	imshow("roi", img_roi);
	Mat mask = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\logo.jpg",0);
	//Mat mask = Mat::ones(img_roi.rows, img_roi.cols, CV_8UC1);
	//�������ģ����ֻҪ�Ƿ���ľͿ�����,��Ҫ��copyto�������÷�������
	cout << format(mask,Formatter::FMT_MATLAB);
	//������ģ
	logo.copyTo(img_roi, mask);
	//������ȥ
	imshow("12", img);


	
	waitKey();
	return 0;

}


//------------���Ӻ���ԭ�Ͳ��֡�-----------------
//		�Ӻ���ԭ�Ͷ���
//-----------------------------------------------



