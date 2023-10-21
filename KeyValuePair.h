#ifndef ASSIGNMENT_3_KEYVALUEPAIR_H
#define ASSIGNMENT_3_KEYVALUEPAIR_H //compilation guard

#include "Defs.h"

// generic ADT of KeyValuePair
typedef struct KeyValuePair_h* KeyValuePair;


//create key value pair
KeyValuePair createKeyValuePair(CopyFunction, FreeFunction, PrintFunction, CopyFunction, FreeFunction, PrintFunction, EqualFunction,Element, Element);
// destroy key value pair
status destroyKeyValuePair(KeyValuePair);
//print the value from the pair
status displayValue(KeyValuePair);
//print the key from the pair
status displayKey(KeyValuePair);
//return the value of the pair
KeyValuePair getValue(KeyValuePair);
//return the key of the pair
KeyValuePair getKey(KeyValuePair);
//check if the given key equal to the key in the given pair
bool isEqualKey(KeyValuePair, Element);


#endif //ASSIGNMENT_3_KEYVALUEPAIR_H
