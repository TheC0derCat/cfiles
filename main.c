#include<ncurses.h>
int main(void){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	printw("Hello, world!");
	getch();
	endwin();
	return 0;
}
