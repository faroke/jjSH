

#ifndef SHELL_INTERPRETER_IF_H
#define SHELL_INTERPRETER_IF_H
#include "var.h"
#include <unistd.h>
#include "string_arr.h"
#include "jjsh.h"
struct cond {
    int i[3];
    float f[3];
    char c[3][250];
};
typedef struct cond cond_t;
char *get_if_content(char*);
void parse_if(char*, var_t*);
#endif //SHELL_INTERPRETER_IF_H
