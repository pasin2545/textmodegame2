#include<stdio.h>
#include<windows.h>
#include<conio.h>

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void del(int x, int y) {
	gotoxy(x, y);
	printf("        ");
}
void draw_ship(int x, int y) {
	x = max(x, 0);
	y = max(y, 0);
	x = min(x, 80);
	y = min(y, 25);
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}
int main()
{
	setcursor(0);
	int i = 0, bullet[5] = { 0,0,0,0,0 }, xbullet[5], showbull[5] = { 0,0,0,0,0 };
	int x = 0, y = 20, direc = 0;
	char ch = ' ';
	char ch2 = ' ';
	draw_ship(x, y);
	do {
		if (direc == 1) {
			setcolor(2, 0);
			del(x, y);
			draw_ship(--x, y);
			if (x > 80) {
				x = 80;
			}
			Sleep(100);
		}
		if (direc == 2) {
			setcolor(2, 0);
			del(x, y);
			draw_ship(++x, y);
			if (x > 80) {
				x = 80;
			}
			Sleep(100);
		}
		if (direc == 3) {
			setcolor(2, 0);
			draw_ship(x, y);
		}
		//ยิงเริ่มต้น
		if (_kbhit()) {
			ch = _getch();
			if (ch == ' ') {
				if (bullet[i] == 0) {
					setcolor(6, 0);
					bullet[i] = 19;
					xbullet[i] = x;
				}
				i++;
				if (i > 4) {
					i = 0;
				}
				fflush(stdin);
			}
		}
		//ยาน
		//เดินซ้าย
		if (ch == 'a') {
			direc = 1;
		}
		//เดินขวา
		if (ch == 'd') {
			direc = 2;
		}
		if (ch == 's') {
			direc = 3;
		}
		for (int i = 0; i < 5; i++) {
			if (bullet[i] > 0){
					setcolor(6, 0);
					gotoxy(xbullet[i], bullet[i]);
					printf("  ||");
					Sleep(25);
					showbull[i] = 1;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (bullet[i] > 0) {
					setcolor(6, 0);
					gotoxy(xbullet[i], bullet[i]);
					printf("    ");
					Sleep(10);
			}
		}
		for (int i = 0; i < 5; i++) {
			if (bullet[i] > 0) {
				bullet[i]--;
			}
			else {
				bullet[i] = 0;
			}
			if (bullet[i] == 1) {
				showbull[i] = 0;
			}
		}
	} while (ch != 'x');
	return 0;
}