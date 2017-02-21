#include "Enemy.h"
#include <iostream>
#include "SomeConst.h"

Enemy::Enemy(int sx, int sy, short kind) {
	coord[0] = sx; coord[1] = sy; speed = 0; move_wait = 0;
	ekind = (ENEMYKIND)kind;

	switch (kind) {
	case 0:alive = 10; bkind = 4; speed = 1; break;
	case 1:alive = 50; bkind = 4; speed = 2; break;
	default:break;
	}
}

void Enemy::getPos(int &x, int &y) {
	x = coord[0];
	y = coord[1];
}

int Enemy::give_score() {
	switch (ekind) {
	case 0:return 10;
	case 1:return 50;
	default:return 0;
	}
}

void Enemy::move() {
	int randMove = rand() % 3;	//	move in 3 directions
	coord[1]++;
	switch (randMove) {
	case 0:if (coord[0] > 0)coord[0]--; break;
	case 1:break;
	case 2:if (coord[0] < WIDTH)coord[0]++; break;
	default:exit(-1);
	}
	return;
}

void Enemy::shoot() {
	char ch = '.';
	switch (ekind) {
	case 0:bkind = 4; ch = 'o'; break;//SMALL1
	case 1:bkind = 7; ch = '@'; break;//BIG1
	default:break;
	}
	switch (ekind) {
	case 0:
		if (rand() % 8 == 0) {
			Bullet *b = new Bullet(coord[0], coord[1], Bullet::DOWN, ch, PONE);
			bullets.push_front(b);
		}
		break;
	case 1:
		if (rand() % 8 == 6) {
			Bullet *b = new Bullet(coord[0], coord[1], Bullet::DOWN, ch, PTWO);
			bullets.push_front(b);
		}
		else if (rand() % 8 == 7) {
			Bullet* b1 = new Bullet(coord[0] + 1, coord[1], Bullet::DOWN, ch, PTWO);
			Bullet* b2 = new Bullet(coord[0] - 1, coord[1], Bullet::DOWN, ch, PTWO);
			bullets.push_front(b1);
			bullets.push_front(b2);
		}
		break;
	default:break;
	}

}
void Enemy::update() {
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end();) {//子弹移动
		(*iter)->move();
		if ((*iter)->inscreen() == false) {
			delete (*iter);
			bullets.erase(iter++);
		}
		else
			++iter;
	}
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter)
		(*iter)->updata();

	if (alive > 0) {
		switch (ekind) {
		case 0:battlefield[coord[1]][coord[0]] = '=';
			if (coord[0] - 1 > 0)
				battlefield[coord[1]][coord[0] - 1] = 'M';
			if (coord[0] + 1 < WIDTH)
				battlefield[coord[1]][coord[0] + 1] = 'M';
			break;
		case 1:
			battlefield[coord[1]][coord[0]] = 'U';
			if (coord[0] - 2 > 0)
				battlefield[coord[1]][coord[0] - 2] = '=';
			if (coord[0] + 2 < WIDTH)
				battlefield[coord[1]][coord[0] + 2] = '=';
			if (coord[0] - 1 > 0) {
				battlefield[coord[1]][coord[0] - 1] = 'I';
			//	if (coord[1] - 1 > 0) { battlefield[coord[1] - 1][coord[0] - 1] = '-'; battlefield[coord[1] - 1][coord[0] - 1] = '-'; }
				if (coord[1] + 1 < HEIGHT) { battlefield[coord[1] + 1][coord[0] - 1] = 'o'; battlefield[coord[1] + 1][coord[0] - 1] = 'o'; }
			}
			if (coord[0] + 1 < WIDTH) {
				battlefield[coord[1]][coord[0] + 1] = 'I';
			//	if (coord[1] - 1 > 0) { battlefield[coord[1] - 1][coord[0] + 1] = '-'; battlefield[coord[1] - 1][coord[0] + 1] = '-'; }
				if (coord[1] + 1 < HEIGHT) { battlefield[coord[1] + 1][coord[0] + 1] = 'o'; battlefield[coord[1] + 1][coord[0] + 1] = 'o'; }
			}
			break;
		default:break;
		}
		shoot();
	}
}

void Enemy::clear_bullet() {
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end();) {
		if ((*iter)->get_alive() == false) {
			delete (*iter);
			bullets.erase(iter++);
		}
		else
			++iter;
	}
}

void Enemy::reduce_life(Myplane &p) {
	if (alive > 0) {
		alive -= p.hurt(coord[0], coord[1]);
		if (ekind == 0) {
			alive -= p.hurt(coord[0] - 1, coord[1]);
			alive -= p.hurt(coord[0] + 1, coord[1]);
		}
		else if (ekind == 1) {
			alive -= p.hurt(coord[0] - 1, coord[1] + 1) / 2;
			alive -= p.hurt(coord[0] + 1, coord[1] + 1) / 2;
			alive -= p.hurt(coord[0] - 2, coord[1]) / 2;
			alive -= p.hurt(coord[0] + 2, coord[1]) / 2;
		}
	}
}

int Enemy::hurt(int x, int y) {//对某点的伤害
	int hurt = 0;
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter)
		hurt += (*iter)->hurt(x, y);
	hurt += Enemy::hurt0(x, y);
	return hurt;
}

int Enemy::hurt0(int x, int y) {//撞机
	if (alive > 0)
		if (x == this->coord[0] && y == this->coord[1]
			|| (x - 1) == this->coord[0] && y == this->coord[1]
			|| (x + 1) == this->coord[0] && y == this->coord[1]
			|| (x - 2) == this->coord[0] && y == this->coord[1]
			|| (x + 2) == this->coord[0] && y == this->coord[1])
			switch (ekind) {
			case 0:return 25; break;
			case 1:return 150; break;
			default:return 0;
			}
	return 0;
}