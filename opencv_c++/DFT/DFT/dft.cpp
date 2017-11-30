//dft���Գ���
//zhxing  2017-05-30 17:42:48


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<math.h>          

using namespace cv;
using namespace std;



//-----------����������ڡ�----------------------
//	�������  main����
//------------------------------------------------

int main()
{
	Mat srcImage = imread("C:/Users/zh_xing/Desktop/opencv/cx.jpg",0);  //�ԻҶȶ���
	if (!srcImage.data) {
		cout << "��ȡ��������ͼƬ·���Ƿ���ȷ" << endl;
		return false;
	}
	imshow("", srcImage);

	//����߽磬�����Ŀ��������dft������ٶ�
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	Mat padded;   //���������������ͼ��
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
	//ȫ0���
	//��ҳ����һҳ��double���ԭ�Ҷ�ͼ���ڶ�ҳ��ȫ�����
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };   //size������õ���һ��size�͵�����
	
	
	//ΪDFT�Ľ�������ڴ�ռ䣬����ͨ���ֱ���ʵ��������
	/*Mat x;
	planes[0].convertTo(x, CV_8U);*/    //�����ǲ����£�imshowĬ����ʾ����uint8�͵ģ������double�Ļ�imshowֻ��ʾ��һ���Ľ��
									   //���ֻ��ת����double�Ļ���Ҫ��һ��֮����imshow��ʾ�����ֱ����ʾ������ȫ�׵Ľ��
	
	Mat complexI;
	merge(planes, 2, complexI);    //�ϲ���һ��ͨ��

	dft(complexI, complexI);   //ԭλFFT
	
	//������ת��Ϊ��ֵ
	split(complexI, planes);   //����ͨ��
	magnitude(planes[0], planes[1], planes[0]);   //���ֵ������ʵ����ͨ����
	Mat magnitudeImage = planes[0];            //�ѷ�ֵͼ�񵥶��ó���

	//����Ҷ�任��ֵ�ܴ󣬴󵽲��ʺ�ֱ����ʾ���������ǰ���������ת���ɶ�������úܶ�
	magnitudeImage += Scalar::all(1);     //��1����  Ӧ����Ϊlog��׼����Ҫ���е�������0
	log(magnitudeImage, magnitudeImage);        //�����

	
	
	//Ƶ�����Ļ�
	magnitudeImage = magnitudeImage(Rect(0, 0, srcImage.cols, srcImage.rows));  
	//ԭʼͼ����չ����еĸ���Ҷ�任������������
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
	//��һ��

	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	//cx���У�������y�����꣬opencv�������Ͻ�Ϊ����ϵԭ�㣬����ϵ
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));    //ROI��������
	Mat q1(magnitudeImage, Rect(cx,0, cx, cy));    //����
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));   //����
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));  //����
	//��������
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//����������
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//����������


	namedWindow("Ƶ��", WINDOW_FREERATIO);
	imshow("Ƶ��", magnitudeImage);




	waitKey();
	return 0;

}


