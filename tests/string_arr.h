#ifndef SHELL_INTERPRETER_STRING_ARR_H
#define SHELL_INTERPRETER_STRING_ARR_H
#include<stdlib.h>
#include<stdio.h>
int WHITESPACE (char);
int	word_size(char*);
int	word_count(char*);
char **split_whitespaces(char*);
int		count_words(char*);
char	*malloc_word(char*);
char	**ft_split(char*);

#endif //SHELL_INTERPRETER_STRING_ARR_H
