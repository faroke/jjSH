#include "jjsh.h"
#include "var.h"
#include "string_arr.h"
#include<sys/wait.h>

char *commands[100];



int
main(void)
{
    char *s = "a=5 b=6";
    var_t v;
    find_var(s,&v);
    printf("%s = %s", v.name[0], v.content[0]);
    return 0;
    /*char usr_cmd[250];
    int exit_sh, a;

    exit_sh = 0;
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
    return 0;*/
}
