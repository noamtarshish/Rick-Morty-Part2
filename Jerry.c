
#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Jerry* initJerry(char *id, int bliss_level,Planet *planet, char *dimension){
    Jerry *newJerry; //create new jerry
    newJerry=(Jerry*)malloc(sizeof(Jerry)); //allocate memory to the new jerry

    if (newJerry == NULL || id == NULL || planet == NULL || dimension == NULL){ //check if one of the pointers is null
        return NULL;
    }
    newJerry->id= malloc(sizeof(char)*(strlen(id)+1));
    if (newJerry->id == NULL){
        free_Jerry(newJerry);
        exit(1);}
    else {
        strcpy(newJerry->id, id); //initialize every parameter into the new jerry
        newJerry->bliss_level = bliss_level;
        newJerry->origin = initOrigin(planet, dimension);
        newJerry->val_num = 0;
        newJerry->physchar_arr = NULL;
        return newJerry; //return new jerry
    }
}

Planet* initPlanet(double x,double y,double z, char *name){
    Planet *newPlanet; // create new planet
    newPlanet=(Planet*)malloc(sizeof(Planet)); //allocate memory to the new planet
    if (newPlanet == NULL || name == NULL){ //check if one of the pointers is null
        return NULL;
    }
    newPlanet->x=x;//initialize every parameter into the new jerry
    newPlanet->y=y;
    newPlanet->z=z;
    newPlanet->name= malloc(sizeof(char)*(strlen(name)+1));
    if (newPlanet->name == NULL){
        free_planet(newPlanet);
        exit(1);}
    strcpy(newPlanet->name, name);

    return newPlanet; //return new planet
}

PC* initPC (char *name, double value){
    PC *newPC; // create new Physical Characteristic
    newPC=(PC*)malloc(sizeof(PC)); //allocate memory to the new Physical Characteristic
    if (newPC == NULL || name == NULL){ //check if one of the pointers is null
        return NULL;
    }
    newPC->name= (char*)malloc(sizeof(char)*(strlen(name)+1));
    if (newPC->name == NULL){
        free(newPC);
        exit(1);}
    strcpy(newPC->name, name);//initialize every parameter into the new Physical Characteristic
    newPC->value=value;
    return newPC; //return new Physical Characteristic
}

Origin* initOrigin (Planet *planet, char *dimension){
    Origin *newOrigin; //create new origin
    newOrigin= (Origin*)malloc(sizeof(Origin)); //allocate memory to the new origin
    if (newOrigin == NULL || planet == NULL){ //check if one of the pointers is null
        return NULL;
    }
    newOrigin->planet=planet; //initialize every parameter into the new jerry
    newOrigin->dimension= malloc(sizeof(char)*(strlen(dimension)+1));
    if (newOrigin->dimension == NULL){
        free(newOrigin);
        exit(1);
        ;}
    strcpy(newOrigin->dimension, dimension);

    return newOrigin; //return new origin
}

bool isPCexist (Jerry *jerry, char *PCname) {

    if (jerry == NULL || PCname == NULL) { //check if one of the pointers is null
        return false;
    }
    int counter = 0;
    for (int i = 0;i < jerry->val_num; i++) //run with loop on every pc in jerry pc list and check if the pc found there
    {
        if (strcmp(PCname, jerry->physchar_arr[i]->name) == 0) {
            counter++;
            continue;
        }
    }
    if (counter != 0) {
        return true;
    } else {
        return false;
    }
}

status addPC (Jerry *jerry, PC *pc){

    if (pc == NULL || jerry == NULL){ //check if one of the pointers is null
        return failure;
    }

    if (jerry->physchar_arr == NULL){ //if the pc list is empty, I need to allocate memory and initialize it
        jerry->physchar_arr=(PC**)malloc(sizeof(PC*));
        if(jerry->physchar_arr == NULL)
            return failure;
        jerry->physchar_arr[0]=pc;
        jerry->val_num++;
    }
    else{
        jerry->physchar_arr= realloc(jerry->physchar_arr, sizeof(PC*)*(jerry->val_num+1)); // if not empty, I need to realloc and update the list
        if (jerry->physchar_arr == NULL)
            return failure;
        jerry->physchar_arr[jerry->val_num]=pc;
        jerry->val_num++;

    }
    return success;

}

status deletePC (Jerry *jerry, char *characterist) {

    if (jerry == NULL || characterist == NULL){  //check if one of the pointers is null
        return failure;
    }
    int flag=0; //check if only one in pc
    for (int i = 0; i < jerry->val_num; i++) { //if the pc is found, remove it
        if (strcmp(characterist, jerry->physchar_arr[i]->name) == 0) {
            flag++;
            free(jerry->physchar_arr[i]->name);
            free(jerry->physchar_arr[i]);
        }
        if (flag > 0 && i < jerry->val_num-1) { //arrange the list without the removed pc
            jerry->physchar_arr[i] = jerry->physchar_arr[i+1];
        }
    }
    if (flag>0){ //realloc to change to memory allocation of the pc list
        jerry->physchar_arr= realloc(jerry->physchar_arr, sizeof(PC*)*(jerry->val_num-1));
        if (jerry->physchar_arr == NULL)
            return failure;
        jerry->val_num--;
        return success;
    }
    else{
        return failure;//failure if the deletion is not successed
    }

}

status printJerry(Jerry *jerry) {
    if (jerry == NULL){ //check if jerry is empty to avoid memory problem
        return failure;
    }
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %d \n", jerry->bliss_level);
    printf("Origin : %s \n", jerry->origin->dimension);
    printPlanet(jerry->origin->planet); //using the print planet function to print the planet of the jerry
    if (jerry->val_num > 0) {
        printf("Jerry's physical Characteristics available : \n\t");
        for (int i = 0; i < jerry->val_num; i++) {
            if (i==jerry->val_num-1) {
                printf("%s : %.2f \n", jerry->physchar_arr[i]->name, jerry->physchar_arr[i]->value);
            }
            else{
                printf("%s : %.2f , ", jerry->physchar_arr[i]->name, jerry->physchar_arr[i]->value);
            }
        }
    }
    return success;
}

status printPlanet(Planet *planet) {

    if (planet == NULL){ //check if jerry is empty to avoid memory problem
        return failure;
    }
    if (planet->name == NULL) { //check if one of the parameters initialize to zero or empty
        return failure;
    } else {
        printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet->name, planet->x, planet->y, planet->z);
        return success;
    }

}

status free_Jerry(Jerry *jerry){

    if (jerry == NULL)
        return failure;

    free(jerry->id); //free the id
    jerry->id = NULL; //initialize to null
    for (int i = 0; i < jerry->val_num; i++) {
        free(jerry->physchar_arr[i]->name); //free every name of every pc
        jerry->physchar_arr[i]->name = NULL; //initialize to null
        free(jerry->physchar_arr[i]); //free every pc
        jerry->physchar_arr[i] = NULL; //initialize to null
    }
    free(jerry->physchar_arr); //free the list of pc
    jerry->physchar_arr = NULL;
    free(jerry->origin->dimension); //free the origin dimension
    jerry->origin->dimension = NULL;//initialize to null
    free(jerry->origin);
    jerry->origin = NULL;
    return success;
}

void free_planet(Planet *planet){
    free(planet->name); //free the name of the planet
    planet->name=NULL;
    free(planet); //free the planet itself
    planet=NULL;

}

