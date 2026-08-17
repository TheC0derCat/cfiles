#include<ncurses.h>
int main(void){
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	while(1){
		erase();
		printw("Hello, world!");
		int input = getch();
		switch(input){
			case 'q':
				endwin();
				return 0;
		}
	}
}
