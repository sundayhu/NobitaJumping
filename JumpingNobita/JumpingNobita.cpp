// JumpingNobita.cpp : 定义控制台应用程序的入口点。
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
