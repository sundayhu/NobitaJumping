#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
	
}


CPlayer::~CPlayer()
{
}



void  CPlayer::init(IplImage *back)
{
	//	0-6 为左1到左7
	char filename1[] = "img\\player\\left1.jpg";
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(filename1, "img\\player\\left%d.jpg", i+1);
		m_img[i] = cvLoadImage(filename1);
	}
	// 7-13为右1到右7
	char filename2[] = "img\\player\\right1.jpg";
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(filename2, "img\\player\\right%d.jpg", i + 1);
		m_img[i+7] = cvLoadImage(filename2);
	}
	m_pos.x = (back->width - m_img[0]->width) / 2;
	m_pos.y = back->height - m_img[0]->height;
	m_xspeed = 8;
	m_upspeed = 20;
	m_downspeed = 10;
	m_dir = 0; 
	m_count = 0;
	m_flag = false;
	m_upordown = false;
} 

void CPlayer::runInit()
{
	m_xspeed *= 5;
	m_img[0] = cvLoadImage("img\\player\\left7.jpg");
	m_img[7] = cvLoadImage("img\\player\\right7.jpg");
}
void  CPlayer::move(string order,IplImage *back)
{
	if (!order.compare("left")) //相等为0 
	{
		m_pos.x -= m_xspeed;
		if (m_pos.x <= 0)
			m_pos.x = 0;
		
	}
	else if (!order.compare("right"))
	{
		m_pos.x += m_xspeed;
		if (m_pos.x >= back->width - m_img[0]->width)
			m_pos.x = back->width - m_img[0]->width;
		
	}

}

void CPlayer::changemode(string order)
{
	if (!order.compare("left")) //相等为0 
	{
		m_dir = 0; 
	}
	else if (!order.compare("right"))
	{
		m_dir = 7;
	}
}

void CPlayer::drawToBack(IplImage *back)
{
	for (int row = 0; row < m_img[m_dir]->height; row++)
	{
		for (int col = 0; col < m_img[m_dir]->width; col++)
		{
			int b = CV_IMAGE_ELEM(m_img[m_dir],
				uchar, row, col * 3);
			int g = CV_IMAGE_ELEM(m_img[m_dir],
				uchar, row, col * 3 + 1);
			int r = CV_IMAGE_ELEM(m_img[m_dir],
				uchar, row, col * 3 + 2);

			if ((b > 230) && (g > 230) && (r > 230))
				continue;

			CV_IMAGE_ELEM(back, uchar,
				row + m_pos.y, (col + m_pos.x) * 3) = b;
			CV_IMAGE_ELEM(back, uchar,
				row + m_pos.y, (col + m_pos.x) * 3 + 1) = g;
			CV_IMAGE_ELEM(back, uchar,
				row + m_pos.y, (col + m_pos.x) * 3 + 2) = r;
		}
	}
}

void CPlayer::release()
{

}


void CPlayer::autoMove()
{
	if (m_count <= 8)
	{
		if (m_pos.y - m_upspeed <= 0)
		{
			m_pos.y = 0;
			m_count += 10;
		}
		else
			m_pos.y -= m_upspeed;
	}
	else
	{
		m_upordown = true;
		if (m_pos.y + m_downspeed >= 455-112)
		{
			m_pos.y = 455 - 112;
			m_flag = true;
		}
		else
			m_pos.y += m_downspeed;
	}
	m_count++;
}
