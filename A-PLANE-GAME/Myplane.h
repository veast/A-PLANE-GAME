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

	int alive;	//����ֵ
	int life;	//������
	int score;

	int bkind;
	
	
	list<Bullet*> bullets;//ʹ��list ˫����������
public:
	Myplane(int sx, int sy);
	~Myplane(){};
	
	void getPos(int &x, int &y);
	bool still_alive();

	void move(SHORT *stas);//���ݼ������룬�����ƶ�
	void update();//���·ɻ��Լ����ӵ�
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