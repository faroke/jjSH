CC = gcc

jjsh:	main.o jjsh.o string_arr.o var.o if.o convert.o
		$(CC) main.o jjsh.o string_arr.o var.o if.o convert.o -o jjsh

main.o:	main.c jjsh.h var.h

jjsh.o:	jjsh.c jjsh.h

string_arr.o:	string_arr.c string_arr.h

var.o:		var.c var.h

if.o:		if.c if.h

convert.o:	convert.c convert.h

clean:
		/bin/rm -f *.o
		/bin/rm -f core
		/bin/rm -f *~

.PHONY: all clean
