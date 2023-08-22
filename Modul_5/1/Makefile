all: prog1 prog2 prog3
prog1: main.o libdiv.a
	gcc main.o -L. -ldiv -o prog1

prog2: main.o libdiv_dyn.so
	gcc main.o -L. -ldiv_dyn -o prog2

prog3:
	gcc main2.c -o prog3 -ldl

main.o: main.c
	gcc -c main.c

libdiv.a: div.o mod.o
	ar rc libdiv.a div.o mod.o
	ranlib libdiv.a

libdiv_dyn.so: div_dyn.o mod_dyn.o
	gcc -shared -o libdiv_dyn.so div_dyn.o mod_dyn.o

div.o: div.c
	gcc -c div.c
mod.o: mod.c
	gcc -c mod.c

div_dyn.o: div.c
	gcc -fPIC -c div.c -o div_dyn.o
mod_dyn.o: mod.c
	gcc -fPIC -c mod.c -o mod_dyn.o

clean:
	rm prog1 prog2 prog3 main.o div.o mod.o libdiv.a libdiv_dyn.so div_dyn.o mod_dyn.o
