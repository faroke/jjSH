
#include "var.h"
#include <stddef.h>

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
    char *token,*cp;
    int i,j,k,equal_detect;
    i = 0;
    j = 0;
    k = 0;
    equal_detect = 0;
    cp = strdup(s);
    token = strtok(cp," ");
    while(token != '\0') {
        while (*token != '\0') {
            if (*token == '=') {
                equal_detect = 1;
                token++;
                k = 0;
            }
            switch (equal_detect) {
                case 0 :
                    v->name[j][k] = *token;
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
        token = strtok(NULL," ");
        equal_detect = 0;
        j++;
        k = 0;
    }
    free(cp);
}

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
