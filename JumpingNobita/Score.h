#pragma once
#include "stdio.h"
#include "string.h"
#include<opencv2/opencv.hpp>
using namespace cv;

class CScore
{
public:
	CScore();
	~CScore();
	void init();
	void drawGrade(int score, IplImage *back);
	void drawAwardTime(int time, IplImage *back);
	char m_str1[10];
	char m_str2[10];
	char m_str3[20];
	CvPoint m_pt1;
	CvPoint m_pt2;
	CvPoint m_pt3;
	CvFont m_font;
};

