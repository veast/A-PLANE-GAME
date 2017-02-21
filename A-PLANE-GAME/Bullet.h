#pragma once
#include "SomeConst.h"



class Bullet{
	int xpos, ypos;
	char ch;
	bool alive;
	static short shadow_wait;
public:
	
	enum Direction { DOWN, UP };
	Direction dir;
	BKIND kind;
	Bullet(){ xpos = 0; ypos = 0; dir = DOWN; ch = '.'; kind = PONE; }
	Bullet(int x, int y, Direction dirc, char sig, BKIND k){
		kind = k;
		xpos = x;ypos = y;
		dir = dirc;ch = sig;alive = true;
	}
	int getPosX()const{ return xpos; }
	int getPosY()const{ return ypos; }
	bool get_alive(){ return alive; }
	void kill(){ alive = false; }//用于碰撞
	void move();
	
	void updata();
	int hurt(int x, int y);
	bool inscreen();//用于list中删除
};