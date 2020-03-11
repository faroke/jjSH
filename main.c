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
// https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
void cat (char *arg) {
        int c;
        FILE *file;
        file = fopen(arg, "r");
        if (file) {
        	while ((c = getc(file)) != EOF)
                	putchar(c);
        fclose(file);
	}
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

int main(int argc, char *argv[]) {
	if (argc == 1) {
                size_t entry;
		char *buf;
		size_t bufsize = 0;
		initShell();
		print("\n");
		while ( 1 ) {
			prompt();
			getline(&buf, &bufsize, stdin);
		}
	}
        else 
                execl("/bin/bash", "/bin/bash", argv[1], NULL);
        //execl est temporaire en attendant l analyse des fichiers
	return 0;

}
