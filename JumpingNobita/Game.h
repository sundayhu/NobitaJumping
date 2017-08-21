#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;
#include "Back.h"
#include "Player.h"
#include "Cloud.h"
#include "Score.h"
#include "Award.h"
#include<vector>
using namespace std;
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


class CGame
{
public:
	CGame();
	~CGame();
	void init();
	void run();
	void over();
	void release();
	int m_count;
	int m_grade;
	int m_awardtime;
	int m_dir;
	void actionCloud();
	void actionAward();
	CBack m_back;
	CPlayer m_player; 
	CScore m_score;
	vector<CCloud> m_cloud;
	vector<CCloud>::iterator iter;
	vector<CAward> m_award;
	vector<CAward>::iterator _iter;
};

