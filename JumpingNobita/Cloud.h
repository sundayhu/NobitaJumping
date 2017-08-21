#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;

class CCloud
{
public:
	CCloud();
	~CCloud();
	CvPoint m_pos;
	int m_maxy;
	int m_speed;
	IplImage* m_img;
	IplImage* m_bombimg[3];

public:
	void init(IplImage *back);
	void move();
	void draw(IplImage *back);
	void drawbomb(IplImage *back);
	void release();
	void bomb();
	bool flag; // À¿Õˆ
	bool m_bombflag;
	int m_pir;
};

