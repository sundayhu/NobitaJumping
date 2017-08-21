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
	//��ʼ����
	cvNamedWindow("Start");
	m_back.start();
	while (1)
	{
		cvShowImage("Start", m_back.m_showimg);
		char order = cvWaitKey();
		switch (order)
		{
		case 'P':
		case 'p': // p����ʼ��Ϸ
		{
					  flag1 = true;
					  break;
		}
		case 'H':
		case 'h': // h�������������
		{
					  cvShowImage("Start", m_back.m_helpimg);
					  cvWaitKey();
					  break;
		}
		case 'E':
		case 'e': // e���˳���Ϸ
		{
					  exit(0);
		}

		}
		if (flag1)	//�˳������� ������Ϸ
		{
			cvDestroyWindow("Start");
			break;
		}
	}


	//׼�����棨��ʾһ�£������ƶ�
	PlaySoundA("music\\music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cvNamedWindow("Run");
	m_back.copy();
	m_player.drawToBack(m_back.m_showimg);
	cvShowImage("Run", m_back.m_showimg);
	bool flag2 = false;
	while (1)
	{
		m_count++;	  //��Ϸʱ��
		actionCloud();//�ƵĻ
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
		case 'w':flag2 = true; break;			//��ʼ��Ϸ
		case 'E':
		case 'e': // e���˳���Ϸ
		{
					  exit(0);
		}
		}
		if (flag2)	//�˳�׼������ ��ʽ��ʼ��Ϸ
		{
			break;
		}
	}

	//���н��� ��ʽ��ʼ
	m_back.run();	//��ʼ������ͼƬ����
	m_player.runInit(); //����ͼƬ���޸�
	while (1)
	{
		//��Ϸ����ʱ��
		m_count++;
		//�����ı仯
		m_back.change();
		//����ʱ��仯
		if (m_count % 20 == 0 && m_awardtime > 0)
			m_awardtime--;
		//�����ƶ�
		m_player.autoMove();
		//�ƵĻ
		actionCloud();
		//����
		actionAward();
		//���� �ӱ�ʱ�����
		m_score.drawGrade(m_grade, m_back.m_showimg);
		m_score.drawAwardTime(m_awardtime, m_back.m_showimg);
		//����Ļ���
		m_player.drawToBack(m_back.m_showimg);
		
		//����ȵ��Ƶ��ж�   ���µ�ʱ���ж�
		if (m_player.m_upordown)
		{
			//done(m_player.m_pos.x, m_player.m_pos.y); //�Ʒ֣�����Ƶ�����
			int dir = 0;
			for (int i = 0; i < m_cloud.size(); i++)
			{
				if ((m_player.m_pos.y + m_player.m_img[0]->height / 2 - m_cloud[i].m_pos.y   > 0 &&
					m_player.m_pos.y + m_player.m_img[0]->height / 2 - m_cloud[i].m_pos.y < m_player.m_downspeed)
					&& (m_player.m_pos.x >= m_cloud[i].m_pos.x && m_player.m_pos.x < m_cloud[i].m_pos.x + m_cloud[i].m_img->width))
				{
					m_player.m_count = 0; //�Զ��˶���������	
					if (m_awardtime>0)	//�÷��Ƿ�˫��
						m_grade += 10 * 2;
					else
						m_grade += 10;
					dir = i;
					//��ը
					m_cloud[i].bomb();	//��ʼ����ըͼƬ
					m_cloud[i].m_bombflag = true;  //���Ʊ�ըЧ��
				}
			}
		}
		//����ͽ�������ײ���ж�
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
		//�����ж�
		if (m_player.m_flag)
		{
			cvDestroyWindow("Run");
			break;
		}

		//��ʾ��Ϸ����
		cvShowImage("Run", m_back.m_showimg);

		//�ȴ�����
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
		case ' ':cvWaitKey(); break;				//��ͣ��Ϸ��������ص���Ϸ
		case 'E':
		case 'e': exit(0); 				//�˳���Ϸ
		}
		
	}
	cvDestroyWindow("Run");
}


void CGame::over()
{
	//����+����
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
		case 'p': // p��������Ϸ
		{
					  m_award.clear();
					  m_cloud.clear();
					  cvDestroyWindow("Over");
					  init();
					  run();
					  over();
		}
		case 'E':
		case 'e': // e���˳���Ϸ
			cvDestroyWindow("Over");
			return;
		}
		
	}

}



void CGame::actionCloud()  //���� ��� �ƶ� ���� 
{
	//�ƵĲ���
	if (m_count % 20 == 0)
	{
		CCloud cloud1;
		cloud1.init(m_back.m_srcimg);
		m_cloud.push_back(cloud1);
		//CCloud cloud2;
		//cloud2.init(m_back.m_srcimg);
		//m_cloud.push_back(cloud2);
	}

	//�Ƶ��ƶ�
	for (int j = 0; j < m_cloud.size(); j++)
	{
		m_cloud[j].move();
	}

	//�ƵĻ���
	iter = m_cloud.begin();
	while (iter != m_cloud.end())
	{
		if ((*iter).m_bombflag && (*iter).m_pir < 3)  //���Ʊ�ըЧ��  ��ըЧ��������ʱ �ж�������
			(*iter).drawbomb(m_back.m_showimg);
		else					//����ԭͼ       
			(*iter).draw(m_back.m_showimg);

		iter++;
	}

	//�Ƶ����
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
