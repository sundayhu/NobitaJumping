#pragma once

#include<opencv2/opencv.hpp>
using namespace cv;
#include <string>

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	IplImage *m_img[14];
	CvPoint m_pos;
	int m_xspeed;
	int m_upspeed;
	int m_downspeed;
	int m_dir;
	int m_count;
	bool m_flag;
	bool m_upordown;
public:
	void init(IplImage *back);
	void move(string order,IplImage *back);
	void autoMove();
	void drawToBack(IplImage *back);
	void release();
	void changemode(string order);
	void runInit();
};

