#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<algorithm>
#include<vector>
//��Сֵ�˲����ø�ʴ������
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size);

//BGRͨ������Сֵ
cv::Mat min_BGR(cv::Mat &src_img);

//�����˲�
cv::Mat guide_filter(cv::Mat &img, cv::Mat &p, int r, double eps);

//�����������ͼ��V1�͹���ֵ
void getV1(cv::Mat &m, int r, double eps, double w, double maxV1);