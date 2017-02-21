#include"Myplane.h"


extern char battlefield[HEIGHT][WIDTH];

Myplane::Myplane(int sx, int sy) {
	bkind = PMY;
	coord[0] = sx;
	coord[1] = sy;
	planeLength = 5;
	alive = 200; life = 2; score = 0;
}

bool Myplane::still_alive() {
	if (alive > 0)
		return true;
	else
		return false;
}

void Myplane::getPos(int &x, int &y) {
	x = coord[0];
	y = coord[1];
}

void Myplane::gain_score(int sr) {
	score += sr;
	return;
}

void Myplane::move(SHORT *stas) {
	if (alive) {
		if (stas[UP] < 0)
			(coord[1] > 0) ? coord[1]-- : coord[1] = coord[1];
		else if (stas[DOWN] < 0)
			(coord[1] < HEIGHT - 1) ? coord[1]++ : coord[1] = coord[1];
		else if (stas[LEFT] < 0)
			(coord[0] > 0) ? coord[0]-- : coord[0] = coord[0];
		else if (stas[RIGHT] < 0)
			(coord[0] < WIDTH - 1 - planeLength) ? coord[0]++ : coord[0] = coord[0];
	}
}

void Myplane::update() {
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter) //iterator begin()������Ԫ�صĵ�����ָ��iterator end()����βԪ��֮��λ�õĵ�����ָ��
		(*iter)->updata();

	if (alive) {
		battlefield[coord[1]][coord[0]] = 'o';
		battlefield[coord[1]][coord[0] + 1] = '=';
		battlefield[coord[1]][coord[0] + 2] = 'W';
		battlefield[coord[1]][coord[0] + 3] = '=';
		battlefield[coord[1]][coord[0] + 4] = 'o';
	}
	else {
		battlefield[coord[1]][coord[0]] = 'X';
		battlefield[coord[1]][coord[0] + 1] = 'X';
		battlefield[coord[1]][coord[0] + 2] = 'X';
		battlefield[coord[1]][coord[0] + 3] = 'X';
		battlefield[coord[1]][coord[0] + 4] = 'X';
	}
}

void Myplane::shoot() {
	char ch = '*';
	Bullet *b = new Bullet(coord[0] + 2, coord[1], Bullet::UP, ch, PMY);
	bullets.push_front(b);//listԪ����Ԫ���ӵ�ǰ���һ���ӵ�
}

void Myplane::move_bullet() {
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end();) {//�ӵ��ƶ�
		(*iter)->move();
		if ((*iter)->inscreen() == false) {
			delete (*iter);
			bullets.erase(iter++);
		}
		else
			++iter;
	}
}

void Myplane::clear_bullet() {//�ӵ���ײ
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end();) {
		if ((*iter)->get_alive() == false) {
			delete (*iter);
			bullets.erase(iter++);
		}
		else
			++iter;
	}
}

bool Myplane::next_life() {
	if (life > 0) {
		life--;
		alive = 200;
		//blines = 1; 
		return true;
	}
	else
		return false;
}

void Myplane::reduce(Enemy *e) {
	if (alive > 0) {
		for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter) {
			if (e->hurt((*iter)->getPosX(), (*iter)->getPosY()) > 0)//�ӵ���ײ
				(*iter)->kill();
		}
		int dec = 0;
		dec += e->hurt(coord[0], coord[1]);
		dec += e->hurt(coord[0] - 1, coord[1]);
		dec += e->hurt(coord[0] + 1, coord[1]);
		
		alive -= dec;
		if (alive < 0)	alive = 0;
	}
}

int Myplane::hurt(int x, int y) {//��ĳһλ�õ��˺�
	int hurt = 0;
	for (list<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter) {
		hurt += ((*iter)->hurt(x, y));	//�ӵ��˺�
	}
	if (alive > 0 && (x == this->coord[0] && y == this->coord[1])
		|| ((x - 1) == this->coord[0] && y == this->coord[1])
		|| ((x + 1) == this->coord[0] && y == this->coord[1])
		|| ((x - 2) == this->coord[0] && y == this->coord[1])
		|| ((x + 2) == this->coord[0] && y == this->coord[1]))
		hurt += 100;//��ײ�˺�
	return hurt;
}
