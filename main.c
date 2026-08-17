#include<ncurses.h>
#include<dirent.h>
int main(void){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	int cursor = 0;
	while(1){
		// set vars
		struct dirent *de;
		DIR *dr = opendir(".");
		char *current_file_name;
		int i = 0;
		// draw
		erase();
		while ((de = readdir(dr)) != NULL){
			if(i == cursor)
				current_file_name = de->d_name;
			printw("%s\n", de->d_name);
			i++;
		}
		move(cursor, 0);
		// get input
		char input = getch();
		switch(input){
			case 'q': endwin(); return 0;
			case 'j': cursor++; break;
			case 'k': if(cursor > 0) cursor--; break;
		}
		// free stuff
		closedir(dr);
	}
}
