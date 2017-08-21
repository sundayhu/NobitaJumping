#include "stdafx.h"
#include "Game.h"
#include"time.h"
#include <iostream>
using namespace std;

CGame::CGame()
{
};


CGame::~CGame()
{
}

void CGame::init()
{
	m_count = 0;
	m_grade = 0;
	m_awardtime = 0;
	m_dir = 0;
	m_score.init();
	m_back.init();
	m_player.init(m_back.m_srcimg);
}

void CGame::run()
{
	bool flag1 = false;
	//开始界面
	cvNamedWindow("Start");
	m_back.start();
	while (1)
	{
		cvShowImage("Start", m_back.m_showimg);
		char order = cvWaitKey();
		switch (order)
		{
		case 'P':
		case 'p': // p键开始游戏
		{
					  flag1 = true;
					  break;
		}
		case 'H':
		case 'h': // h键进入帮助界面
		{
					  cvShowImage("Start", m_back.m_helpimg);
					  cvWaitKey();
					  break;
		}
		case 'E':
		case 'e': // e键退出游戏
		{
					  exit(0);
		}

		}
		if (flag1)	//退出主界面 进入游戏
		{
			cvDestroyWindow("Start");
			break;
		}
	}


	//准备界面（显示一下）左右移动
	PlaySoundA("music\\music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cvNamedWindow("Run");
	m_back.copy();
	m_player.drawToBack(m_back.m_showimg);
	cvShowImage("Run", m_back.m_showimg);
	bool flag2 = false;
	while (1)
	{
		m_count++;	  //游戏时间
		actionCloud();//云的活动
		m_player.drawToBack(m_back.m_showimg);
		cvShowImage("Run", m_back.m_showimg);
		m_back.copy();
		char order = cvWaitKey(40);
		switch (order)
		{
		case 'A':
		case 'a':
		{
					m_player.changemode("left");
					for (int ix = 0; ix < 7; ix++)
					{
						m_count++;
						actionCloud();
						m_player.move("left", m_back.m_srcimg);
						cvWaitKey(40);
						m_player.drawToBack(m_back.m_showimg);
						cvShowImage("Run", m_back.m_showimg);
						m_back.copy();
						m_player.m_dir++;
					}
					m_player.m_dir--;
					break;
		}
		case 'D':
		case 'd':
		{
					m_player.changemode("right");
					for (int ix = 0; ix < 7; ix++)
					{
						m_count++;
						actionCloud();
						m_player.move("right", m_back.m_srcimg);
						cvWaitKey(40);
						m_player.drawToBack(m_back.m_showimg);
						cvShowImage("Run", m_back.m_showimg);
						m_back.copy();
						m_player.m_dir++;
					}
					m_player.m_dir--;
					break;
		}
		case 'W':
		case 'w':flag2 = true; break;			//开始游戏
		case 'E':
		case 'e': // e键退出游戏
		{
					  exit(0);
		}
		}
		if (flag2)	//退出准备界面 正式开始游戏
		{
			break;
		}
	}

	//运行界面 正式开始
	m_back.run();	//初始化背景图片数组
	m_player.runInit(); //人物图片的修改
	while (1)
	{
		//游戏运行时间
		m_count++;
		//背景的变化
		m_back.change();
		//奖励时间变化
		if (m_count % 20 == 0 && m_awardtime > 0)
			m_awardtime--;
		//人物移动
		m_player.autoMove();
		//云的活动
		actionCloud();
		//奖励
		actionAward();
		//分数 加倍时间绘制
		m_score.drawGrade(m_grade, m_back.m_showimg);
		m_score.drawAwardTime(m_awardtime, m_back.m_showimg);
		//人物的绘制
		m_player.drawToBack(m_back.m_showimg);
		
		//人物踩到云的判定   向下的时候判定
		if (m_player.m_upordown)
		{
			//done(m_player.m_pos.x, m_player.m_pos.y); //计分，标记云的死亡
			int dir = 0;
			for (int i = 0; i < m_cloud.size(); i++)
			{
				if ((m_player.m_pos.y + m_player.m_img[0]->height / 2 - m_cloud[i].m_pos.y   > 0 &&
					m_player.m_pos.y + m_player.m_img[0]->height / 2 - m_cloud[i].m_pos.y < m_player.m_downspeed)
					&& (m_player.m_pos.x >= m_cloud[i].m_pos.x && m_player.m_pos.x < m_cloud[i].m_pos.x + m_cloud[i].m_img->width))
				{
					m_player.m_count = 0; //自动运动步数清零	
					if (m_awardtime>0)	//得分是否双倍
						m_grade += 10 * 2;
					else
						m_grade += 10;
					dir = i;
					//爆炸
					m_cloud[i].bomb();	//初始化爆炸图片
					m_cloud[i].m_bombflag = true;  //绘制爆炸效果
				}
			}
		}
		//人物和奖励类碰撞的判定
		for (int i = 0; i < m_award.size(); i++)
		{
			if ((abs(m_player.m_pos.x - m_award[i].m_pos.x) < m_player.m_img[0]->width ||
				abs(m_player.m_pos.x - m_award[i].m_pos.x) < m_award[i].m_img->width) &&
				(abs(m_player.m_pos.y - m_award[i].m_pos.y) < m_player.m_img[0]->height ||
				abs(m_player.m_pos.y - m_award[i].m_pos.y) < m_award[i].m_img->height))
			{
				m_awardtime += 5;
				m_award[i].m_flag = true;
			}
		}
		//死亡判定
		if (m_player.m_flag)
		{
			cvDestroyWindow("Run");
			break;
		}

		//显示游戏界面
		cvShowImage("Run", m_back.m_showimg);

		//等待按键
		char order = cvWaitKey(40);
		switch (order)
		{
		case 'A':
		case 'a':
		{
					m_player.changemode("left");
					m_player.move("left", m_back.m_srcimg);
					break;
		}
		case 'D':
		case 'd':
		{
					m_player.changemode("right");
					m_player.move("right", m_back.m_srcimg);
					break;
		}
		case ' ':cvWaitKey(); break;				//暂停游戏，任意键回到游戏
		case 'E':
		case 'e': exit(0); 				//退出游戏
		}
		
	}
	cvDestroyWindow("Run");
}


void CGame::over()
{
	//结束+界面
	PlaySoundA("music\\over.wav", NULL, SND_FILENAME | SND_ASYNC);
	cvNamedWindow("Over");
	m_back.over();
	m_score.m_pt1.x = 490;
	m_score.m_pt1.y = 305;
	m_score.drawGrade(m_grade,m_back.m_showimg);
	cvShowImage("Over", m_back.m_showimg);
	
	while (1)
	{
		char order = cvWaitKey();
		switch (order)
		{
		case 'P':
		case 'p': // p键继续游戏
		{
					  m_award.clear();
					  m_cloud.clear();
					  cvDestroyWindow("Over");
					  init();
					  run();
					  over();
		}
		case 'E':
		case 'e': // e键退出游戏
			cvDestroyWindow("Over");
			return;
		}
		
	}

}



void CGame::actionCloud()  //产生 清除 移动 绘制 
{
	//云的产生
	if (m_count % 20 == 0)
	{
		CCloud cloud1;
		cloud1.init(m_back.m_srcimg);
		m_cloud.push_back(cloud1);
		//CCloud cloud2;
		//cloud2.init(m_back.m_srcimg);
		//m_cloud.push_back(cloud2);
	}

	//云的移动
	for (int j = 0; j < m_cloud.size(); j++)
	{
		m_cloud[j].move();
	}

	//云的绘制
	iter = m_cloud.begin();
	while (iter != m_cloud.end())
	{
		if ((*iter).m_bombflag && (*iter).m_pir < 3)  //绘制爆炸效果  爆炸效果第三下时 判定云死亡
			(*iter).drawbomb(m_back.m_showimg);
		else					//绘制原图       
			(*iter).draw(m_back.m_showimg);

		iter++;
	}

	//云的清除
	if (m_cloud.size())
	{
		iter = m_cloud.begin();
		while (iter != m_cloud.end())
		{
			if ((*iter).flag)
			{
				(*iter).release();
				iter = m_cloud.erase(iter);
				break;
			}
			else
				iter++;
		}
	}

}

void CGame::actionAward()
{

	if (m_count % 100 == 0)
	{
		CAward award;
		award.init(m_back.m_srcimg);
		m_award.push_back(award);

	}

	for (int j = 0; j < m_award.size(); j++)
	{
		m_award[j].move();
	}

	_iter = m_award.begin();
	while (_iter != m_award.end())
	{
		(*_iter).draw(m_back.m_showimg);
		_iter++;
	}

	if (m_award.size())
	{
		_iter = m_award.begin();
		while (_iter != m_award.end())
		{
			if ((*_iter).m_flag)
			{
				(*_iter).release();
				_iter = m_award.erase(_iter);
				break;
			}
			else
				_iter++;
		}
	}
}


void CGame::release()
{
	m_player.release();
	m_back.release();
}
