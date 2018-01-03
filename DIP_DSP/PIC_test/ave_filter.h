/*
 * mid_filter.h
 *
 *  Created on: 2018-1-3
 *      Author: zhxing
 */

#ifndef AVE_FILTER_H_
#define AVE_FILTER_H_
int coefArray[9]={1,1,1,1,1,1,1,1,1};

void Img_smooth(unsigned char *F,
		unsigned char *G,
		int cols,int rows)
{
	unsigned char *ptr,*pp,*newpp;  //�ֲ�����
	int tmpNum,x,y;
	//-----------����߽磬���������ԭֵ
	for(x=0;x<cols;x++)
	{
		G[x]=F[x];      // ��һ�в���������ԭֵ
	}
	newpp=G+(rows-1)*cols;   //�����������һ���׵�ַ
	pp=F+(rows-1)*cols;      //��Ҳ������ͼ�����һ���׵�ַ
	for(x=0;x<cols;x++)    //���һ��Ҳ����ԭֵ
	  *newpp++=*pp++;

	newpp=G;
	pp=F;   //׼���������һ��
	for(y=0;y<rows;y++)
	{
		*newpp=*pp;
		newpp+=cols;
		pp+=cols;
		//��ֵ�Ժ��ƶ�����һ��
	}
	newpp=G+cols;
	pp=F+cols;  //׼�������ұ�һ��
	for(y=0;y<rows;y++)
	{
		*newpp=*pp;
		newpp+=cols;
		pp+=cols;
	}
	//-------------����߽�----------------------

	for(y=1;y<rows-1;y++)
		for(x=1;x<cols-1;x++)
		{
			newpp=G+y*cols+x;
			pp=F+y*cols+x;
			//��һ������Ԫ��
			ptr=pp-cols-1;  //���Ͻ�
			tmpNum+=(*ptr++)*coefArray[0];
			tmpNum+=(*ptr++)*coefArray[1];
			tmpNum+=(*ptr)*coefArray[2];
			//�ڶ�������Ԫ��
			ptr=pp-1;
			tmpNum+=(*ptr++)*coefArray[3];
			tmpNum+=(*ptr++)*coefArray[4];
			tmpNum+=(*ptr)*coefArray[5];
			//����������Ԫ��
			ptr=pp+cols-1;
			tmpNum+=(*ptr++)*coefArray[6];
			tmpNum+=(*ptr++)*coefArray[7];
			tmpNum+=(*ptr)*coefArray[8];

			tmpNum/=9;
			if(tmpNum>255)  //������
			{
				*newpp=255;
			}
			else
				*newpp=tmpNum;
		}

}




#endif /* AVE_FILTER_H_ */
