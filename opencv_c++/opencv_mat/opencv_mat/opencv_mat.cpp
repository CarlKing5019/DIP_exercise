//----------opencv���ݽṹѧϰ���Գ���-------------
// zhxing
// 2017/5/13


#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;


int main()
{
	//------------��1.���ù��캯����----------------------------------
	Mat m(2, 2, CV_8UC3, Scalar(0, 0, 255));  //���ù��캯������mat
	
	//------------��2.���ó�Ա������---------------------------------
	Mat m1;
	m1.create(2,2,CV_8UC3);         //����create����������һ����Ա����

	//------------��3.���þ�̬��Ա������-------------------------------
	Mat E = Mat::eye(3, 3, CV_8UC1);    //������ľ�̬��Ա����������ǵ�λ��
	//Mat E = Mat::ones(3, 3, CV_8UC1);       //���ֶ��巽ʽ��matlab��Щ���ƶ���һЩ�򵥵ľ���
	//Mat E = Mat::zeros(3, 3, CV_8UC1);
	
	//------------��4.ֱ�Ӷ�С������ж��塿---------------------------
	Mat c = (Mat_<double>(3, 3) << 2, 3, 4, 5, 6, 7, 8, 9, 1);   
	// �����д���������漴�ɣ�д���������ͺ�������
	
	//-------------��5.Ϊ�Ѵ��ڵĶ��󴴽���Ϣͷ��---------------------
	Mat c_row1 = c.row(1).clone();       //���Ѵ��ھ����һ�����������¹���һ������
	//--------------�������ĺ���Ҳ��ֹ��ô���֣������õ��ٲ�-------------
	
	//-------------------��opencv���ʽ���������ķ�����-------------------
	Mat r(5, 5, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));       //�ȳ�ʼ��һ������
	//opencv���ṩ������ʽ������ķ���
	cout << "Ĭ�Ϸ��" << endl << r << endl;
	cout << "python���" << endl << format(r, Formatter::FMT_PYTHON) << endl;
	cout << "���ŷ��" << endl << format(r, Formatter::FMT_CSV) << endl;
	cout << "NUMPY���" << endl << format(r, Formatter::FMT_NUMPY) << endl;
	cout << "matlab���" << endl << format(r, Formatter::FMT_MATLAB) << endl;
	cout << "c���Է��" << endl << format(r, Formatter::FMT_C) << endl;
	//Զ��ֹ�⼸�ַ�񣬱Ƚ�����python��matlab���ǱȽϺÿ��ģ�matlab����Ϊ�����˰�
	

	//��ά��Ķ���
	Point2d p1(5, 5);    //���ù��캯��֮�䶨��
	//��ά��Ķ���         
	Point3f p2(3, 3, 3); //���ù��캯��
	//������ʵ���кܶ�����Զ��壬�����õ���ʱ���ٲ�ɣ�����f�ĳ�i����d�Ϳ��Դ���ͬ����������
	//������ά�ĵ����matȥ�����
	
	cout << p1 << endl << p2 << endl;

	Size s(1, 3);
	cout << s.area() << "," << s.height << s.width << endl;
	//size�����г�Ա������������������Ҳ���ڲ����ݳ�Ա��͸�

	
	return 0;            //��������棬����return 0����̨Ҳ��һ����������Ctrl+F5ֱ�����л����ԡ�
}