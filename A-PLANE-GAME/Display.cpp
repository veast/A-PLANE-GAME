#include <iostream>
#include <windows.h>
#include <conio.h>	
#include "SomeConst.h"

using namespace std;

void hideCursor(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = sizeof(cci);
	SetConsoleCursorInfo(hOut, &cci);
}

void gotoxy(int x, int y){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

void getxy(int &x, int &y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hOut, &screen_buffer_info);

	x = screen_buffer_info.dwCursorPosition.X;
	y = screen_buffer_info.dwCursorPosition.Y;
}

void startDisplay(){//���ÿ���̨��ɫ����������Ըı���Ļ���������ɫ
	system("cls");
	gotoxy(56, 5);
	system("color 03");
	cout<<"�ɻ���Ϸ";
	Sleep(800);
	gotoxy(52, 8);
	cout << "Are you ready???";
	Sleep(800);
	gotoxy(51, 15);
	cout<<"�밴�������ʼ��Ϸ";
	Sleep(300);
	cout << "��";
	Sleep(300);
	cout << "��";
	Sleep(300);
	cout << "��";
	_getch();
	
	
	//_getch();
}

void update_field(int score, int blood, int life){
	gotoxy(0, 0);
	cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|�÷֣�" << score << endl;
	for (int i = 0; i < HEIGHT; i++){
		cout<<"|";
		for (int j = 0; j < WIDTH; j++){
			cout << battlefield[i][j];
		}
		cout << "|";
		cout << endl;
	}
	cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	//cout << "\tѪ����" << blood << endl;
	printf("\tѪ����%3d\n", blood);
	cout << endl;
	cout << "\t����ʣ�ࣺ" << life << endl;

}

void const_display(){
	gotoxy(0,38);
	cout << "\t���� W A S D \t���: J" << endl;
	cout << endl;
	cout << "\t��ͣ��Ϸ��space"<<endl;
	cout << endl;
	cout << "\t������Ϸ�� ����T" << endl;
}

void game_interrupt(){
	gotoxy(0, 14);
	cout << "\t\t\t\t  Game over\n\t\t\t  You have stopped the game!" << endl;
	gotoxy(0, 30);
}

void game_over(int score){
	gotoxy(0, 14);
	cout << "\t\t\t\t  Game over\n\t\t\t  Your Total Score " << score << endl;;
	gotoxy(0, 30);
}

void game_win(int s){
	gotoxy(0, 14);
	cout << "\t\t\t\t  You Win!!\n\t\t\t  Your Final Score :" << s << endl;
	gotoxy(0, 17);
	cout << "\t yeah! " << endl;
	gotoxy(0, 30);
	Sleep(5000);
}