#include "var.h"

int
strArrSize(char **str)
{ // size of string array
    int i = 0;
    while (*str++ != NULL) {
        i++;
    }
    printf("%d\n",i);
    return (i - 1);
}

void
arr_free(char **strArr)
{ // free alocated memory to string array
    int i;
    int arr_size = strArrSize(strArr);
    for (i = 0; i < arr_size; i++)
        free(strArr[i]);
    free(strArr);
}


void
find_var(char *s, var_t *v)
{
    char *token,*cp, delim[] = " ";
    int j,k,equal_detect;
    j = 0;
    k = 0;
    equal_detect = 0;
    cp = strdup(s);
    token = strtok(cp,delim);
    while(token != NULL) {
        while (*token != '\0') {
            if (*token == '$'){
                break;
            }
            if (*token == '=') {
                equal_detect = 1;
                token++;
                k = 0;
            }
            switch (equal_detect) {
                case 0 :
                    v->name[j][k] = *token;
                    v->size++;
                    k++;
                    break;
                case 1 :
                    v->content[j][k] = *token;
                    k++;
                    break;
                default :
                    break;
            }
            token++;
        }
        token = strtok(NULL,delim);
        equal_detect = 0;
        j++;
        k = 0;
    }
    free(cp);
    find_type(v);
}

void
find_type(var_t *v)
{
    int i,j;
    char *cp = NULL;

    for (i = 0; i < v->size; i++) {
        cp = strdup(v->content[i]);
        for (j = 0; cp[j] != '\0'; j++) {
            if (cp[j] == '.'){
                v->type[i] = 2;// float
                break;
            } else if (cp[j] >= '0' && cp[j] <= '9'){
                v->type[i] = 1; // int
            } else {
                v->type[i] = 0; // char or *char
            }
        }
        free(cp);
    }
}

/*
if str == while
 char* wh;
 for (str, str != "done", str++) {
    token = strtok(str,""); //strtok without delim
    append(token,wh);
    }
    at the end we have string with only while loop ! genius !
*/

/*
*       TEST
void
make_vars(char *s, var_t *v)
{
    char *token;
    int i,j,k,equal_detect;
    i = 0;
    j = 0;
    k = 0;
    equal_detect = 0;
    token = s;
    while (*token) {
        if (*token == ' '){
            token++;
            j++;
            k = 0;
            equal_detect = 0;
        }
        if (*token == '=') {
            equal_detect = 1;
            token++;
            k = 0;
        }
        switch (equal_detect) {
            case 0 :
                v->name[j][k] = *token;
                break;
            case 1 :
                v->content[j][k] = *token;
                break;
            default :
                break;
        }
        token++;
    }
}
*/
