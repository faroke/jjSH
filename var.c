#include<string.h>
#include"string_arr.h"

//strchr -> first occurrence to char


int strArrSize(char **str) { // size of string array
	int i = 0;
	while (*str++ != NULL) {
		i++;
	}
	return (i - 1);
}

void arr_free(char **strArr) { // free alocated memory to string array
	int i;
	int arr_size = strArrSize(strArr);
	for (i = 0; i < arr_size; i++)
		free(strArr[i]);
	free(strArr);
}

int findVar(char** str) { //it finds '=' symbols from strings like var = 5 (not var=5)
	int i;
	int size;
	int vars;
	vars = 0;
	size = strArrSize(str);
	for (i = 0; i < size; i++) {
			if (strcmp(str[i],"=") == 0)
				vars++;
	}
	if (vars != 0){
		return vars;
	} else {
		return -1;
	}
}

int checkVar(char **str) { //checks if there is '=' symbol in string
	int i,size;
	size = strArrSize(str);
	for (i = 0; i < size; i++) {
		if (strcmp(str[i],"=") == 0) 
			return 0;
		else
			return 1;
	}
}

/*void varr (char **str, var_t w) { // add name and content of variable to type var_t
	int i,size;
	size = strArrSize(str);
	for (i = 0; i < size; i++) {
		if (strcmp(str[i],"=") == 0) {
			w.name = str[i-1];
			w.content = str[i+1];
		}
	}
}*/

/*void addName (char **str, char **res) {
	int i,size,j;
	j = 0;
	size = strArrSize(str);
	for (i = 0; i < size; i++) {
		if (strcmp(str[i],"=") == 0) {
			res[j++] = str[i-1];	
		}
	}
}*/

int main(void) {
	//char **content;
	int i;
	char *buf= NULL; 
	size_t bufzise = 0;
	char **newbuf;
	getline(&buf, &bufzise, stdin);
	newbuf = split_whitespaces(buf);
	int nbvars = 0;
	nbvars = findVar(newbuf);
	arr_free(newbuf);
	free(buf);
    return 0;
}
