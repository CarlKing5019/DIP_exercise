#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<math.h>

using namespace std;
using namespace cv;

//-----------------���Ӻ���������-----------------------------------
void DrawEllipse(Mat img, double angle);   //�Զ��廭��Բ����,����ͼ��ͽǶ�
void DrawFilledCircle(Mat img, Point center);  //�Զ��廭ʵ��Բ������Բ�ĺ�ͼ��
void Drawploy(Mat img);      //������Σ����ﻭ�������ΰ�

//----------------���궨�塿----------------------------------------
#define WINDOW_WIDTH 600


int main() 
{
	Mat img(WINDOW_WIDTH, WINDOW_WIDTH,CV_8UC3,Scalar(120,120,120)); 
	//�����ɫ����ͼ
	DrawEllipse(img, 0);
	DrawEllipse(img, 45);
	DrawEllipse(img, 90);
	DrawEllipse(img,135);
	//����Բ
	DrawFilledCircle(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	//��ʵ��Բ
	Drawploy(img);
	imshow("ellipse", img);
	waitKey();
	
	return 0;
}


//------------------���Զ��������Բ��--------------
//---���Ʋ�ͬ�Ƕȵ���Բ-----------------------------
//--------------------------------------------------
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;  //�߿�2������
	int linetype = 8;   //����Ϊ8��8��ͨ��
	ellipse(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),   
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16), 
		angle, 0, 360, 
		Scalar(255, 0, 0), thickness);

}

//------------------���Զ������Բ��--------------
//- Ҫ�����Ҫ����λ���Լ�ͼ��-----------------------------
//--------------------------------------------------
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;   //�߿�-1����ʵ��
	int linetype = 8;
	circle(img, center, WINDOW_WIDTH / 32, Scalar(0, 255, 0), thickness, linetype);
	//�࿴����ԭ�ͣ���ʵ���ĺ����
}

// ------------------���Զ�����ƶ���Ρ�--------------
//---�������㻭��-----------------------------
//--------------------------------------------------
void Drawploy(Mat img)
{
	int linetype = 8;
	Point rookPoints[1][4];
	rookPoints[0][0] = Point(  WINDOW_WIDTH / 4,  WINDOW_WIDTH / 4);
	rookPoints[0][1] = Point( 3*WINDOW_WIDTH / 4,  WINDOW_WIDTH / 4);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 4);
	rookPoints[0][3] = Point(  WINDOW_WIDTH / 4, 3* WINDOW_WIDTH / 4);
	const Point *ppt[1] = {rookPoints[0]};
	int npt[] = { 4 };
	polylines(img, ppt, npt,1,true,Scalar(0,255,0));
	
	//fillPoly(img, ppt, npt, 1, Scalar(0, 255, 0));
    //����ǻ�ʵ�ĵ�


}