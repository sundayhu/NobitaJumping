#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;
class CBack
{
public:
	CBack();
	~CBack();
	IplImage *m_srcimg;
	IplImage *m_changeimg[13];
	IplImage *m_showimg;
	IplImage *m_helpimg;
	int m_count;
	int m_dir;

public:
	void init();
	void copy();
	void start();
	void ready();
	void run();
	void over();
	void change();
	void release();

};

