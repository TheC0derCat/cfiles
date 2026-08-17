#include<ncurses.h>
#include<dirent.h>
int main(void){
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	int cursor = 0;
	while(1){
		struct dirent *de;
		DIR *dr = opendir(".");
		erase();
		int i = 0;
		while ((de = readdir(dr)) != NULL){
			printw("%c%s\n", ((i == cursor) ? '=' : ' '),de->d_name);
			i++;
		}
		char input = getch();
		switch(input){
			case 'q': endwin(); return 0;
			case 'j': cursor++; break;
			case 'k': if(cursor > 0) cursor--; break;
		}
		closedir(dr);
	}
}
