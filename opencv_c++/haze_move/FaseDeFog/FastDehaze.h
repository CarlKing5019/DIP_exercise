#pragma once


#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<algorithm>

#include<vector>


using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size);
cv::Mat min_BGR(cv::Mat &src_img);
cv::Mat max_BGR(cv::Mat &src_img);
Mat getLx_A(Mat &M_min, Mat &img, double p, int kernel_size, double &A);
Mat FastDehaze(Mat &Img, const double p,const int kernel_size,double eps=0.0001);


//��Сֵ�˲���
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size)
{
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * kernel_size - 1, 2 * kernel_size - 1));
	cv::erode(src_img, res_img, element);
	//cv::imshow("dark_channel", res_img);
}


//��ȡͨ������Сֵ����ͨ��
cv::Mat min_BGR(cv::Mat &src_img)
{
	int rows = src_img.rows;
	int cols = src_img.cols;

	cv::Mat res = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
	//creat one channel image to save min_rgb
	int channel_num = src_img.channels();
	/*std::cout << channel_num << std::endl;*/
	if (channel_num <= 1)
	{
		std::cout << "channel is just 1, return zeros matrix!" << std::endl;
		return res;
	}


	for (int i = 0; i < rows; i++)
	{
		uchar *img_adress = src_img.ptr<uchar>(i);   //��ǰ�еĵ�ַ
		uchar *res_adress = res.ptr<uchar>(i);       //��ǰ�еĵ�ַ
		for (int j_i = 0, j_r = 0; j_r < cols, j_i<cols*channel_num; j_i += channel_num, j_r++)
		{
			res_adress[j_r] = std::min(std::min(img_adress[j_i], img_adress[j_i + 1]), img_adress[j_i + 2]);
		}

	}
	//std::cout << "done!"<<std::endl;
	return res;
}

cv::Mat  min_BRG_32F(cv::Mat &img_32F)
{
	int rows = img_32F.rows;
	int cols = img_32F.cols;

	Mat res = Mat::zeros(Size(cols,rows), CV_32FC1);
	//cout << img_32F.size()<<endl;
	//cout << res.size() << endl;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
	
			res.at<float>(i, j) = std::min(img_32F.at<Vec2f>(i, j)[0], img_32F.at<Vec2f>(i, j)[1]);
		}
	}
	return res;
}

//��ȡͨ�������ֵ����ͨ����
cv::Mat max_BGR(cv::Mat &src_img)
{
	int rows = src_img.rows;
	int cols = src_img.cols;

	cv::Mat res = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
	//creat one channel image to save min_rgb
	int channel_num = src_img.channels();
	/*std::cout << channel_num << std::endl;*/
	if (channel_num <= 1)
	{
		std::cout << "channel is just 1, return zeros matrix!" << std::endl;
		return res;
	}

	for (int i = 0; i < rows; i++)
	{
		uchar *img_adress = src_img.ptr<uchar>(i);   //��ǰ�еĵ�ַ
		uchar *res_adress = res.ptr<uchar>(i);       //��ǰ�еĵ�ַ
		for (int j_i = 0, j_r = 0; j_r < cols, j_i<cols*channel_num; j_i += channel_num, j_r++)
		{
			res_adress[j_r] = std::max(std::max(img_adress[j_i], img_adress[j_i + 1]), img_adress[j_i + 2]);
		}

	}
	//std::cout << "done!"<<std::endl;
	return res;
}

Mat getLx_A(Mat &M_min,Mat &img, double p,int kernel_size,double &A)
{
	Mat M_minfilter;

	blur(M_min, M_minfilter, Size(kernel_size, kernel_size));    //��ֵ�˲�
	Scalar m_av = cv::mean(M_min);              //��ͨ���ľ�ֵ������Ӧ���ǶԵ�

	double m_ave = m_av[0]/255.0;                 //��ֵ������һ��Scalar,ȡ��һ������
	double m = std::min(m_ave*p, 0.9);         //ȡ����������Сֵ
	//cout << "m" <<m<< endl;             //����û���⣬���Թ���
	//����ļ���ǣ������ม�����㣬��������ת����32F������
	
	Mat M_minfilter_32f, M_min_32f;
	M_min.convertTo(M_min_32f, CV_32F);
	M_minfilter.convertTo(M_minfilter_32f, CV_32F);
	//�ĳ�32F����ȥ��������0.9��p*m_av����Сֵ
	
	//cout <<"��Сֵ�˲���" <<M_minfilter_32f(Range(0, 9), Range(0, 9));
	//cout << "��Сֵ����" << M_min_32f(Range(0, 9), Range(0, 9));
	//cout << M_minfilter_32f(Range(0, 9), Range(0, 9))*m;
	
	vector<Mat> M_vector = { M_minfilter_32f*m,M_min_32f };
	Mat M_merge;
	merge(M_vector, M_merge);
	Mat res = min_BRG_32F(M_merge);     //ר�������������ȡ��Сֵ
	//cout <<"res"<< res(Range(0, 9), Range(0, 9))<< endl;   //�������Ҳ����ȷ�ģ�û����

	Mat max_img = max_BGR(img);
	double max_max_img, max_ave_img;
	minMaxLoc(max_img, NULL, &max_max_img, NULL, NULL);
	minMaxLoc(M_minfilter, NULL, &max_ave_img, NULL, NULL);
	A = 0.5*(max_max_img + max_ave_img);
	return res;
}


Mat FastDehaze(Mat &Img, const double p,const int kernel_size,double eps)
{
	Mat Lx, ImgDark;
	ImgDark = min_BGR(Img);
	Mat ImgDark_32f,Img_32F;
	Img.convertTo(Img_32F, CV_32F);
	ImgDark.convertTo(ImgDark_32f, CV_32F);
	double A;
	Lx = getLx_A(ImgDark, Img, p, kernel_size, A);
	
	//cout <<"A:" <<A << endl;
	//cout << Lx(Range(0,9),Range(0,9)) << endl;

	vector<Mat> Img_split;
	if (Img_32F.channels() != 3)
		cout << "�����ǲ�ɫͼ��" << endl;
	else 
		split(Img_32F, Img_split);
	
	Mat fenmu = 1 - Lx / (A+eps);

	vector<Mat> Fenzi;
	Fenzi.push_back(Img_split[0] - Lx);
	Fenzi.push_back(Img_split[1] - Lx);
	Fenzi.push_back(Img_split[2] - Lx);

	

	vector<Mat> Img_split_dehaze;
	Mat div_tmp;

	for (int i = 0; i < 3; i++)
	{
		/*cv::divide(Fenzi[i], fenmu, div_tmp);
		Img_split_dehaze.push_back(div_tmp);*/        
		
		//һ��ʼ��ע�͵�������ˣ�����ǰ��һ��һ����ŷ��֣�������֪�����������⣬�ĳ�new����Ϳ����ˣ����棡

		Mat *tmp = new Mat;
		cv::divide(Fenzi[i], fenmu, *tmp);
		Img_split_dehaze.push_back(*tmp);
		delete tmp;
	}
	
	Mat res_32f, res;
	merge(Img_split_dehaze, res_32f);
	res_32f.convertTo(res, CV_8UC3);
	return res;
}



