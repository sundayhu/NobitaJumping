#include "stdafx.h"
#include "Cloud.h"


CCloud::CCloud()
{
}


CCloud::~CCloud()
{
}


void CCloud::init(IplImage *back)
{

	m_img = cvLoadImage("img\\cloud\\cloud01.png");
	m_pos.x = rand()%(back->width-m_img->width);
	m_pos.y = 0;
	m_speed = 2;
	m_maxy = back->height - m_img->height;
	flag = false; //存活
	m_bombflag = false; //不绘制爆炸
	m_pir = 0;
}


void CCloud::draw(IplImage *back)
{
	for (int row = 0; row < m_img->height; row++)
	{
		for (int col = 0; col < m_img->width; col++)
		{
			int b = CV_IMAGE_ELEM(m_img,uchar, row, col * 3);
			int g = CV_IMAGE_ELEM(m_img,uchar, row, col * 3 + 1);
			int r = CV_IMAGE_ELEM(m_img,uchar, row, col * 3 + 2);

			if ((b == 0) && (g == 0) && (r == 255))
				continue;

			CV_IMAGE_ELEM(back, uchar,row + m_pos.y, (col + m_pos.x) * 3) = b;
			CV_IMAGE_ELEM(back, uchar,row + m_pos.y, (col + m_pos.x) * 3 + 1) = g;
			CV_IMAGE_ELEM(back, uchar,row + m_pos.y, (col + m_pos.x) * 3 + 2) = r;
		}
	}
}

void CCloud::drawbomb(IplImage *back)
{

	for (int row = 0; row < m_bombimg[m_pir]->height; row++)
	{
		for (int col = 0; col < m_bombimg[m_pir]->width; col++)
		{
			int b = CV_IMAGE_ELEM(m_bombimg[m_pir], uchar, row, col * 3);
			int g = CV_IMAGE_ELEM(m_bombimg[m_pir], uchar, row, col * 3 + 1);
			int r = CV_IMAGE_ELEM(m_bombimg[m_pir], uchar, row, col * 3 + 2);

			if ( b==0 && g==0 &&  r == 255)
				continue;

			CV_IMAGE_ELEM(back, uchar, row + m_pos.y, (col + m_pos.x) * 3) = b;
			CV_IMAGE_ELEM(back, uchar, row + m_pos.y, (col + m_pos.x) * 3 + 1) = g;
			CV_IMAGE_ELEM(back, uchar, row + m_pos.y, (col + m_pos.x) * 3 + 2) = r;
		}
	}

	m_pir++;

	if (m_pir == 3)
		flag = true;	//标记为死亡
}


void CCloud::move()
{
	m_pos.y += m_speed;
	if (m_pos.y + m_speed > m_maxy)
	{
		m_pos.y = m_maxy;
		flag = true;
	}
}
void CCloud::release()
{
	cvReleaseImage(&m_img);
}

void CCloud::bomb()
{
	m_bombimg[0] = cvLoadImage("img\\cloud\\cloud_01.png");
	m_bombimg[1] = cvLoadImage("img\\cloud\\cloud_02.png");
	m_bombimg[2] = cvLoadImage("img\\cloud\\cloud_03.png");

	m_pir = 0;
}