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
#include<map>
#include<algorithm>


using namespace cv;
using namespace std;
using namespace cv::ml;

void getTrainImg(vector<vector<Mat>>  &TrainImgMat);
bool isPlace(int count, vector<vector<int>> &map);
void backtrace(int count, vector<vector<int>> &map, vector<vector<int>> &res);


int main()
{
	Mat srcImg;
	Mat Img;
	Mat Img_gray; 
	Mat Img_g;
	
	srcImg = imread("5.jpg",0);
	srcImg.copyTo(Img_gray);
	//cvtColor(Img, Img_gray,COLOR_BGR2GRAY);
	
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(Img_gray, Img_g, -1, kernel);
	threshold(Img_g, Img_g, 150, 255, THRESH_BINARY_INV);         //��ֵ��ֵ���������ֵ�Լ�ѡ,�����Ƿ��ŵģ���Ϊһ���ǰ�ֽ����

	imshow("��ֵ��", Img_g);

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
	

	int index_x;
	int index_y;
	Point index_xy;
	vector<Point> PosOfNum_true;
	

	vector<Mat> Numbers;
	vector<Point>  PosOfNum;
	vector<Point>  UpLeftPosOfNum;

	vector<Rect>  Pos;

	for (int i = 0; i < hierarchy.size(); i++)
	{
		Rect tmp;
		if (hierarchy[i][3] == 0)
		{
			Pos.push_back(boundingRect(contours[i]));
		}
	}
	
	//����y������һ��һ�Ŷ�����һ��

	sort(Pos.begin(), Pos.end(), [](Rect &a, Rect &b)->bool{return a.y < b.y; });
	cout << "С���εĸ�����" << Pos.size() << endl;

	vector<vector<Rect>> PosMat(9,vector<Rect>());
	int index = 0;
	for (int i = 0; i < 81; i+=9)
	{
		PosMat[index++].assign(Pos.begin() + i, Pos.begin() + i + 9);    //��ֵÿһ��
	}
	cout <<"pos��size��\t"<< PosMat.size() << endl;
	
	for (int i=0;i<9;i++)
	{
		sort(PosMat[i].begin(), PosMat[i].end(), [](Rect &a, Rect &b)->bool {return a.x < b.x; });  //ÿһ�а���x����
		cout << PosMat[i].size() << endl;
	}






	for (int i = 0; i < hierarchy.size(); i++)
	{
		if (hierarchy[i][3] == 0&&hierarchy[i][2]!=-1)    
		//��������0�������Ļ�������С���Σ���������������������������
		{
			
			num_contours.push_back(contours[hierarchy[i][2]]);
			tmp = boundingRect(contours[hierarchy[i][2]]);
			UpLeftPosOfNum.push_back(Point(tmp.x, tmp.y));
			//ÿ�����ֵ�����,ת��Ϊ���꣬���巽����һ��������ķ���������֪����Ч��
			index_x = double((tmp.x + tmp.width / 2))/Round.width*9;
			index_y = double((tmp.y + tmp.height / 2)) / Round.height * 9;
			index_xy.x = index_x;
			index_xy.y = index_y;
			
			
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
	
	TestData.convertTo(TestData, CV_32F);


	



	//namedWindow("co", 2);
	

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
	knn->setDefaultK(4);        
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



	//�ع���������
	vector<vector<int>> ShuDuMat(9,vector<int>());
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			ShuDuMat[i].push_back(0);

		}
	}
	for (int i = 0; i < PredicrRes.size(); i++)
	{
		ShuDuMat[PosOfNum[i].y][PosOfNum[i].x] = PredicrRes[i];
	}


	for (auto s : ShuDuMat)
	{
		for (auto t : s)
			cout << t << "  ";
		cout << endl;
	}

	
	for (auto s : PosOfNum)
		cout << s << endl;


	//ʶ����
	Mat srcImg_color;
	cvtColor(srcImg, srcImg_color, CV_GRAY2BGR);
	for (int i = 0; i < PredicrRes.size(); i++)
	{
		string text = to_string(PredicrRes[i]);
		cout << text << " ";
		putText(srcImg_color, text, UpLeftPosOfNum[i], FONT_ITALIC, 1, Scalar(0, 0, 255),1);
	}
	
	imshow("ԭͼ���ּ����", srcImg_color);

	vector<vector<int>>  res(9,vector<int>());
	backtrace(0, ShuDuMat,res);

	//����������
	cout << "������� :"<< endl;
	for (auto s : res)
	{
		for (auto t : s)
			cout << t << "  ";
		cout << endl;
	}


	Mat ResultImg;
	cvtColor(srcImg, ResultImg, CV_GRAY2BGR);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			string text = to_string(res[i][j]);
			putText(ResultImg, text, Point(PosMat[i][j].x, PosMat[i][j].y+15), FONT_ITALIC, 1, Scalar(0, 0, 255), 2);	
		}
		
	}

	imshow("���������", ResultImg);


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


bool isPlace(int count,vector<vector<int>> &map) {
		int row = count / 9;
		int col = count % 9;
		int j;
		//ͬһ��  
		for (j = 0; j < 9; ++j) {
			if (map[row][j] == map[row][col] && j != col) {
				return false;
			}
		}
		//ͬһ��  
		for (j = 0; j < 9; ++j) {
			if (map[j][col] == map[row][col] && j != row) {
				return false;
			}
		}
		//ͬһС��  
		int tempRow = row / 3 * 3;
		int tempCol = col / 3 * 3;
		for (j = tempRow; j < tempRow + 3; ++j) {
			for (int k = tempCol; k < tempCol + 3; ++k) {
				if (map[j][k] == map[row][col] && j != row && k != col) {
					return false;
				}
			}
		}
		return true;
	}
	


void backtrace(int count, vector<vector<int>> &map, vector<vector<int>> &res) {
		if (count == 81) {
			cout << "�����" << endl;
			for (int i = 0; i < 9; ++i) {
				for (int j = 0; j < 9; ++j) { 
					res[i].push_back(map[i][j]);
				}	
			}
			return;
		}
		int row = count / 9;
		int col = count % 9;
		if (map[row][col] == 0) {
			for (int i = 1; i <= 9; ++i) {
				map[row][col] = i;//��ֵ  
				if (isPlace(count, map)) {//���Է�  
					backtrace(count + 1, map,res);//������һ��  
				}
			}
			map[row][col] = 0;//����  
		}
		else {
			backtrace(count + 1,map,res);
		}
	}
