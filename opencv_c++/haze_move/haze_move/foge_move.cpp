#include"fog_move.hpp"


//��Сֵ�˲���ʵ���Ͼ���һ����ʴ�Ĺ��̣�ֱ�ӽ���opencv�ĸ�ʴ��������
void min_filter(cv::Mat &src_img, cv::Mat &res_img, int kernel_size)
{
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size));
	cv::erode(src_img, res_img, element);
}

//��ȡͨ������Сֵ������ֻ���Լ���������
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
	std::cout << "done!";
	return res;

}
