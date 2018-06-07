#include"fog_move.hpp"


//��Сֵ�˲���ʵ���Ͼ���һ����ʴ�Ĺ��̣�ֱ�ӽ���opencv�ĸ�ʴ��������
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size)
{
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size));
	cv::erode(src_img, res_img, element);
}

//��ȡͨ������Сֵ������ֻ���Լ��������ˣ�������ָ�����ģ�ò���������
cv::Mat min_BGR(cv::Mat &src_img)
{
	int rows = src_img.rows;
	int cols = src_img.cols;
	
	cv::Mat res = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC1);
	//creat one channel image to save min_rgb
	int channel_num = src_img.channels();
	std::cout << channel_num << std::endl;
	if (channel_num <= 1)
	{
		std::cout << "channel is just 1, return zeros matrix!" << std::endl;
		return res;
	}
	
	
	for (int i = 0; i < rows; i++)
	{
		uchar *img_adress = src_img.ptr<uchar>(i);   //��ǰ�еĵ�ַ
		uchar *res_adress = res.ptr<uchar>(i);       //��ǰ�еĵ�ַ
		for (int j_i = 0,j_r=0; j_r < cols,j_i<cols*channel_num; j_i+=3,j_r++)
		{
			res_adress[j_r] =std::min(std::min(img_adress[j_i],img_adress[j_i+1]),img_adress[j_i+2]);
		}
		
	}
	std::cout << "done!"<<std::endl;
	return res;

}


//�����˲�����
cv::Mat guide_filter(cv::Mat & img, cv::Mat & p, int r, double eps)
{
	cv::Mat img_32f, p_32f, res;
	if()
	img.convertTo(img_32f, CV_32F);
	p.convertTo(p_32f, CV_32F);
	//��ת����32F���������˷�


	cv::Mat i_p, i2;
	cv::multiply(img_32f, p_32f, i_p);
	cv::multiply(p_32f, p_32f, i2);

	int height = img.rows;
	int width = img.cols;
	cv::Size kernel_sz(2 * r + 1, 2 * r + 1);

	//�����ĸ���ֵ�˲���
	cv::Mat m_Img, m_p, m_Ip, m_i2;    
	cv::boxFilter(img, m_Img, CV_32F, kernel_sz);
	cv::boxFilter(p, m_p, CV_32F, kernel_sz);
	cv::boxFilter(i_p, m_Ip, CV_32F, kernel_sz);
	cv::boxFilter(i2, m_i2, CV_32F, kernel_sz);
	
	//����ip��Э�����img�ķ���
	cv::Mat cov_ip = m_Ip - m_Img.mul(m_p);
	cv::Mat var_i = m_i2 - m_Img.mul(m_Img);

	//��a��b
	cv::Mat a, b;
	cv::divide(cov_ip, var_i+eps, a);
	b = m_p - a.mul(m_Img);

	//�԰�������i������a,b��ƽ��(����a��b����ֵ�˲�)
	cv::Mat mean_a, mean_b;
	cv::boxFilter(a, mean_a, CV_32F, kernel_sz);
	cv::boxFilter(b, mean_b, CV_32F, kernel_sz);

	//�������
	res = mean_a.mul(p_32f) + mean_b;
	
	return res;	
}

void getV1(cv::Mat &m, int &r, double eps, double &w, double &maxV1)
{
	cv::Mat V1 = min_BGR(m);    
	cv::Mat V1_32f;
	V1.convertTo(V1_32f, CV_32F);
	V1_32f = V1_32f / 255.0;

	cv::Mat V1_min_filter;
	min_filter(V1, V1_min_filter, 7);
	cv::Mat V1_min_32f;
	V1_min_filter.convertTo(V1_min_32f, CV_32F);        
	//��Ϊ��д��min_bgr���������uint8�ģ����Ծ���������Сֵ֮����ȥ����255
	V1_min_32f = V1_min_32f / 255.0;

	cv::Mat V1_g = guide_filter(V1_32f, V1_min_filter, r, eps);
	//�����˲��԰�ͨ��Ϊԭͼ����Сֵ�˲�֮��ͨ����ͼ��Ϊ����
	int bins = 1000;
	
	std::vector<int>  his;
	cv::calcHist(V1_g, 1, his);        //ͳ��ֱ��ͼ
	

}