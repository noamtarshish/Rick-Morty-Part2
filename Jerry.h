#ifndef Jerry_h
#define Jerry_h //compilation guard

#include <stdio.h>
#include "Defs.h"

typedef struct Planet_t{ //struct that define planet of the jerry
    double x,y,z;
    char *name;
}Planet;

typedef struct Origin_t{ //struct that define origin of the jerry
    Planet *planet;
    char *dimension;
}Origin;

typedef struct PhysicalCharacteristics_t{ //struct that define physical characteristic to the pc list of the jerry
    char *name;
    double value;
}PC;

typedef struct Jerry_t{ //struct that define the jerry
    char *id;
    int bliss_level;
    Origin *origin;
    PC **physchar_arr;
    int val_num;
}Jerry;

//all the function from jerry.c
Jerry* initJerry(char *id, int bliss_level,Planet *planet, char *dimension);
//function that initial new jerry with all his characteristics and return jerry
Planet* initPlanet(double x,double y,double z, char *name);
//function that initial new planet with all his characteristics and return planet
PC* initPC (char *name, double value);
//function that initial new physical characteristic with all his characteristics and return physical characteristic
Origin* initOrigin (Planet *planet, char *dimension);
//function that initial new origin with all his characteristics and return origin
bool isPCexist (Jerry *jerry, char *PCname);
//bool function that check if physical characteristic found in given jerry by the name of the physical characteristic
status addPC (Jerry *jerry, PC *pc);
// function that add new physical characteristic to a given jerry
status printJerry (Jerry *jerry);
// function that print jerry by structure include his name, happiness level, origin, planet and his physical characteristics
status printPlanet (Planet *planet);
// status function that print planet with his name and coordinates, return if the print was succeed
status deletePC (Jerry *jerry, char *characterist);
// status function that delete physical characteristic of a given name by name of the physical characteristic
status free_Jerry(Jerry *jerry);
// function that free the allocation of a jerry from the memory
void free_planet(Planet *planet);
// function that free the allocation of a planet from the memory




#endif