/*
 * algor.h
 *
 *  Created on: 2018-1-5
 *      Author: zhxing
 *      һЩҪ�õ��Ĳ�����
 *
 *      1. max_index  max(float *p,int nums)
 *       	�����ֵ������
 *      2. floar2uchar(float *f,unsigned char *u,int nums)
 *      	float->uchar
 *      3. element_wise_product(float *x1,float *x2,float *y,int num)
 *      	��ˣ���Ӧλ��ˣ�ʵ����
 *
 *
 */

#ifndef ALGOR_H_
#define ALGOR_H_

//-------------��1���������Ӧֵ��������---------------------------------
struct max_index{
	float max_num;
	int max_index;
};

struct max_index  max(float *p,int nums)   //һ��������ҳ����ֵ������
{
	int i=0;

	float max=0;
	int index=0;

	struct max_index  max_response;

	for(i=0;i<nums;i++)
	{
		if(p[i]>max)
		{
			max=p[i];       //����Ҫ����CSK�㷨��ʱ����Բ�Ҫ�����ֵ����Ϊ����ֻ��Ҫ�ҵ���������
			index=i;
		}
	}
	max_response.max_num=max;
	max_response.max_index=index;

	return max_response;
}
//-------------��1���������Ӧֵ��������---------------------------------


//-------------��2��float->uchar---------------------------------
void floar2uchar(float *f,unsigned char *u,int nums)
{
	int i=0;
	for(i=0;i<nums;i++)
	{
		u[i]=f[i];   //ֱ�Ӹ�ֵ�Ϳ���
	}
}
//-------------��2��float->uchar---------------------------------


//-------------��3��element_wise_product---------------------------------
void element_wise_product(float *x1,float *x2,float *y,int num)
{
	int i=0;
	for(i=0;i<num;i++)
	{
		y[i]=x1[i]*x2[i];
	}
}
//-------------��3��element_wise_product---------------------------------


#endif /* ALGOR_H_ */
