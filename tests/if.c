#include "if.h"

int define_type(char *s) {
    if ((s[0] < '0' || s[0] > '9') && s[0] != '$')
        return 0;
    while (*s) {
        if (*s == '.')
            return 2;
        s++;
    }
    return 1;
}

void parse_if(char *s, var_t *v) {
    char *token, *cp, op[4];
    char delimiters[] = " [];";
    int i, t;
    cond_t c;

    cp = strdup(s);
    token = strtok(cp, delimiters);

    token = strtok(NULL, delimiters);
    if (strcmp(token, "-n") == 0 || strcmp(token, "-z") == 0) {
        strcpy(op, token);
    }
    if (token[0] == '$') {
        token++;
        for (i = 0; strcmp(v->name[i], token) != 0; i++);
        switch (v->type[i]) {
            case 1:
                c.i[0] = atoi(v->content[i]);
                t = 1;
                break;
            case 2:
                c.f[0] = atof(v->content[i]);
                t = 2;
                break;
            default:
                strcpy(c.c[0], v->content[i]);
                t = 0;
                break;
        }
        token = strtok(NULL, delimiters);
        strcpy(op, token);
    } else {
        switch (define_type(token)) {
            case 1:
                c.i[0] = atoi(token);
                t = 1;
                break;
            case 2:
                c.f[0] = atof(token);
                t = 2;
                break;
            default:
                break;
        }
        token = strtok(NULL, delimiters);
        strcpy(op, token);
    }
    if (strcmp(op, "-eq") == 0 || strcmp(op, "-ge") == 0 || strcmp(op, "-gt") == 0 ||
        strcmp(op, "-le") == 0 || strcmp(op, "-lt") == 0 || strcmp(op, "-ne") == 0) {
        token = strtok(NULL, delimiters);
        if (token[0] == '$') {
            token++;
            for (i = 0; strcmp(v->name[i], token) != 0; i++);
            switch (v->type[i]) {
                case 1:
                    c.i[1] = atoi(v->content[i]);
                    break;
                case 2:
                    c.f[1] = atof(v->content[i]);
                    break;
                default:
                    exit(-1);
            }
        } else {
            switch (define_type(token)) {
                case 1:
                    c.i[1] = atoi(token);
                    break;
                case 2:
                    c.f[1] = atof(token);
                    break;
                default:
                    exit(-1);
            }
        }
        if (strcmp(op, "-eq") == 0) {
            if (t == 1) {
                if (c.i[0] == c.i[1]) {
                    // TODO perform what's inside
                }
            } else if (t == 2) {
                if (c.f[0] == c.f[1]) {
                    // TODO perform what's inside
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-ge") == 0) {
            if (t == 1) {
                if (c.i[0] >= c.i[1]) {
                    // TODO perform what's inside
                }
            } else if (t == 2) {
                if (c.f[0] >= c.f[1]) {
                    // TODO perform what's inside
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-gt") == 0) {
            if (t == 1) {
                if (c.i[0] > c.i[1]) {
                    // TODO perform what's inside
                }
            } else if (t == 2) {
                if (c.f[0] > c.f[1]) {
                    // TODO perform what's inside
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-le") == 0) {
            if (t == 1) {
                if (c.i[0] <= c.i[1]) {
                    // TODO perform what's inside
                }
            } else if (t == 2) {
                if (c.f[0] <= c.f[1]) {
                    // TODO perform what's inside
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-lt") == 0) {
            if (t == 1) {
                if (c.i[0] < c.i[1]) {
                    // TODO perform what's inside
                }
            } else if (t == 2) {
                if (c.f[0] < c.f[1]) {
                    // TODO perform what's inside
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-ne") == 0) {
            if (t == 1) {
                if (c.i[0] != c.i[1]) {
                    // TODO perform what's inside
                }
            } else if (t == 2) {
                if (c.f[0] != c.f[1]) {
                    // TODO perform what's inside
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }

        } else if (strcmp(op, "=") == 0 || strcmp(op, "!=") == 0 || strcmp(op, "-n") == 0 || strcmp(op, "-z") == 0) {
            token = strtok(NULL, delimiters);
            if (token[0] == '$') {
                token++;
                for (i = 0; strcmp(v->name[i], token) != 0; i++);
                strcpy(c.c[1], v->content[i]);
            } else {
                strcpy(c.c[1], token);
            }
            if (strcmp(op, "=") == 0) {
                if (strcmp(c.c[0], c.c[1]) == 0) {
                    // TODO perform what's inside
                }
            } else if (strcmp(op,"!=") == 0) {
                if (strcmp(c.c[0],c.c[1]) != 0) {
                    // TODO perform what's inside
                }
            } else if (strcmp(op,"-n") == 0) {
                if (c.c[1] != NULL) {
                    // TODO perform what's inside
                }
            } else if (strcmp(op,"-z") == 0) {
                if (c.c[1] == NULL) {
                    // TODO perform what's inside
                }
            }


        }
        free(cp);
    }
}
/*
 * if [[ $a >= $b]]; then     if [[ $a -ge $b ]];   if [[ 4 -ge $a ]];   if [[ $a -ge 4 ]];  if [[ 4 -lt 5 ]];
 *  $a = $b
 *  fi
 */
