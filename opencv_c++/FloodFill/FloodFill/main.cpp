//��ˮ�����Գ���
//zhxing
//2017-06-03 16:03:05    ���Ի���˳������Ϊ�����Լ��õģ���Ż�������Сʱ��ʱ�䡣
//�м�cvtcolor�ĺ����ֳ�����һЩ���⣬���ϴ�˫���˲�������һ��������Ҳ��֪�����������������
//����������һ�����Ա�����ûʲô�����ˣ�˵�������������Ҳ���˺ü���Сʱ��


#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//--------------��ȫ�ֱ���������--------------------
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;  //ԭͼ��Ч��ͼ���Ҷ�ͼ����ģͼ
int g_nFillMode = 1;      //��ˮ����ģʽ
int g_nlow = 20, g_nUp = 20;  //����������ֵ
int g_nConnectivity = 4;     //floodFill������ʶ���ڰ�λ����ֵͨ
int g_bIsColor = true;			 //�Ƿ�Ϊ��ɫͼ�ı�ʶ��
bool g_bUserMask = false;   //�Ƿ���ʾ��Ĥ���ڵı�ʶ��
int g_nNewMaskVal = 255;    //�µ����»��Ƶ�����ֵ

//----------------�����ص�������--------------------
static void onMouse(int event, int x, int y, int, void *)
{
	if (event != EVENT_LBUTTONDOWN)    //���û�б�����
	{
		return;
	}
	Point seed = Point(x, y);
	int low = (g_nFillMode == 0 )? 0 : g_nlow;  
	int up = (g_nFillMode == 0 )? 0 : g_nUp;
	//�շ�Χ����ˮ�������ѡ��0�൱�ڲ����
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	//��ʶ��0-7Ϊg_nConnectivity��8-15λΪg_nNewMaskVal������8Ϊ��ֵ��16-23λΪ FLOODFILL_FIXED_RANGE����0������һλ��fiilmodeѡ��

	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;   //�������һ����ɫֵ
	cout << "color:"<<r << g << b<<endl;
	Rect ccomp;   //�����ػ��������С���α߽�
	Scalar newVal = (g_bIsColor==1) ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
	//��ͼ��ģʽ����ɫģʽ��ѡ��Scalar(b, g, r),�Ҷ�ģʽѡ��Scalar(r*0.299 + g*0.587 + b*0.114)
	Mat dst = (g_bIsColor==1) ? g_dstImage : g_grayImage;
	//Ŀ��ͼ��ֵ�������ǲ�ɫ���ǻҶ�ȡ����g_bIsColor

	int area;     //ͳ�Ʊ��������ظ�����FLOODFILL�ķ���ֵ�������,������е�С��,int�Ŷ���λ
	if (g_bUserMask)   //ʹ����Ĥ
	{
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(low, low, low), Scalar(up, up, up), flags);
		imshow("mask", g_maskImage);
	}
	
	else      //��������Ĥ
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(low, low, low), Scalar(up, up, up), flags);
	}
	imshow("Ч��ͼ", dst);
	cout <<area << "�����ر����»���" << endl;
}


int main()
{
	g_srcImage = imread("xyjy.jpg");
	imshow("ԭͼ", g_srcImage);
	g_srcImage.copyTo(g_dstImage);     //ԭͼ��ֵ��Ŀ��ͼ����ͬ����Ҳһ�����ơ�
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);    //ת���Ҷ�ͼ
	imshow("", g_grayImage);
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);
	//����ԭʼͼ��ĳߴ紴����Ĥͼ��
	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);
	
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nlow, 255, 0);
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nUp, 255, 0);
	//����������
	setMouseCallback("Ч��ͼ", onMouse, 0);
	//���ص�����

	while (1)
	{
		imshow("Ч��ͼ", g_bIsColor ? g_dstImage : g_grayImage);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "�����˳�" << endl;
			break;
		}
		switch (char(c))
		{
		case '1':
			if (g_bIsColor)   //��ԭͼΪ��ɫ����ת���ɻҶ�ͼ��������Ĥ����Ԫ����0
			{
				cout << "���̡�1�������£��л���ɫ�Ҷ�ģʽ����ǰ��������ɫ�л��ɻҶ�ģʽ" << endl;
				cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;   //��ʶ����0����ʾ��ǰΪ�Ҷ�ͼ��
			}
			else
			{
				cout << "����1�����£���ǰ�ӻҶȲ�ɫת��Ϊ�Ҷ�" << endl;
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;      

			}
			break;
		case '2':
			if (g_bUserMask)
			{
				destroyWindow("mask");
				g_bUserMask = 0;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUserMask = 1;
			}
			break;
		case '3':
			cout << "����3�����£��Ҷ�ԭʼͼ��" << endl;
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':
			cout << "����4�����£�ʹ�ý��䣬�̶���䷶Χ���" << endl;
			g_nFillMode = 1;
			break;
		case '5':
			cout << "����5�����£�ʹ�ý��䣬������Χ������ˮ���" << endl;
			g_nFillMode = 2;
			break;
		case '7':
			cout << "����7�����£�������ʶ���Ͱ�λ����4����" << endl;
			g_nConnectivity = 4;
			break;
		case '8':
			cout<< "����7�����£�������ʶ���Ͱ�λ����8����" << endl;
			g_nConnectivity = 8;
			break;
		}
	}

	return 0;
	
}