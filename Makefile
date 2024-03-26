COMP=gcc -g
DEPS=prefix_tree.o

main : main.c  $(DEPS)
		$(COMP) main.c $(DEPS) -o main

prefix_tree.o : prefix_tree.c prefix_tree.h
		$(COMP) prefix_tree.c -c

clean : 
		rm -rf main *.o
