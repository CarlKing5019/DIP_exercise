//�������ܽ��˱���ͼ�����ص����ַ����ֱ���ָ�룬�������Ͷ�̬��ַ����
//2017��5��14����ͨ��


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

void ColorReduce_C(Mat img_input, Mat &img_output, int div);
void ColorReduce_STL(Mat &img_input, Mat &img_output, int div);
void ColorReduce_AT(Mat &img_input, Mat &img_output, int div);


//-----------����������ڡ�----------------------
//	�������  main����
//------------------------------------------------

int main()
{
	Mat img_input = imread("C:\\Users\\zh_xing\\Desktop\\opencv\\chunxia.jpg");
	Mat img_output(img_input.rows, img_input.cols, img_input.type());
	//ԭ����һ��ͼƬ�����Ǿ�����û��ָ��
	imshow("ԭͼ", img_input);
	

	ColorReduce_C(img_input, img_output, 10);
	imshow("c���ʼ�ɫ��ͼ��",img_output);
	ColorReduce_STL(img_input, img_output, 50);
	imshow("���������ʼ�ɫ��ͼ��", img_output);
	ColorReduce_AT(img_input, img_output, 100);
	imshow("AT���ʼ�ɫ��ͼ��", img_output);
	waitKey();
	return 0;

}







//------------���Ӻ���ԭ�Ͳ��֡�-----------------
//		�Ӻ���ԭ�Ͷ���
//-----------------------------------------------



//-----------����ָ��������ء�------------------
void ColorReduce_C(Mat img_input, Mat &img_output, int div)
 //�����img_output�����ñز����٣���Ϊ���ֻ���βΣ��Ͳ��ܹ��Դ�������
//	��ַ�ı������޸ģ�һ��ʼ����д�˾Ͳ��ԣ����Ҫ�ں������޸Ĳ�����ֵ�����������ðѵ�ַ������
{	
	img_output = img_input.clone();  //����ʵ�ε���ʱ����
	int rowNum = img_output.rows;  //����
	int colNum = img_output.cols*img_output.channels();  //��*ͨ��=ÿһ��Ԫ����
	cout << rowNum;
	cout << colNum;

	for (int i = 0; i < rowNum; i++)
	{
		uchar*data = img_output.ptr<uchar>(i); //���ÿ�е��׵�ַ
		for (int j = 0; j < colNum; j++)
		{
			data[j] = (data[j] / div)*div;     //���д�����ɫ����
		}
	}
		//�������
}


//----------------���õ������������ء�-----------------------
//�����û��ô����������STL֮���ٻ������°�-----------------
void ColorReduce_STL(Mat &img_input, Mat &img_output, int div)
{
	img_output = img_input.clone();
	Mat_<Vec3b>::iterator it = img_output.begin<Vec3b>();
	//��ʼλ�õĵ�����
	Mat_<Vec3b>::iterator itend = img_output.end<Vec3b>();
	//��ֹλ�õĵ�����

	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div*div;
		(*it)[1] = (*it)[1] / div*div;
		(*it)[2] = (*it)[2] / div*div;

	}
}


//----------------���á���̬��ַ���㡱�������ء�-----------------------
//		������ˣ����϶����ص���ʶ��ͨ������������---------------------
void ColorReduce_AT(Mat &img_input, Mat &img_output, int div)
{
	img_output = img_input.clone();     //����ʵ�ε���ʱ����
	int row_Num = img_output.rows;
	int col_Num = img_output.cols;
	//�������
	for (int i = 0; i < row_Num; i++)
	{
		for (int j = 0; j < col_Num; j++)
		{
			img_output.at<Vec3b>(i, j)[0] = img_output.at<Vec3b>(i, j)[0] / div*div;
			img_output.at<Vec3b>(i, j)[1] = img_output.at<Vec3b>(i, j)[1] / div*div;
			img_output.at<Vec3b>(i, j)[2] = img_output.at<Vec3b>(i, j)[2] / div*div;
			//��������ͨ��
		}
	}
}