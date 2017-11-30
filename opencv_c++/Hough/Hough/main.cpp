#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat srcImage = imread("1.jpg");   
	imshow("ԭͼ", srcImage);
	Mat midImage, dstImage;    //��ʱ������Ŀ��ͼ

	//Canny(srcImage, midImage, 40, 120, 3);
	//imshow("canny", midImage);
	//cvtColor(midImage, dstImage,COLOR_GRAY2BGR);   //�����ǰѵ�ͨ����ת��Ϊ��ͨ���ģ�����R=G=B�����Ի��ǻ�ɫ��
	//vector<Vec2f> lines;
	
	//---------------------------------------------------------------------

	//HoughLines(midImage, lines, 1, CV_PI / 180, 150,0,0);   //ע������Ҫ�������8λ������ͼ��ֻ��0��255����ֵ
	////���⣬hough�任�Ժ��������ֵ�ǳ����У��ǳ�������죬����ѡ����ֵ��ʱ��Ҫ�ԡ����Ա�׼����任���Ǻ�ʵ�á�
	////cout<<format(lines,Formatter::FMT_MATLAB);    //��ķֱ���r��theta�������������
	//
	//imshow("dstImage", dstImage);

	//for (int i = 0; i < lines.size(); i++)
	//{
	//	float rho = lines[i][0];
	//	float theta = lines[i][1];
	//	Point pt1, pt2;
	//	double a = cos(theta), b = sin(theta);
	//	double x0 = a*rho, y0 = b*rho;
	//	pt1.x = cvRound(x0 + 1000 * (-b));
	//	pt1.y = cvRound(y0 + 1000 * (a));
	//	pt2.x = cvRound(x0 - 1000 * (-b));
	//	pt2.y = cvRound(y0 - 1000 * (a));

	//	line(dstImage, pt1, pt2, Scalar(0, 0, 255),1,LINE_AA);

	//	
	//}

	//�����Ǳ�׼����任��ʹ��-----------------------------------------------------------

	//---------------------------------------------------------
	//vector<Vec4i> lines1;

	//HoughLinesP(midImage, lines1, 1, CV_PI / 180, 80, 20, 5);
	//for (int i = 0; i < lines1.size(); i++)
	//{
	//	Point pt1, pt2;
	//	pt1.x = lines1[i][0];
	//	pt1.y = lines1[i][1];
	//	pt2.x = lines1[i][2];
	//	pt2.y = lines1[i][3];

	//	line(dstImage, pt1, pt2, Scalar(0, 0, 255));
	//}
	//--------------------�������ۼƸ��ʻ���任�����������Щ

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	
	imshow("gray", midImage);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
	//Ϊʲôһ��Ҫ��һ����˹��
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 2, 20, 100, 200, 0, 0);  //�ݶȷ�
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center;
		center = Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(srcImage, center, 3, Scalar(0, 0, 255), -1);   //��ʵ��Բ�ģ������ؿ�
		circle(srcImage, center, radius, Scalar(0, 0, 255), 3);  //��Բ��3���ؿ�
	}

	imshow("HoughCircle", srcImage);
	imwrite("c.jpg", srcImage);
	waitKey();
	return 0;
}