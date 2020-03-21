#include "jjsh.h"
#include<sys/wait.h>

char *commands[100];

int main(void) {
    char usr_cmd[250];

    int exit_sh = 0,a;


    initShell();
    while (1) {
        prompt();
        memset(&usr_cmd[0], 0, sizeof(usr_cmd));
        a = scanf("%[^\n]%*c", usr_cmd);
        if (a < 0)
            exit(1);
        if (strlen(usr_cmd) == 0 && usr_cmd[0] == '\0') {
            while ((getchar()) != '\n'); //don't print prompt infinitely, wait for \n
        }
        parse(usr_cmd, commands, exit_sh);
        for (int i = 1; i <= child_count; i++)
            wait(0);
    }
    return 0;
}
