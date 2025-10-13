CC = gcc

INCLUDE = ../include

OBJ = ../obj/

all : func
	$(CC) prog.c $(OBJ)func.o -I $(INCLUDE) -o../bin/prog

func : 
	gcc -c func.c -o ../obj/func.o

AR : 
	ar rcs ../ar/libfunc.a ../obj/func.o

clean :
	rm ../obj/*.o

gcclib:
	gcc prog.c -I ../include -L ../ar/ -lfunc -o ../bin/prog