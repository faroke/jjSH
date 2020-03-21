CC=gcc

jjsh:	main.o jjsh.o jjsh.h
		$(CC) main.o jjsh.o -o jjsh

main.o: main.c jjsh.h

jjsh.o: jjsh.c jjsh.h

clean:
	@rm -f *o
	@rm -f core
	@rm -f *~
