#include<ncurses.h>
#include<form.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
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
		printw("%d.%s\n", cursor, getcwd(s, sizeof(s)));
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
			case 'n':
				char new_file_name[100];
				strcpy(new_file_name, current_file_name);
				while(1) {
					erase();
					addstr(new_file_name);
					int input2 = getch();
					switch(input2){
						case '\n':
							rename(current_file_name, new_file_name);
							goto stuff;
						case KEY_BACKSPACE:
							new_file_name[strlen(new_file_name)-1] = '\0';
							break;
						default:
							new_file_name[strlen(new_file_name)] = input2;
							break;
					}
				}
				break;

		}
stuff:
		if(cursor >= (dirlen))
			cursor = dirlen;
		// free stuff
		closedir(dr);
	}
}
