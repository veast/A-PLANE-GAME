#include "Bullet.h"
#include <iostream>
using namespace std;

short Bullet::shadow_wait = 0;

void Bullet::move(){
	switch (dir) {
	case DOWN:ypos++; break;
	case UP:ypos--; break;
	}
}

//void Bullet::set_char(char sig){
//	ch = sig;
//}

void Bullet::updata(){
	if (alive)
		battlefield[ypos][xpos] = ch;
}

int Bullet::hurt(int x, int y){
	if (x == xpos && y == ypos){
		switch (kind){
		case PONE:return 10;
		case PTWO:return 20;
		case PMY: return 10;
		default:return 0;
		}
	}
	else
		return 0;
}

bool Bullet::inscreen(){	//judge whether the bullet is in the screen.
	if ((alive) && (xpos >= 0) && (xpos < WIDTH) && (ypos >= 0) && (ypos < HEIGHT)) return true;
	else return false;
}