

#ifndef SHELL_INTERPRETER_IF_H
#define SHELL_INTERPRETER_IF_H
#include "var.h"
struct cond {
    int i[3];
    float f[3];
    char c[3][250];
};
typedef struct cond cond_t;
void parse_if(char*, var_t*);
#endif //SHELL_INTERPRETER_IF_H
