#include <conio.h>
#include<list>
#include "Game_run.h"
#include "Display.h"
using namespace std;

char battlefield[HEIGHT][WIDTH];

int Game_run::time_wait = 40;

Game_run::Game_run():player(24,16){
	enemy_born = 0;
	for (int i = 0; i < 14; i++)
		states[i] = 1;
}
Game_run::~Game_run(){
	for (list<Enemy*>::iterator iter = enemy_list.begin(); iter != enemy_list.end();){
		delete (*iter);
		enemy_list.erase(iter++);
	}
}
void  Game_run::check_keyboard_input(){
	states[UP] = GetAsyncKeyState('W');
	states[DOWN] = GetAsyncKeyState('S');
	states[LEFT] = GetAsyncKeyState('A');
	states[RIGHT] = GetAsyncKeyState('D');
	states[FIRE] = GetAsyncKeyState('J');
	states[RESTART] = GetAsyncKeyState('R');
	states[PAUSE] = GetAsyncKeyState(' ');
	
	SHORT exi = GetAsyncKeyState('T');
	if (exi == 1){
		system("cls");
		game_interrupt();
		system("pause");
		exit(0);
	}
}
void Game_run::update(){
	for (list<Enemy*>::iterator iter = enemy_list.begin(); iter != enemy_list.end(); ++iter){
		(*iter)->update();
	}
	update_field(player.score, player.alive, player.life);
}

void Game_run::add_enemy(){
	int sx = rand() % 48;
	int k = rand() % 100;
	enemy_born++;
	if (enemy_born == time_wait){
		Enemy *p;
		if (k > 80)  p = new Enemy(sx, 0, 1);
		else p = new Enemy(sx, 0, 0);
		if (p == NULL){ cerr << "Space error!\n"; exit(1); }
		enemy_list.push_front(p);
		enemy_born = 0;
	}
}

void Game_run::move_clear_enemy(){//同时移动并清理出界
	for (list<Enemy*>::iterator iter = enemy_list.begin(); iter != enemy_list.end();){
		(*iter)->move();
		if ((*iter)->coord[0]<0 || (*iter)->coord[0]>=WIDTH || (*iter)->coord[1]>=HEIGHT){
			delete (*iter);
			enemy_list.erase(iter++);
		}
		else
			++iter;
	}
}

bool Game_run::check_crash(){
	for (list<Enemy*>::iterator iter = enemy_list.begin(); iter != enemy_list.end();){
		(*iter)->reduce_life(player);
		player.reduce(*iter);
		for (list<Bullet*>::iterator iterb = (*iter)->get_bullets().begin(); iterb != (*iter)->get_bullets().end();iterb++){//子弹碰子弹
			if (player.hurt((*iterb)->getPosX(), (*iterb)->getPosY()) > 0){
				if ((*iterb)->kind == 0||(*iterb)->kind == 1)
					(*iterb)->kill();
			}
		}
		(*iter)->clear_bullet();
		player.clear_bullet();
		if ((*iter)->still_alive() == false){
			player.gain_score((*iter)->give_score());
			if ((*iter)->give_score() == 10000){ 
				delete (*iter);
				enemy_list.erase(iter++);
				return true; 
			}
			delete (*iter);
			enemy_list.erase(iter++);
		}
		else
			++iter;
	}
	return false;
}

bool Game_run::check_life(){
	if (player.alive <= 0 && player.life <= 0){
		Sleep(1000);
		system("cls");
		game_over(player.score);
		system("pause>nul");
		return false;
	}
	if (player.alive <= 0 && player.life > 0){
		Sleep(1000);
		if (player.next_life()){
			for (list<Enemy*>::iterator iter = enemy_list.begin(); iter != enemy_list.end();){
				for (list<Bullet*>::iterator iterb = (*iter)->get_bullets().begin(); iterb != (*iter)->get_bullets().end(); iterb++)
					(*iterb)->kill();
				if ((*iter)->coord[1] > 20){
					delete (*iter);
					enemy_list.erase(iter++);
				}
				else iter++;
			}
		}
		player.coord[0] = 25;
		player.coord[1] = 31;
		update_field(player.score, player.alive, player.life);
	}
	return true;
}

void Game_run::pause(){
	if ((states[PAUSE]) < 0)
		system("pause>nul");
}

int Game_run::game_run(){
	system("mode con cols=70 lines=45");
	const_display();
	int time_count = 0;

	updateField();
	update();
	while (1){
		time_count++;
		if (time_count == 40000 && time_wait >= 7){
			time_count = 0;
			time_wait--;
		}
		updateField();
		if(check_life()==0)return 0;
	
		add_enemy();
	
		check_keyboard_input();
		pause();

		if ((states[FIRE]) < 0 && player.still_alive()) player.shoot();//射击
		if (player.still_alive()) player.move(states);//移动

		player.move_bullet();
		check_crash();
	
		if(time_count % 20 == 0)
			move_clear_enemy();

		check_crash();
		player.update();
		update();
	}
}
void Game_run::updateField() {
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			battlefield[i][j] = ' ';
}