#include "stdafx.h"
#include "Back.h"


CBack::CBack()
{
}


CBack::~CBack()
{
}

//变量初始化
void CBack::init()
{
	m_count = 0 ;
	m_dir = 0; 
	m_srcimg = cvLoadImage("img\\back\\map_01.png");
	m_helpimg = cvLoadImage("img\\back\\help.png");
}

//复制背景
void CBack::copy()
{
	m_showimg = cvCloneImage(m_srcimg);
}

//开始界面
void CBack::start()
{
	m_showimg = cvLoadImage("img\\back\\start.jpg");
}

//运行界面
void CBack::run()
{
	//	0-12 背景图从01 到 13
	char filename[] = "img\\back\\map_01.png";
	for (int i = 0; i < 13; i++)
	{
		sprintf_s(filename, "img\\back\\map_%02d.png", i + 1);
		m_changeimg[i] = cvLoadImage(filename);
	}
}


//结束界面
void CBack::over()
{
	m_showimg = cvLoadImage("img\\back\\over.png");
}


void CBack::release()
{
	cvReleaseImage(&m_srcimg);
	cvReleaseImage(&m_showimg);
}



//背景的变化 相当于变化版的cvcopy
void CBack::change()
{
	m_count++;
	if ( ( m_count% 5 ==0)  && (m_dir < 12))
		m_dir++;
	m_showimg = cvCloneImage(m_changeimg[m_dir]);

}