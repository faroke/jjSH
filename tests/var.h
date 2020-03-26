#ifndef SHELL_INTERPRETER_VAR_H
#define SHELL_INTERPRETER_VAR_H

#include "string_arr.h"
#include <string.h>
struct var {
    char name[100][50];
    char content[100][250];
    int type[100];
};
typedef struct var var_t;
void find_var(char*, var_t*);
void make_vars(char*, var_t*);
#endif //SHELL_INTERPRETER_VAR_H
