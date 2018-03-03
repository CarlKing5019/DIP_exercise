//�����Ŀ��Ҫ�������ֵģ��Ӷ��������Ӵ�ͼ����Ҳ��һ����ˣ���ǰҲ��opencv��д�Ķ���ЩС�ű���
//
//�����Ŀ����Ҫ�������ڶ�9*9�������ṩ�⣬Ϊʲô֮����д�������Ϊ������һЩ�ο����ϣ��м������������ֻ����������ˣ�
//2018/3/1


#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<string>
#include<vector>

using namespace cv;
using namespace std;

void getTrainImg(vector<vector<Mat>>  &TrainImgMat);

int main()
{
	//Mat srcImg;
	//Mat Img;
	//Mat Img_gray; 
	//Mat Img_g;
	//
	//srcImg = imread("2.jpg");
	//srcImg.copyTo(Img);
	//cvtColor(Img, Img_gray,COLOR_BGR2GRAY);
	//
	//Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//filter2D(Img_gray, Img_g, -1, kernel);
	//threshold(Img_g, Img_g, 150, 255, THRESH_BINARY_INV);         //��ֵ��ֵ���������ֵ�Լ�ѡ,�����Ƿ��ŵģ���Ϊһ���ǰ�ֽ����

	//imshow("��ֵ��", Img_g);

	//auto kernel_dilate = getStructuringElement(MORPH_CROSS, Size(3, 3));    //���ͺ�
	//
	//dilate(Img_g, Img_g, kernel_dilate);           //���ͣ���ֹ�ж���
	//dilate(Img_g, Img_g, kernel_dilate);

	//vector<vector<Point>> contours;           
	//vector<Vec4i> hierarchy;
	//imshow("thres", Img_g);
	//findContours(Img_g,contours, hierarchy, RETR_TREE,CHAIN_APPROX_SIMPLE);     

	//cout <<"����⵽�����ĸ���\t"<<contours.size() << endl;

	///*for (auto h : hierarchy)
	//	cout << h << endl;*/

	//drawContours(Img, contours, -1, Scalar(0, 0, 255), 1);
	//

	////vector<vector<Point>>  rec_contours;
	////for (int i = 0; i < hierarchy.size(); i++)
	////{
	////	if (hierarchy[i][3] == 0)     //��������0�������Ļ�������С����
	////	{
	////		rec_contours.push_back(contours[i]);	
	////	}
	////}

	//vector<vector<Point>> num_contours;
	//vector<Rect>  RecOfNum;
	//Rect tmp;
	//vector<pair<Point, Rect>>  IndexAndPos;
	//auto Round = boundingRect(contours[0]);     //���Ե

	///*cout << "���\t" << Round.width << endl;
	//cout << "�߶�\t" << Round.height << endl;*/

	//rectangle(Img, Round, Scalar(255, 0, 255));
	//namedWindow("co", 2);
	//imshow("co", Img);

	//int index_x;
	//int index_y;
	//Point index_xy;
	//Mat ImgROI;

	//for (int i = 0; i < hierarchy.size(); i++)
	//{
	//	if (hierarchy[i][3] == 0&&hierarchy[i][2]!=-1)    
	//	//��������0�������Ļ�������С���Σ���������������������������
	//	{
	//		
	//		num_contours.push_back(contours[hierarchy[i][2]]);
	//		tmp = boundingRect(contours[hierarchy[i][2]]);
	//		
	//		//ÿ�����ֵ�����,ת��Ϊ���꣬���巽����һ��������ķ���������֪����Ч��
	//		index_x = double((tmp.x + tmp.width / 2))/Round.width*9;
	//		index_y = double((tmp.y + tmp.height / 2)) / Round.height * 9;
	//		index_xy.x = index_x;
	//		index_xy.y = index_y;
	//		cout << index_x << "--" << index_y << endl;

	//		IndexAndPos.push_back(make_pair(index_xy, tmp));    //����Ͷ�Ӧ�ľ���
	//		
	//		resize(srcImg(tmp), ImgROI, Size(20, 20));
	//		
	//		//imwrite("C:\\Users\\zhxing\\Desktop\\DIP_exercise\\opencv_c++\\ShuDu\\ShuDu\\img\\"+to_string(index_xy.x) + "_"+to_string(index_xy.y)+".jpg", ImgROI);
	//		//�����ã�����ȷʵ���Եõ�λ�ö�Ӧ��ͼ��

	//		rectangle(srcImg, tmp, Scalar(255, 255, 0));
	//		RecOfNum.push_back(tmp);
	//	}
	//}

	//


	////namedWindow("co", 2);
	//imshow("co", srcImg);

	//cout << "��⵽�����ֵ���Ŀ�ǣ�\t" << num_contours.size() << endl;
	
	
	vector<vector<Mat>>  TrainImgMat(10,vector<Mat>());
	getTrainImg(TrainImgMat);
	

	Mat TrainImg=Mat::zeros(Size(200,200), TrainImgMat[0][0].type());
	Mat img20x20;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			resize(TrainImgMat[i][j], img20x20, Size(20, 20));
			img20x20.copyTo(TrainImg(Rect(i*20,j*20,20,20)));
		}
	}
	imshow("test", TrainImg);

	waitKey();
	
	return 0;
}



//���ļ����е�ͼ����һ��ȡΪ���õ����ݸ�ʽ
void getTrainImg(vector<vector<Mat>>  &TrainImgMat)
{
	Mat tmp_srcImg;
	Mat tmp_Img_thresh;
	vector<vector<Point>> cons;
	vector<Vec4i>  hies;

	vector<Rect>  img0_9;
	for (int i = 0; i < 10; i++)
	{
		//���룬��ֵ��
		tmp_srcImg = imread(".\\TrainImg\\" + to_string(i) + ".jpg");
		cvtColor(tmp_srcImg, tmp_Img_thresh, CV_BGR2GRAY);
		threshold(tmp_Img_thresh, tmp_Img_thresh, 150, 255, CV_THRESH_BINARY_INV);
		//3*3ʮ������
		auto kernel=getStructuringElement(CV_SHAPE_CROSS, Size(3, 3));
		dilate(tmp_Img_thresh, tmp_Img_thresh, kernel);
		//��������
		findContours(tmp_Img_thresh, cons, hies, RETR_TREE, CHAIN_APPROX_SIMPLE);
		
		//ɸѡû�и�����������Ϊ���֣���������С��Χ����
		for (int j = 0; j < hies.size(); j++)
		{
			if (hies[j][3] == -1)
			{
				img0_9.push_back(boundingRect(cons[j]));
			}
		}
		cons.clear();
		hies.clear();

		//���򣬰��վ��ΰ�ΧȦ��x��������
		sort(img0_9.begin(), img0_9.end(), [](Rect &a, Rect &b)->bool {return a.x < b.x; });     
		
		for (int k = 0; k < img0_9.size(); k++)
		{
			TrainImgMat[i].push_back(tmp_srcImg(img0_9[k]));	
		}
		//����ڴ�ռ䣬�´���
		cons.clear();
		hies.clear();
		img0_9.clear();	
	}
}