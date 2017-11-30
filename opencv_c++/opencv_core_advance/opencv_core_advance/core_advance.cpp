//#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
//#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


void creattable(Mat &table, uchar val);

int main()
{
	Mat table;
	creattable(table, 10);
	cout << table;
	
	Mat img = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\chunxia.jpg");
	//����ͼ��
	Mat img_out;
	//�����洢ͼ��
	double time0 = static_cast<double>(getTickCount()); //��¼��ʼʱ��
	LUT(img, table, img_out);
	//look up table
	imshow("������ɫ�ռ��", img_out);
	time0 = (double(getTickCount())-time0)/getTickFrequency(); //����Ƶ�ʿ��������
	cout << "LUT��ʱ���ǣ�" << time0 << "��" << endl;
	waitKey();
	return 0;
}


//------------���������ұ�--------------
//  �����ǳ���256�ײ��ұ�����Ϊval-----
void creattable(Mat &table, uchar val)
{
	table.create(1, 256, CV_8UC1);
	uchar *p = table.data;
	//ָ������ȽϿ�
	for(int i=0;i<256;i++)
	{
		p[i] = i / val * val;   
	}
}


