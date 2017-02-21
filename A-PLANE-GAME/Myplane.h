#pragma once

#include "Enemy.h"
#include "SomeConst.h"
#include <windows.h>
#include <list>
#include "Bullet.h"

using namespace std;

class Enemy;
class Myplane{
	int coord[2];
	int planeLength;

	int alive;	//生命值
	int life;	//生命数
	int score;

	int bkind;
	
	
	list<Bullet*> bullets;//使用list 双向链表容器
public:
	Myplane(int sx, int sy);
	~Myplane(){};
	
	void getPos(int &x, int &y);
	bool still_alive();

	void move(SHORT *stas);//根据键盘输入，进行移动
	void update();//更新飞机以及其子弹
	bool next_life();
	void gain_score(int sc);

	int hurt(int x, int y);
	void reduce(Enemy *e);

	void shoot();
	void move_bullet();
	void clear_bullet();
	
	list<Bullet*> & get_bullets(){ return bullets; }

	friend Game_run;
};