#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"


struct MultiValueHashTable_s{

    hashTable muitihashtable;
    CopyFunction copyK;
    FreeFunction freeK;
    PrintFunction printK;
    CopyFunction copyV;
    FreeFunction freeV;
    PrintFunction printV;
    EqualFunction equalK;
    EqualFunction equalV; //function that only MultiValueHashTable has and HashTable has not
    TransformIntoNumberFunction transform;
    int hashsize;

};

MultiValueHashTable createMultiValueHashTable(CopyFunction copyK, FreeFunction freeK, PrintFunction printK, CopyFunction copyV, FreeFunction freeV, PrintFunction printV, EqualFunction equalK,EqualFunction equalV, TransformIntoNumberFunction transform, int hashsize) {
    //create of MultiHash and HashTable is the same so there is calling to the create HashTable function
    if (copyK == NULL || freeK == NULL || printK == NULL || equalK == NULL)
        return NULL;

    if(copyV == NULL || freeV == NULL || printV == NULL || equalV == NULL || transform == NULL)
        return NULL;

    //allocate memory
    MultiValueHashTable multihash = (MultiValueHashTable)malloc(sizeof(struct MultiValueHashTable_s)); //allocate memory to the hash table
    if (multihash == NULL)
        return NULL;

    //allocate memory to the Hash Table in the Multi Value Hash Table
    hashTable multihashtable = createHashTable(copyK,freeK,printK,copyV,freeV,printV,equalK,transform,hashsize);
    if (multihashtable == NULL)
        return NULL;

    //initialize every parameter of the hash table
    multihash->muitihashtable = multihashtable;
    multihash->copyK=copyK;
    multihash->freeK=freeK;
    multihash->printK=printK;
    multihash->equalK=equalK;
    multihash->copyV=copyV;
    multihash->freeV=freeV;
    multihash->equalV=equalV;
    multihash->printV=printV;
    multihash->transform=transform;
    multihash->hashsize=hashsize;

    return multihash;
}
status addToMultiValueHashTable(MultiValueHashTable multihash, Element key,Element value) {

    if (multihash == NULL || key == NULL || value == NULL)
        return failure;


    Element exist= lookupInHashTable(multihash->muitihashtable,key);
    if (exist == NULL) { //if the key does not found in the linked list
        LinkedList newlinkedlist = createLinkedList(multihash->copyV, (FreeFunction) multihash->freeV,
                                                    (PrintFunction) multihash->printV, multihash->equalV, multihash->equalV);
        if (newlinkedlist == NULL){
            destroyList(newlinkedlist);
            return failure;}


        appendNode(newlinkedlist, value); //append new list in the linked list for the values of the key
        Element a = multihash->freeV;
        MultiValueHashTable b=(MultiValueHashTable)multihash->muitihashtable;
        b->freeV = (FreeFunction) destroyList;
        addToHashTable(multihash->muitihashtable,key,newlinkedlist);
        b->freeV = a;
    } else {
        multihash->freeK(key);
        appendNode(exist, value);
    }
    return success;
}

status destroyMultiValueHashTable(MultiValueHashTable multihash){

    if (multihash == NULL)
        return failure;

    destroyHashTable(multihash->muitihashtable);
    free(multihash); //free the hash table
    return success;
}

status removeFromMultiValueHashTable(MultiValueHashTable multihash, Element key, Element value){

    if (multihash == NULL || key == NULL || value == NULL)
        return failure;
    LinkedList val = (LinkedList)lookupInMultiValueHashTable(multihash,key); //search the list of values
    if (val == NULL) {
        printf("Memory problem");
        return failure;
    }
    else {
        deleteNode(val,value); //delete the specific val from the list
        if (getLengthList(val) == 0){ //if there is no more values in the list, remove the list itself
            removeFromHashTable(multihash->muitihashtable,key);
        }
    }
    return success;
}

Element lookupInMultiValueHashTable(MultiValueHashTable multihash, Element key){

    if (multihash == NULL || key == NULL)
        return NULL;

    Element result = lookupInHashTable(multihash->muitihashtable,key); //calling to the function from HashTable
    if (result == NULL)
        return NULL;
    return result;

}

status displayMultiValueHashElementsByKey(MultiValueHashTable multihash, Element key){

    if (multihash == NULL || key == NULL)
        return failure;

    LinkedList val = (LinkedList)lookupInMultiValueHashTable(multihash,key); //searching the line in the hash
    if (val == NULL)
        return failure;
    if (getLengthList(val) != 0) {
        displayList(val);
    }
    return success;

}