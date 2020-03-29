/*
 * Processus de reflexion sur la réalisation de conditions
 * Partons d'une structure contenant deux tableaux et un int. Les tableaux parle deux même et le type sera défini ainsi :
 * 1 = if
 * 2 = while
 * 3 = for
 * Il faut donc chercher dans le fichier et/ou la string les mots clef et vérifié qu'ils soit suivis de leurs syntaxe respective.
 * C'est à dire qu'ils comportent une condition, un contenu à executé si la condition est vrai et une fin (fi).
 * Si les critères ne sont pas remplie on renverra une erreur
*/

#include <stdio.h>
struct cond {
    char condition[100][50];
    char content[100][250];
    int type;
};
typedef struct cond cond_t;
cond_t splitcond(char str[]) {
    int i;
    while (str[i] != '\0') {
        if ((str[i] == 'i') && (str[++i] == 'f'))
            printf("IF DETECTION");
        printf("%c", str[i]);
        i++;
    }
}
int main() {
    char str[] = "if [a=2];then\n a++\n fi ";
    splitcond(str);
    //printf("%s", str);
}
