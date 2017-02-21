
#include "Display.h"
#include "Game_run.h"

using namespace std;

int main(){

	hideCursor();
	startDisplay();
	
	Game_run game;
	game.game_run();

}