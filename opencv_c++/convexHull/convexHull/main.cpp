#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{

	Mat image(600, 600, CV_8UC3);
	RNG &rng = theRNG();
	while (1) 
	{
		char key;
		int count = (unsigned)rng % 100 + 3;
		count = 55;
		
		vector<Point> points;

		for (int i = 0;i < count;i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.rows * 3 / 4);
			point.y = rng.uniform(image.cols / 4, image.rows * 3 / 4);
			points.push_back(point);
			//�����������������POINTS��׷��һ�����ݣ�Ҳ���ǵ㼯�ĵ�����һ����
		}

			
			vector<int> hull;
			convexHull(Mat(points), hull, true);

			//���Ƹ�����
			image = Scalar::all(255);
			imshow("͹��", image);
			for (int i = 0;i < count;i++)
			{
				circle(image, points[i], 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED);

			}

			//����͹���ıߣ���Ȼ��һ��һ���߻��Ƶģ�Ϊë�������һ��������
			Point point0 = points[hull[(int)hull.size() - 1]];  //���һ���㡣
			for (int i = 0;i < (int)hull.size();i++)
			{
				Point point = points[hull[i]];
				line(image, point0, point, Scalar(0, 0, 255), 3);
				point0 = point;
			}
			imshow("͹��", image);
			
			key = (char)waitKey();
			if (key = 'q' || key == 'Q')
				break;
			//���break�����٣�Ҫ���ͻ���ѭ�����Ϳ�������������͹���ˡ�

		}
	waitKey();
	return 0;

	}
	