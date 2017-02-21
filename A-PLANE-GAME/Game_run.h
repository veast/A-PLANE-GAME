#ifndef _GAME_RUN_
#define _GAME_RUN_

#include <iostream>
#include <windows.h>
#include "SomeConst.h"
#include "Myplane.h"
#include "Enemy.h"

#include<stdlib.h>

using namespace std;

class Game_run{
private:
	short enemy_born;
	Myplane player;
	SHORT states[14];//key state
	list<Enemy*>  enemy_list;

	static int time_wait;
public:
	Game_run();
	~Game_run();

	int game_run();//run the game
	void check_keyboard_input();//check the keyboard input
	void update();//update everything
	
	void add_enemy();
	void move_clear_enemy();

	bool check_crash();
	bool check_life();


	void pause();

	void updateField();
};
#endif