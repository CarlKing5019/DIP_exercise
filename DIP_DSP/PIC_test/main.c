#include<stdio.h>
#include<math.h>
#include"ave_filter.h"
#include"windows.h"
#include"algor.h"

unsigned char *img=(unsigned char *)0x00850000;
unsigned char *img_uchar=(unsigned char *)0x00850000+4096;
float  *img_with_window=(float *)0x00852000;   //����պ�����img_smooth�ĺ���
int main(void) {
	add_coswindow(img,cos_window_64_64,img_with_window,4096);

	floar2uchar(img_with_window,img_uchar,4096);

	struct max_index max_res;
	max_res=max(img_with_window,4096);
	printf("���ֵ�ǣ�%f\n",max_res.max_num);
	printf("���ֵ�����ǣ�%d\n",max_res.max_index);

	//Img_smooth(img,img_smooth,64,64);
	return 0;
}
