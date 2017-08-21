#include "stdafx.h"
#include "Score.h"


CScore::CScore()
{
}


CScore::~CScore()
{
}


void CScore::init()
{
	m_pt1.x = 10;
	m_pt1.y = 50;
	m_pt2.x = 550;
	m_pt2.y = 50;
	m_pt3.x = 300;
	m_pt3.y = 50;
	strcpy_s(m_str3, "Double Time : ");
	cvInitFont(&m_font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 3, 8);
}

void CScore::drawGrade(int score, IplImage *back)
{
	score *= 10;
	sprintf_s(m_str1, "%d", score);
	cvPutText(back, m_str1, m_pt1, &m_font, CV_RGB(0, 255, 0));
}

void CScore::drawAwardTime(int time, IplImage *back)
{
	cvPutText(back, m_str3, m_pt3, &m_font, CV_RGB(255, 0, 0));
	sprintf_s(m_str2, "%d", time);
	cvPutText(back, m_str2, m_pt2, &m_font, CV_RGB(255, 0, 0));
}