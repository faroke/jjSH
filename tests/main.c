#include "jjsh.h"
#include "var.h"
#include "string_arr.h"
#include "if.h"
#include<sys/wait.h>
char *commands[100];



int
main(void)
{
    char *s = "a=q b=q $a=b";
    var_t v;
    v.size = 0;
    find_var(s,&v);
   // printf("%s = %s type = %d\n", v.name[1], v.content[1], v.type[1]);
    s = "if [[ $a = $b ]]; \nthen\n$a=f\necho $a\necho $b\nfi\n";
    //execlp("ls","ls","-l",(char*) NULL);
    parse_if(s,&v);
    /*char *test = "if [[;lkd;flk]]; then \n echo $a\n echo $b\n fi $b='helllllllloooooo'";
    char *tt;
    tt = get_if_content(test);
    printf("%s", tt);
    free(tt);*/
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
