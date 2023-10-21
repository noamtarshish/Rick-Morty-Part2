#ifndef ASSIGNMENT_3_MULTIVALUEHASHTABLE_H
#define ASSIGNMENT_3_MULTIVALUEHASHTABLE_H //compilation guard
#include "Defs.h"

//adt generic of Multi Value Hash Table
typedef struct MultiValueHashTable_s *MultiValueHashTable;

//create new Multi Value hash table
MultiValueHashTable createMultiValueHashTable(CopyFunction,FreeFunction,PrintFunction,CopyFunction,FreeFunction,PrintFunction,EqualFunction,EqualFunction,TransformIntoNumberFunction,int);
//free the memory of the Multi Value hash table
status destroyMultiValueHashTable(MultiValueHashTable);
//add new pair to the Multi Value hash table by chaining
status addToMultiValueHashTable(MultiValueHashTable,Element,Element);
//search for a pair in the Multi Value hash table by key
Element lookupInMultiValueHashTable(MultiValueHashTable,Element);
//remove pair from the Multi Value hash table by key
status removeFromMultiValueHashTable(MultiValueHashTable,Element,Element);
//print all the Multi Value hash table
status displayMultiValueHashElementsByKey(MultiValueHashTable,Element);


#endif //ASSIGNMENT_3_MULTIVALUEHASHTABLE_H
