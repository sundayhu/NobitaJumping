// JumpingNobita.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CGame mygame;
	mygame.init();
	mygame.run();
	mygame.over();
	mygame.release();
	return 0;
}
