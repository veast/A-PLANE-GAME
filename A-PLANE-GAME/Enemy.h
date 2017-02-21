#pragma once
#include "Myplane.h"
#include "SomeConst.h"
#include <windows.h>
#include <list>
#include "Bullet.h"

using namespace std;

class Myplane;

class Enemy{
private:
	int coord[2];
	short bkind;
	short speed;
	short move_wait;
	ENEMYKIND ekind;
protected:
	list<Bullet*> bullets;
	int alive;
public:
	Enemy(){ coord[0] = coord[1] = 0; speed = 0; alive = 20; move_wait = 0; }
	Enemy(int sx, int sy,short kind);
	~Enemy(void){};
	void getPos(int &x, int &y);
	bool still_alive(){
		if (alive > 0)return true;
		return false;
	}
	int give_score();
	virtual void move();

	virtual void update();//���·ɻ��Լ����ӵ�
	virtual void reduce_life(Myplane &p);
	virtual int hurt(int x, int y);
	int hurt0(int x, int y);
	virtual void shoot();
	void clear_bullet();
	list<Bullet*> & get_bullets(){ return bullets; }
	friend Game_run;
	friend Myplane;
};