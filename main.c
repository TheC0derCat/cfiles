#include<ncurses.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
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
		int dirlen = 0;	
		// draw
		erase();
		char s[100];
		printw("%d: %s\n", cursor, getcwd(s, sizeof(s)));
		while ((de = readdir(dr)) != NULL){
			if(dirlen == cursor)
				current_file_name = de->d_name;
			if(de->d_name[0] != '.'){
				printw("%d.%s\n", dirlen, de->d_name);
				dirlen++;
			}
			i++;
		}
		if(cursor >= (dirlen))
			cursor = dirlen;
		move(cursor + 1, 0);
		// get input
		char input = getch();
		switch(input){
			case 'q': endwin(); return 0;
			case 'j': cursor++; break;
			case 'k': cursor -= cursor > 0; break;
			case 'h': chdir(".."); break;
			case 'l':
				if(chdir(current_file_name) != 0){
					erase();
					FILE *fp = fopen(current_file_name, "r");
					char ch;
					while ((ch = fgetc(fp)) != EOF)
						addch(ch);
					fclose(fp);
					getch();

				}
				break;
			case 'd':
				erase();
				printw("Are you sure you want to delete %s? (y/n)", current_file_name);
				if(getch() == 'y')
					remove(current_file_name);
				break;
		}
		if(cursor >= (dirlen))
			cursor = dirlen;
		// free stuff
		closedir(dr);
	}
}
