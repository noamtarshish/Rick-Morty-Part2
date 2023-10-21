#ifndef ASSIGNMENT_3_LINKEDLIST_H
#define ASSIGNMENT_3_LINKEDLIST_H //compilation guard

#include "Defs.h"

/* generic ADT of LinkedList */
typedef struct LinkedList_h* LinkedList;

//create a new Linked List
LinkedList createLinkedList(CopyFunction, FreeFunction, PrintFunction, EqualFunction, EqualFunction);
//clean destroy of the list
status destroyList(LinkedList);
//Add element to the end of the list
status appendNode(LinkedList,Element);
//delete element from the list
status deleteNode(LinkedList,Element);
//print all the list
status displayList(LinkedList);
//get the value of the node by index of the node
Element getDataByIndex(LinkedList,int);
//get the length of the list
int getLengthList(LinkedList);
//search if the given value exist in one of the value's node in the list
Element searchByKeyInList(LinkedList, Element);

#endif //ASSIGNMENT_3_LINKEDLIST_H
