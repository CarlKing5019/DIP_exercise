//�����Ŀ��Ҫ�������ֵģ��Ӷ��������Ӵ�ͼ����Ҳ��һ����ˣ���ǰҲ��opencv��д�Ķ���ЩС�ű���
//
//�����Ŀ����Ҫ�������ڶ�9*9�������ṩ�⣬Ϊʲô֮����д�������Ϊ������һЩ�ο����ϣ��м������������ֻ����������ˣ�
//2018/3/1


#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv\ml.h>      //knnͷ�ļ�
#include<iostream>
#include<string>
#include<vector>

using namespace cv;
using namespace std;
using namespace cv::ml;

void getTrainImg(vector<vector<Mat>>  &TrainImgMat);

int main()
{
	Mat srcImg;
	Mat Img;
	Mat Img_gray; 
	Mat Img_g;
	
	srcImg = imread("2.jpg",0);
	srcImg.copyTo(Img_gray);
	//cvtColor(Img, Img_gray,COLOR_BGR2GRAY);
	
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(Img_gray, Img_g, -1, kernel);
	threshold(Img_g, Img_g, 150, 255, THRESH_BINARY_INV);         //��ֵ��ֵ���������ֵ�Լ�ѡ,�����Ƿ��ŵģ���Ϊһ���ǰ�ֽ����

	//imshow("��ֵ��", Img_g);

	auto kernel_dilate = getStructuringElement(MORPH_CROSS, Size(3, 3));    //���ͺ�
	
	dilate(Img_g, Img_g, kernel_dilate);           //���ͣ���ֹ�ж���
	dilate(Img_g, Img_g, kernel_dilate);

	vector<vector<Point>> contours;           
	vector<Vec4i> hierarchy;
	imshow("thres", Img_g);
	findContours(Img_g,contours, hierarchy, RETR_TREE,CHAIN_APPROX_SIMPLE);     

	cout <<"����⵽�����ĸ���\t"<<contours.size() << endl;

	
	//--------------����ȡͼƬ�е����ּ���Ӧλ�á�----------------------
	vector<vector<Point>> num_contours;
	vector<Rect>  RecOfNum;
	Rect tmp;
	vector<pair<Point, Rect>>  IndexAndPos;
	auto Round = boundingRect(contours[0]);     //���Ե

	/*cout << "���\t" << Round.width << endl;
	cout << "�߶�\t" << Round.height << endl;*/

	rectangle(srcImg, Round, Scalar(255, 0, 255));
	namedWindow("co", 2);
	//imshow("co", Img);

	int index_x;
	int index_y;
	Point index_xy;
	

	vector<Mat> Numbers;
	vector<Point>  PosOfNum;

	for (int i = 0; i < hierarchy.size(); i++)
	{
		if (hierarchy[i][3] == 0&&hierarchy[i][2]!=-1)    
		//��������0�������Ļ�������С���Σ���������������������������
		{
			
			num_contours.push_back(contours[hierarchy[i][2]]);
			tmp = boundingRect(contours[hierarchy[i][2]]);
			
			//ÿ�����ֵ�����,ת��Ϊ���꣬���巽����һ��������ķ���������֪����Ч��
			index_x = double((tmp.x + tmp.width / 2))/Round.width*9;
			index_y = double((tmp.y + tmp.height / 2)) / Round.height * 9;
			index_xy.x = index_x;
			index_xy.y = index_y;
			cout << index_x << "--" << index_y << endl;

			IndexAndPos.push_back(make_pair(index_xy, tmp));    //����Ͷ�Ӧ�ľ���
			
			Mat ImgROI;
			resize(srcImg(tmp), ImgROI, Size(20, 20));
			
			Numbers.push_back(ImgROI);            //���֣�resize��20x20
			PosOfNum.push_back(index_xy);         //��Ӧ��λ�ã����к��У�

			//imwrite("C:\\Users\\zhxing\\Desktop\\DIP_exercise\\opencv_c++\\ShuDu\\ShuDu\\img\\"+to_string(index_xy.x) + "_"+to_string(index_xy.y)+".jpg", ImgROI);
			//�����ã�����ȷʵ���Եõ�λ�ö�Ӧ��ͼ��

			//rectangle(srcImg, tmp, Scalar(255, 255, 0));
			
			RecOfNum.push_back(tmp);
		}
	}

	Mat TestData;
	for (auto nums:Numbers)
	{
		TestData.push_back(nums.reshape(0, 1));
	}
	imshow("test",TestData);
	TestData.convertTo(TestData, CV_32F);
	cout <<"������������"<<TestData.type() << endl;
	//cout << "�������ݴ�С--ӦΪ" << Point( Numbers.size(),400) <<"\tʵ���ǣ�"<<TestData.size<<endl;

	



	//namedWindow("co", 2);
	imshow("co", srcImg);

	cout << "��⵽�����ֵ���Ŀ�ǣ�\t" << num_contours.size() << endl;
	

	//-----������ѵ�����ݡ�-------------------------
	vector<vector<Mat>>  TrainImgMat(10,vector<Mat>());
	getTrainImg(TrainImgMat);
	cout <<"����Ϊ"<< TrainImgMat[0][0].type() << endl;
	

	Mat TrainImg(Size(200, 200), TrainImgMat[0][0].type());
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			TrainImgMat[i][j].copyTo(TrainImg(Rect(i*20,j*20,20,20)));
		}
	}
	//imshow("test", TrainImg);


	Mat trainData;
	Mat Label;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			trainData.push_back(TrainImgMat[j][i].reshape(0,1));
			imshow(" s", TrainImgMat[j][i]);
			Label.push_back(i);
		}
	}

	imshow("das",trainData);
	cout << "����\t" << trainData.type() << endl;
	//ת���ɸ��㱸��
	trainData.convertTo(trainData, 5);
	cout <<"����\t"<< trainData.type() << endl;

	
	
	//---------��knn���������ã�k=3,����򿪡�-----------------
	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, Label);          //

	Ptr<ml::KNearest> knn = ml::KNearest::create();
	knn->setDefaultK(7);        
	knn->setIsClassifier(true);
	knn->train(tData);

	vector<int>  PredicrRes;
	for (int i = 0; i < TestData.rows; i++)
	{
		Mat tmp = TestData.row(i);
		int response = knn->predict(tmp);
		PredicrRes.push_back(response);
		cout << response <<"\t"<<i<< endl;

	}

	cout << "size" << PredicrRes.size() << endl;
	
	for (int i = 0; i < PredicrRes.size(); i++)
	{
		
		
		imwrite(".\\pre\\" + to_string(PredicrRes[i]) + ".jpg",Numbers[i]);
		
	}




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
		tmp_srcImg = imread(".\\TrainImg\\" + to_string(i) + ".jpg",0);     
		tmp_srcImg.copyTo(tmp_Img_thresh);        //����һ�ݣ���ֵ������ԭͼ������
		
		
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
		//���򣬰��վ��ΰ�ΧȦ��x��������
		sort(img0_9.begin(), img0_9.end(), [](Rect &a, Rect &b)->bool {return a.x < b.x; });     
		
		
		for (int k = 0; k < img0_9.size(); k++)
		{
			Mat img20;
			
			resize(tmp_srcImg(img0_9[k]), img20, Size(20, 20));
			TrainImgMat[i].push_back(img20);
			
		}
		//����ڴ�ռ䣬�´���
		cons.clear();
		hies.clear();
		img0_9.clear();	
	}
}