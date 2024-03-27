COMP=gcc -g
DEPS=prefix_tree.o alphabet.o

main : main.c  $(DEPS)
		$(COMP) main.c $(DEPS) -o main

prefix_tree.o : lib/prefix_tree.c lib/prefix_tree.h
		$(COMP) lib/prefix_tree.c -c -o prefix_tree.o

alphabet.o : lib/alphabet.c lib/alphabet.h
		$(COMP) lib/alphabet.c -c -o alphabet.o

clean : 
		rm -rf main *.o
