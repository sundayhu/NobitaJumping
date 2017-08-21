#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
class CAward
{
public:
	CAward();
	~CAward();
	IplImage *m_img;
	CvPoint m_pos;
	int m_maxx;
	int m_speed; 
	bool m_flag;
	void init(IplImage *back);
	void move();
	void draw(IplImage *back);
	void release();
};

