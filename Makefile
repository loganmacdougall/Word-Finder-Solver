COMP=gcc -g
DEPS=prefix_tree.o alphabet.o linked_list.o queue.o array_list.o heap.o unscrabbler.o lib/tester.h

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

array_list.o : lib/array_list.c lib/array_list.h
		$(COMP) lib/array_list.c -c -o array_list.o

heap.o : lib/heap.c lib/heap.h
		$(COMP) lib/heap.c -c -o heap.o

unscrabbler.o : lib/unscrabbler.c lib/unscrabbler.h
		$(COMP) lib/unscrabbler.c -c -o unscrabbler.o

test_array_list : test/test_array_list.c test/test_array_list.h test_main.c $(DEPS)
		$(COMP) test_main.c test/test_array_list.c $(DEPS) -o test_array_list

clean : 
		rm -rf main *.o
