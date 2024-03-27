COMP=gcc -g
DEPS=prefix_tree.o alphabet.o linked_list.o queue.o unscrabbler.o

main : main.c  $(DEPS)
		$(COMP) main.c $(DEPS) -o main

prefix_tree.o : lib/prefix_tree.c lib/prefix_tree.h
		$(COMP) lib/prefix_tree.c -c -o prefix_tree.o

alphabet.o : lib/alphabet.c lib/alphabet.h
		$(COMP) lib/alphabet.c -c -o alphabet.o

linked_list.o : lib/linked_list.c lib/linked_list.h
		$(COMP) lib/linked_list.c -c -o linked_list.o

queue.o : lib/queue.c lib/queue.h
		$(COMP) lib/queue.c -c -o queue.o

unscrabbler.o : lib/unscrabbler.c lib/unscrabbler.h
		$(COMP) lib/unscrabbler.c -c -o unscrabbler.o

clean : 
		rm -rf main *.o
