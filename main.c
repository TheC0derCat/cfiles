#include<ncurses.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
char * read_file_content(char *file){
	char *content = malloc(1 * sizeof(char));
	int content_len = 0;
	FILE *fp = fopen(file, "r");
	char ch;
	while ((ch = fgetc(fp)) != EOF){
		content[content_len++] = ch;
		content = realloc(content, (content_len + 1) * sizeof(char));
	}
	content[content_len] = '\0';
	fclose(fp);
	return content;
}
void write_file_content(char *file, char *content){
	FILE *fp = fopen(file, "w");
	fprintf(fp, "%s", content);
	fclose(fp);
}
int main(void){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	int cursor = 0;
	char yanked_file_name[100];
	char yanked_file_path[200];
	while(1){
		// set vars
		struct dirent *de;
		DIR *dr = opendir(".");
		char *current_file_name;
		int i = 0;
		int dirlen = 0;	
		// draw
		erase();
		char wd[100];
		printw("%d.%s\n", cursor, getcwd(wd, sizeof(wd)));
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
					char * content = read_file_content(current_file_name);
					addstr(content);
					free(content);
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
			case 'y':
				strcpy(yanked_file_name, current_file_name);
				sprintf(yanked_file_path, "%s/%s", wd, yanked_file_name);
				break;
			case 'c':
				char * content = read_file_content(yanked_file_path);
				write_file_content(yanked_file_name, content);
				free(content);
				break;
			case 'm':
				char * content2 = read_file_content(yanked_file_path);
				write_file_content(yanked_file_name, content2);
				free(content2);
				remove(yanked_file_path);
				break;


		}
stuff:
		if(cursor >= (dirlen))
			cursor = dirlen;
		// free stuff
		closedir(dr);
	}
}
