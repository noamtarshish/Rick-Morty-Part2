#include "KeyValuePair.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct KeyValuePair_h{

    Element key;
    Element value;
    CopyFunction copyK;
    FreeFunction freeK;
    PrintFunction printK;
    CopyFunction copyV;
    FreeFunction freeV;
    PrintFunction printV;
    EqualFunction equalK;
};

KeyValuePair createKeyValuePair(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, Element key, Element value){

    if (copyKey == NULL || freeKey == NULL || printKey == NULL || equalKey == NULL)
        return NULL;

    if(copyValue == NULL || freeValue == NULL || printValue == NULL)
        return NULL;

    KeyValuePair KVP = (KeyValuePair)malloc(sizeof(struct KeyValuePair_h)); //allocate memory to the new key value pair
    if (KVP == NULL)
        return NULL;

    //initialize every parameter to the new key value pair
    KVP->copyK=copyKey;
    KVP->freeK=freeKey;
    KVP->printK=printKey;
    KVP->equalK=equalKey;
    KVP->copyV=copyValue;
    KVP->freeV=freeValue;
    KVP->printV=printValue;
    KVP->key=key;
    KVP->value=value;

    return KVP; //return the new key
}

status destroyKeyValuePair(KeyValuePair KVP){

    if (KVP == NULL)
        return failure;

    KVP->key=NULL;
    (KVP->freeK)(KVP->key); //free the key
    KVP->value=NULL;
    (KVP->freeV)(KVP->value); //free the value
    free(KVP);
    return success;

}

status displayValue(KeyValuePair KVP){

    if (KVP == NULL)
        return failure;

    KVP->printV(KVP->value); //print the value of the pair by using the print function
    return success;
}

status displayKey(KeyValuePair KVP){

    if (KVP == NULL)
        return failure;

    KVP->printK(KVP->key); //print the key of the pair by using the print function
    return success;
}

KeyValuePair getValue(KeyValuePair KVP){

    if (KVP == NULL)
        return NULL;

    return KVP->value; //return the value of the pair
}

KeyValuePair getKey(KeyValuePair KVP){

    if (KVP == NULL)
        return NULL;

    return KVP->key; //return the key of the pair
}

bool isEqualKey(KeyValuePair KVP, Element key){

    if (KVP == NULL)
        return false;

    if (KVP->equalK(KVP->key,key)) //check if the key of the pair equal to the given key by the equal function
        return true;
    else
        return false;
}
