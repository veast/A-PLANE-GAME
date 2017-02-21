void hideCursor();
void gotoxy(int x, int y);
void getxy(int &x, int &y);

void startDisplay();

void update_field(int score, int blood, int life);
void const_display();

void game_interrupt();
void game_over(int socre);
void game_win(int s);