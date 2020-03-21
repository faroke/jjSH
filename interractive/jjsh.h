//
// Created by user on 3/21/20.
//

#ifndef SHELL_INTERPRETER_JJSH_H
#define SHELL_INTERPRETER_JJSH_H
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
extern int child_count;
extern char *commands[100];
void execute(char**);
void parse(char*,char**,int);
void clear();
void initShell();
int prompt();
#endif //SHELL_INTERPRETER_JJSH_H
