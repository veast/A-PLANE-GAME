#pragma once

const int WIDTH = 48;
const int HEIGHT = 32;

extern char battlefield[HEIGHT][WIDTH];

class Myplane;
class Game_run;
class Bullet;
class Magic;

enum ENEMYKIND{ FLIVVER, BIGONE };

enum KEYBOARDSTATE{ RIGHT, LEFT, DOWN, UP, FIRE, RESTART, PAUSE, EXIT };

enum BKIND { PONE = 0, PTWO, PMY };
