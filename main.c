#include<ncurses.h>
#include<dirent.h>
int main(void){
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	while(1){
		struct dirent *de;
		DIR *dr = opendir(".");
		erase();
		while ((de = readdir(dr)) != NULL)
			printw("%s\n", de->d_name);
		int input = getch();
		switch(input){
			case 'q':
				endwin();
				return 0;
		}
		closedir(dr);
	}
}
