JerryBoree: Jerry.o LinkedList.o KeyValuePair.o HashTable.o MultiValueHashTable.o JerryBoreeMain.o
	gcc Jerry.o LinkedList.o KeyValuePair.o HashTable.o MultiValueHashTable.o JerryBoreeMain.o -o JerryBoree

Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c Jerry.h
	
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c LinkedList.h

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c KeyValuePair.h

HashTable.o: HashTable.c HashTable.h Defs.h
	gcc -c HashTable.c HashTable.h

MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h Defs.h
	gcc -c MultiValueHashTable.c MultiValueHashTable.h
	
JerryBoreeMain.o: JerryBoreeMain.c
	gcc -c JerryBoreeMain.c


clean:
	rm -f *.o JerryBoree
