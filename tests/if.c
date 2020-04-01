
#include "if.h"
///https://stackoverflow.com/questions/27160073/replacing-words-inside-string-in-c
char
*replace (char *sentence, char *find, char *replace)
{
    char *dest = malloc (strlen(sentence)-strlen(find)+strlen(replace)+1);
    char *ptr;

    strcpy (dest, sentence);
    ptr = strstr (dest, find);
    if (ptr)
    {
        memmove (ptr+strlen(replace), ptr+strlen(find), strlen(ptr+strlen(find))+1);
        strncpy (ptr, replace, strlen(replace));
    }
    return dest;
}

void
find_and_replace(char **s, var_t *v, char tmp[10][25]){
    int i,j,k,size;

    char *str = strdup(*s);
    i = 0;
    k = 0;
    while (*str++) {
        if (*str == '$'){
            while (*str != ' '){
                if (*str == '\0')
                    break;
                str++;
                tmp[i][k++] = *str;
                str++;
            }
            tmp[i][k] = '\0';
            i++;
            k = 0;
        }
    }

    for (j = 0; j < i; j++) {
        for (k = 0; strcmp(v->name[k], tmp[j]) != 0; k++);
        *s = replace(*s,tmp[j],v->content[k]);
        *s = replace(*s,"$","");
    }
}

int
define_type(char *s)
{
    if ((s[0] < '0' || s[0] > '9') && s[0] != '$')
        return 0;
    while (*s) {
        if (*s == '.')
            return 2;
        s++;
    }
    return 1;
}

char**
empty_str(char *str[10]){
    int i;
    for (i = 0; i < 10; i++){
        str[i] = NULL;
    }
    return str;
}

void
parse_if(char *s, var_t *v)
{
    char *token, *cp, op[4], *if_c = NULL, *tmp;
    char delimiters[] = " [];", vv[10][25];
    int i, t, j;
    cond_t c;
    t = -1;

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
                strcpy(c.c[0],token);
                break;
        }
        token = strtok(NULL, delimiters);
        // strcpy(op, token); NOT SURE

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
                    perror("STRANGE ISN'T IT?");
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
                    perror("STRANGE ISN'T IT?");
                    exit(-1);
            }
        }
        //free(cp);
        if (strcmp(op, "-eq") == 0) {
            if (t == 1) {
                if (c.i[0] == c.i[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else if (t == 2) {
                if (c.f[0] == c.f[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");

                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                            free(if_c);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-ge") == 0) {
            if (t == 1) {
                if (c.i[0] >= c.i[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else if (t == 2) {
                if (c.f[0] >= c.f[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-gt") == 0) {
            if (t == 1) {
                if (c.i[0] > c.i[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else if (t == 2) {
                if (c.f[0] > c.f[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-le") == 0) {
            if (t == 1) {
                if (c.i[0] <= c.i[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else if (t == 2) {
                if (c.f[0] <= c.f[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-lt") == 0) {
            if (t == 1) {
                if (c.i[0] < c.i[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else if (t == 2) {
                if (c.f[0] < c.f[1]) {
                    cp = strdup(s);
                    token = strtok(cp,"\n");
                    while (*token != 't' && *token++ != 'h'){
                        if (*token == '\0')
                            token = strtok(NULL,"\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token,"fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL,"\n");
                    }
                    // TODO if it is a variable
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
        } else if (strcmp(op, "-ne") == 0) {
            if (t == 1) {
                if (c.i[0] != c.i[1]) {
                    cp = strdup(s);
                    token = strtok(cp, "\n");
                    while (*token != 't' && *token++ != 'h') {
                        if (*token == '\0')
                            token = strtok(NULL, "\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token, "fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL, "\n");
                    }
                    // TODO if it is a variable
                }
            } else if (t == 2) {
                if (c.f[0] != c.f[1]) {
                    cp = strdup(s);
                    token = strtok(cp, "\n");
                    while (*token != 't' && *token++ != 'h') {
                        if (*token == '\0')
                            token = strtok(NULL, "\n");
                    }
                    token = strtok(NULL, "\n");

                    while (strcmp(token, "fi") != 0) {
                        if (token[0] != '$') {
                            if_c = strdup(token);
                            find_and_replace(&if_c, v, vv);
                            parse(if_c, commands, 0);
                        }
                        token = strtok(NULL, "\n");
                    }
                    // TODO if it is a variable
                }
            } else {
                perror("BAD COMPARISON");
                exit(-1);
            }
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
                cp = strdup(s);
                token = strtok(cp,"\n");
                while (*token != 't' && *token++ != 'h'){
                    if (*token == '\0')
                        token = strtok(NULL,"\n");
                }
                token = strtok(NULL, "\n");

                while (strcmp(token,"fi") != 0) {
                    if (token[0] != '$') {
                        if_c = strdup(token);
                        find_and_replace(&if_c, v, vv);
                        parse(if_c, commands, 0);
                    }
                    token = strtok(NULL,"\n");
                }
                // TODO if it is a variable
            }
        } else if (strcmp(op,"!=") == 0) {
            if (strcmp(c.c[0],c.c[1]) != 0) {
                cp = strdup(s);
                token = strtok(cp,"\n");
                while (*token != 't' && *token++ != 'h'){
                    if (*token == '\0')
                        token = strtok(NULL,"\n");
                }
                token = strtok(NULL, "\n");

                while (strcmp(token,"fi") != 0) {
                    if (token[0] != '$') {
                        if_c = strdup(token);
                        find_and_replace(&if_c, v, vv);
                        parse(if_c, commands, 0);
                    }
                    token = strtok(NULL,"\n");
                }
                // TODO if it is a variable
            }
        } else if (strcmp(op,"-n") == 0) {
            if (c.c[1] != NULL) {
                cp = strdup(s);
                token = strtok(cp,"\n");
                while (*token != 't' && *token++ != 'h'){
                    if (*token == '\0')
                        token = strtok(NULL,"\n");
                }
                token = strtok(NULL, "\n");

                while (strcmp(token,"fi") != 0) {
                    if (token[0] != '$') {
                        if_c = strdup(token);
                        find_and_replace(&if_c, v, vv);
                        parse(if_c, commands, 0);
                    }
                    token = strtok(NULL,"\n");
                }
                // TODO if it is a variable
            }
        } else if (strcmp(op,"-z") == 0) {
            if (c.c[1] == NULL) { //Does not work
                printf("BIP");
                cp = strdup(s);
                token = strtok(cp,"\n");
                while (*token != 't' && *token++ != 'h'){
                    if (*token == '\0')
                        token = strtok(NULL,"\n");
                }
                token = strtok(NULL, "\n");

                while (strcmp(token,"fi") != 0) {
                    if (token[0] != '$') {
                        if_c = strdup(token);
                        find_and_replace(&if_c, v, vv);
                        parse(if_c, commands, 0);
                    }
                    token = strtok(NULL,"\n");
                }
                // TODO if it is a variable
            }
        }
    }
    free(cp);
}


