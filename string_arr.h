#include<stdlib.h>
#include<stdio.h>

int WHITESPACE (char c) {
	if (c == '\t' || c == '\n' || c == ' ')
		return 1;
	else
		return 0;
}

int	word_size(char *str) {
	int i;

	i = 0;
	while (WHITESPACE(str[i]) && str[i] != '\0')
		str++;
	while (!(WHITESPACE(str[i])) && str[i] != '\0')
		i++;
	return (i);
}

int	word_count(char *str) {
	int words;
	int i;

	i = 0;
	words = 0;
	while (str[i] != '\0') {
		while (WHITESPACE(str[i]) && str[i] != '\0')
			i++;
		while (!(WHITESPACE(str[i])) && str[i] != '\0')
			i++;
		while (WHITESPACE(str[i]) && str[i] != '\0')
			i++;
		words++;
	}
	return (words);
}

char **split_whitespaces(char *str) {
	int	wcount;
	int	words_entered;
	int	i;
	char **words;
	char *word;

	i = 0;
	words_entered = 0;
	wcount = word_count(str);
	words = (char**)malloc(sizeof(char*) * (wcount + 1));
	while (words_entered < wcount)
	{
		word = (char*)malloc(sizeof(char) * (word_size(str) + 1));
		while (WHITESPACE(str[0]) && str[0] != '\0')
			str++;
		while (!(WHITESPACE(str[0])) && str[0] != '\0')
			word[i++] = *str++;
		word[i] = '\0';
		words[words_entered++] = word;
		i = 0;
	}
	words[wcount] = 0;
	free(word);
	return (words);
}




