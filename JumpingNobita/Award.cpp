#include "stdafx.h"
#include "Award.h"


CAward::CAward()
{
}


CAward::~CAward()
{
}

void CAward::init(IplImage *back)
{
	m_img = cvLoadImage("img\\award\\award_1.png");
	m_pos.y = rand() % (back->height - m_img->height);
	m_pos.x = 0;
	m_maxx = back->width - m_img->width;
	m_speed = 2;
	m_flag = false;
}

void CAward::move()
{
	m_pos.x += m_speed;
	if (m_pos.x + m_speed > m_maxx)
	{
		m_pos.x = m_maxx;
		m_flag = true;
	}
}

void CAward::draw(IplImage *back)
{
	if (!m_flag)
	for (int row = 0; row < m_img->height; row++)
	{
		for (int col = 0; col < m_img->width; col++)
		{
			int b = CV_IMAGE_ELEM(m_img, uchar, row, col * 3);
			int g = CV_IMAGE_ELEM(m_img, uchar, row, col * 3 + 1);
			int r = CV_IMAGE_ELEM(m_img, uchar, row, col * 3 + 2);

			if ((b == 5) && (g == 15) && (r == 169))
				continue;

			CV_IMAGE_ELEM(back, uchar, row + m_pos.y, (col + m_pos.x) * 3) = b;
			CV_IMAGE_ELEM(back, uchar, row + m_pos.y, (col + m_pos.x) * 3 + 1) = g;
			CV_IMAGE_ELEM(back, uchar, row + m_pos.y, (col + m_pos.x) * 3 + 2) = r;
		}
	}
}

void CAward::release()
{
	cvReleaseImage(&m_img);
}