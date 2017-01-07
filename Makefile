 SRC=$(wildcard *.c)
 OBJ=$(subst .c,.o,$(SRC))
 PROG=prog
$(PROG): $(OBJ)
	gcc -Wall -ansi -std=c99 -pedantic  $^ -o $@ -lSDL -lSDL_ttf
main.o: main.c
	gcc -c -lSDL -lSDL_ttf -Wall -ansi -std=c99 -pedantic $< -o $@
%.o:%.c %.h
	gcc -c -lSDL -lSDL_ttf -Wall  $< -o $@


.PHONY: clean 

clean:
	rm -f *.o
	rm -f *~



