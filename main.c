#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<dirent.h>
#include<string.h>

void clear(){
	printf("\033[H\033[J");
}

void print(char *str) {
	while (*str){
		write(1,str++,1);
	}
}

void initShell() {
	clear();
	print("Welcome in JJSH!\n\n\n");
	sleep(1);
	clear();
}

void pwd () {
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	printf("\n%s\n", cwd);
}

int prompt() {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s $ ", cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}
	return 0;
}

void ls(char *d) {
	DIR *dir;
	dir = opendir(d);
	struct dirent *dp;
	char *file_name;
	while((dp=readdir(dir)) != NULL) {
		file_name = dp->d_name;
		if (!strcmp(file_name,".") || !strcmp(file_name, "..") || file_name[0] == '.') {
			//nothing
		} else {
		printf("%s  ",file_name);
		}
	}
	printf("\n");
	prompt();
	closedir(dir);
}

void findQuote(char *str) {
	int nbr;

	nbr = 0; // quotes found 
	while(str) {
		if (*str == '\'')
			nbr++;
		str++;
	}
	if (nbr%2 != 2) 
		print("\n> ");
}

void echo(char *str) {
	print(str); 
}

void cd(char *arg) {
	if (access(arg, F_OK) != -1)
		chdir (arg);
	else
		printf("No such file or directory");
}

int main(void) {
	size_t entry;
	char *buf;
	char *str;
	size_t bufsize = 0;
	initShell();
	print("\n");
	//prompt();
	cd("/toto");
	pwd();
	return 0;
}

