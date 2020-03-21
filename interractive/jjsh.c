#include "jjsh.h"



//global variables :
pid_t pid;
int child_count = 0;

void execute(char **str) {
    pid = fork();
    if (pid == 0) {
        if (execvp(*str,str) < 0) {
            printf("Command was %s\n", *str);
            printf("Do not use that again and RTFM!\n");
            exit(1);
        }
    }
}

void parse(char *s, char **str, int exit_sh) {
    int detect, proc_str, exit_shell;
    char **tmp;

    detect = 0;
    proc_str = 0;
    exit_shell = exit_sh;
    tmp = str;
    while (*s != '\0') {
        str = tmp;
        while (detect == 0 && *s != '\0') {
            while (*s == ' ' || *s == '\n' || *s == '\t' || *s == ';') {
                if (*s == ';' && proc_str == 1) {
                    detect = 1;
                    *s = '\0';
                    s++;
                    break;
                }
                *s = '\0';
                s++;
            }
            if (detect == 1 || *s == '\0') {
                break;
            }
            *str = s;
            proc_str = 1;
            str++;

            while(*s != '\0' && *s != '\t' && *s != ' ' && *s != '\n') {
                if (*s == ';') {
                    detect = 1;
                    *s = '\0';
                    s++;
                    break;
                }
                s++;
            }
        }
        if (proc_str == 1) {
            *str = '\0';
            if (strcmp(commands[0], "exit") == 0)
                exit_shell = 1;
            if (strcmp(commands[0], "exit") != 0) {
                child_count++;
                execute(commands);
            }
            detect = 0;
            proc_str = 0;
            if (exit_shell == 1 && *s == '\0') {
                exit(0);
            }
        } else
            printf("Why you do that?\n");
    }
}

void clear(){
    printf("\033[H\033[J");
}

int prompt() {
    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s $ ", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

void initShell() {
    clear();
    printf("Welcome in JJsh!\n\n\n");
    sleep(1);
    clear();
}

