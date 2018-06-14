
#include"enhance_and_denoising.h"



void enhance1(cv::Mat src_img, cv::Mat &out_img, double Gphi, double Iphi)
{
	cv::Scalar mean;
	mean=cv::mean(src_img);
	
	double d_mean = mean.val[0];
	cv::Mat src_img_32f;
	src_img.convertTo(src_img_32f, CV_32F);
	out_img = Gphi*(src_img_32f - d_mean) + d_mean + Iphi;

}

//��ǿ���Ҷ�ͼ,���������Ӧ�ģ�Ч������
void enhance(cv::Mat src, cv::Mat &out_img, double compress)
{
	cv::Mat src_img;
	if (src.channels() < 2) cv::cvtColor(src, src_img, CV_BayerRG2GRAY);
	else   src_img = src;
	
	
	double max,min;
	cv::minMaxLoc(src_img, &min, &max, NULL, NULL);

	int bins = 1000;
	const int channels[1] = { 0 };
	float midRanges[] = { 0,max };
	int hist_sz[] = { bins };
	cv::Mat dstHist;
	const float *ranges[] = { midRanges };

	cv::calcHist(&src_img, 1, channels, cv::Mat(), dstHist, 1, hist_sz, ranges, true, false);

	cv::Mat sum_hist;
	cv::integral(dstHist, sum_hist, CV_32F);      //���������ͼ
	cv::Mat sum_hist2 = sum_hist(cv::Rect(1, 1, 1, 1000)) / src_img.total();      //�ѵڶ���ȡ����

	std::vector<float> vd;
	vd.assign((float*)sum_hist2.datastart, (float*)sum_hist2.dataend);
	auto it_up = std::upper_bound(vd.begin(), vd.end(), 1-compress);        //����%5�ı߽�
	auto it_down = std::lower_bound(vd.begin(), vd.end(), compress);        //��С��%5�ı߽�
	
	/*std::cout << "max--" << max << "  min--" << min << std::endl;
	std::cout << "it--" << it_up - vd.begin() << std::endl;
	std::cout << "it--" << it_down - vd.begin() << std::endl;*/

	double value_up = (max - min) / bins*(it_up - vd.begin());
	double value_down = (max - min) / bins*(it_down - vd.begin());

	//std::cout << value_up << "  " << value_down;

	//������ֵ���˽ض�
	cv::threshold(src_img, src_img, value_up, 255, CV_THRESH_TRUNC);
	//cv::threshold(src_img, src_img, value_down, 255, CV_THRESH_TOZERO);

	//�Ҷ�����
	out_img = (src_img - value_down) / (value_up - value_down) * 255;
}

//ȥ�����ֵȥ�����Σ����þ�ֵ��ȥһЩ��Ƶ
void denoise(cv::Mat src, cv::Mat &out_img)
{
	cv::medianBlur(src, src, 3);
	//cv::GaussianBlur(src, src, cv::Size(3,3), 0);
	cv::Mat kernel = (cv::Mat_<double>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
	cv::Mat out_img_;
	cv::filter2D(src, out_img_, src.depth(), kernel);
	
	out_img_ = src + 0.1*out_img_;

	out_img_.convertTo(out_img, CV_8U);
	
}