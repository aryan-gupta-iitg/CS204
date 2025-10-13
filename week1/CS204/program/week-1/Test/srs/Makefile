
CC = gcc

OBJ = ../obj/


all : func prog
	$(CC) $(OBJ)prog.o ../obj/func.o -I ../include -o ../bin/prog 

func :
	gcc -c func.c -o ../obj/func.o

prog : 
	gcc -c prog.c -I ../include -o ../obj/prog.o


clean :
	rm ../obj/*.o


 

