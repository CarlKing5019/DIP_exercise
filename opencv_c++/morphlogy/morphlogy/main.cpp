
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;   //�����ռ�������������µ������Ϳ��Բ�����cv::ǰ׺����ֱ��ʹ�á�
using namespace std;


//--------------------������������------------------------
Mat	img, img_after;
int on_TrackerBarChose = 0;    //ѡ�����ͻ��߸�ʴ
int on_ElementSize = 3;       //ѡ���ں˳ߴ�

//-------------------������������------------------------
void process();
void on_TrackBarChose(int, void*);
void on_ElementSizechange(int, void*);

int main()
{
	img = imread("chunxia.jpg");   
	//Mat img = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\a.jpg"); 
	//���ﲻ�����¶���Mat,���������ڴ����c++������������±����壬�������Mat���ܼӣ��������Mat���붨��
	//��ȫ�ֱ���������Ϊ�ص������������������⡣
	namedWindow("ԭͼ");
	imshow("ԭͼ", img);
	
	
	namedWindow("��Ч��ͼ��");
	Mat element=getStructuringElement(MORPH_RECT, Size(on_ElementSize+1, on_ElementSize+1));
	//���element�ͻص�������element���������¶�����������Ϊ���Ե������ڲ�����ͻ��
	erode(img, img_after, element);
	imshow("��Ч��ͼ��", img_after);

	createTrackbar("erode(0)_or_dilate(1)", "��Ч��ͼ��", &on_TrackerBarChose, 1, on_TrackBarChose);
	createTrackbar("ElementSize", "��Ч��ͼ��", &on_ElementSize, 25, on_ElementSizechange);
	
	while(char(waitKey(1))!='q'){}
	return 0;
}

void process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(on_ElementSize+1, on_ElementSize+1));
	if (on_TrackerBarChose ==0)
	{
		erode(img, img_after, element);
	}
	else
	{
		dilate(img, img_after, element);
	}
	imshow("��Ч��ͼ��", img_after);
}

void on_TrackBarChose(int, void*)
{
	process();
}

void on_ElementSizechange(int, void*)
{
	process();
}