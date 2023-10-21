#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

struct hashTable_s{ //define the struct of hash table

    LinkedList *hashlist;
    CopyFunction copyK;
    FreeFunction freeK;
    PrintFunction printK;
    CopyFunction copyV;
    FreeFunction freeV;
    PrintFunction printV;
    EqualFunction equalK;
    TransformIntoNumberFunction transform;
    int hashsize;

};

//generic function do copy to the kvp
Element copyKVP(Element elem){

    if (elem == NULL)
        return NULL;

    return (KeyValuePair)elem;
}
//generic function that free the kvp
status freeKVP(Element elem){

    if (elem == NULL)
        return failure;
    if (destroyKeyValuePair((KeyValuePair)elem) == failure)
        return failure;
    return success;
}
//generic function that print the kvp
status displayKVP(Element elem){

    if (elem == NULL)
        return failure;

    KeyValuePair kvpelem= (KeyValuePair)elem;
    displayValue(kvpelem);
    return success;

}

//generic function that equal between two kvp
bool EqualKVP(Element elem, Element elem1){

    return isEqualKey((KeyValuePair)elem, elem1);
}


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){

    if (copyKey == NULL || freeKey == NULL || printKey == NULL || equalKey == NULL)
        return NULL;

    if(copyValue == NULL || freeValue == NULL || printValue == NULL || transformIntoNumber == NULL)
        return NULL;

    hashTable hash = (hashTable)malloc(sizeof(struct hashTable_s)); //allocate memory to the hash table
    if (hash == NULL)
        return NULL;

    LinkedList *hashlist= (LinkedList*) malloc(sizeof(LinkedList)*hashNumber); //allocate memory to the linked list in the hash
    if (hashlist == NULL)
        return NULL;
    for (int i=0;i<hashNumber;i++){
        hashlist[i]= createLinkedList(copyKVP, (FreeFunction) freeKVP, (PrintFunction) displayKVP, EqualKVP, EqualKVP);
    }

    hash->copyK=copyKey; //initialize every parameter of the hash table
    hash->freeK=freeKey;
    hash->printK=printKey;
    hash->equalK=equalKey;
    hash->copyV=copyValue;
    hash->freeV=freeValue;
    hash->printV=printValue;
    hash->transform=transformIntoNumber;
    hash->hashsize=hashNumber;
    hash->hashlist=hashlist;

    return hash;
}

status addToHashTable(hashTable hash, Element key,Element value){

    if (hash == NULL)
        return failure;

    int index=(hash->transform(key))%(hash->hashsize); //find the place of the list
    Element checker= (searchByKeyInList(hash->hashlist[index],key)); //search if the key already exist in the list
    if (checker == NULL) {
        //create new kvp to add to the list
        KeyValuePair newKVP = createKeyValuePair(hash->copyK, hash->freeK, hash->printK, hash->copyV, hash->freeV,hash->printV, hash->equalK, key, value);
        if (newKVP == NULL)
            return failure;
        appendNode(hash->hashlist[index], newKVP); //append it to the list
        return success;
    }
    else{
        return failure;
    }
}

status destroyHashTable(hashTable hash){

    if (hash == NULL)
        return failure;

    for(int i=0;i<hash->hashsize;i++) {
        destroyList(hash->hashlist[i]); //destroy every list of the hashlist
    }
    free(hash->hashlist);
    free(hash); //free the hash table
    return success;
}

Element lookupInHashTable(hashTable hash, Element key){

    if (hash == NULL)
        return NULL;

    int index=(hash->transform(key))%(hash->hashsize); //find the hashlist to search in
    return getValue(searchByKeyInList(hash->hashlist[index],key)); //search the key in the list

}

status removeFromHashTable(hashTable hash, Element key){

    if (hash == NULL)
        return failure;

    int index=(hash->transform(key))%(hash->hashsize); //find the hashlist to search in
    Element data = searchByKeyInList(hash->hashlist[index],key); //search the key in the list
    if (data == NULL)
        return failure;
    deleteNode(hash->hashlist[index],data); //remove the node from the hash
    return success;

}

status displayHashElements(hashTable hash) {

    if (hash == NULL)
        return failure;

    int counter=0;
    for (int i = 0; i < hash->hashsize; i++) {
        if (getLengthList(hash->hashlist[i]) != 0) {
            displayList(hash->hashlist[i]); //display the list
            counter++;

        } else
            continue;
    }
    if (counter == 0) //if there are no values in hash
        return failure;
    return success;

}









