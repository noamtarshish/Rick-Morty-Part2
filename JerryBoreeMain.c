#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"
#include <math.h>

//function that free the memory of all the planets - used in case 9
void free_all_Planets(Planet **planet, int planetsNumber){

    if (planet == NULL)
        return;

    for (int a=0; a<planetsNumber;a++){
        free_planet(planet[a]);
    }
    free(planet);
    planet=NULL;
}

//function that prints all the existed planets - used in case 7 (inner case 3)
void print_all_Planets(int number, Planet **planets){

    if (planets == NULL){ //check if planet is empty
        return;
    }
    for (int i=0;i<number;i++){ //print all the planets
        printPlanet(planets[i]);
    }
}

//function that transform string into integer value - used to know where to add in hash table
int transform(Element key){

    if (key == NULL)
        return 0;

    int number=0;
    char* str=(char*)key;
    int length = strlen(str);
    for (int i=0;i<length;i++) {
        number += str[i]; //sum the score of the string in every letter
    }
    return number;
}

//function that copy key with a shallow copy
Element copysk(Element key){

    if (key == NULL)
        return NULL;

    return (char*)key;
}

//function that copy key with a shallow copy
Element copydk(Element key){

    if (key == NULL)
        return NULL;

    char*str = (char*)key; //casting to char*
    char*id= malloc(sizeof(char)*(strlen(str)+1));
    if (id == NULL){
        printf("Memory Problem");
        exit(1);}
    else{
        strcpy(id, str); //initialize every parameter into the new jerry
        return id;}
}

//function that free the allocation of the key of the pair
status freek(Element key){

    if (key == NULL)
        return failure;

    char*str = (char*)key;//casting to char*
    str=NULL;
    free(str);
    return success;
}

//function that print the key of the pair
status printK(Element key){

    if (key == NULL)
        return failure;

    char* str = (char*)key; //casting to char*
    printf("%s \n", str);
    return success;
}

//function that equal between two keys of two pairs
bool equalK(Element key1, Element key2){

    if (key1 == NULL || key2 == NULL)
        return false;

    if (strcmp((char*)key1,(char*)key2) == 0) //equal
        return true;
    else //not equal
        return false;
}

//function that copy the value of the node - in all of my adts is Jerry therefore there is casting to Jerry
Element copyV(Element val){

    if (val == NULL)
        return NULL;

    Jerry *j = (Jerry *)val; //casting to jerry
    Jerry *new = initJerry(j->id,j->bliss_level,j->origin->planet, j->origin->dimension); //init new Jerry
    if(new==NULL) { //if the allocation was failed
        printf("Memory Problem");
        free_Jerry(new); //free the Jerry
        exit(1); //exit from the program
    }
    return new;
}

//function that check if two Jerries are equal
bool equalV(Element val1, Element val2){

    if (val1 == NULL || val2 == NULL)
        return false;

    Jerry *j1 = (Jerry *)val1; //casting to Jerry
    Jerry *j2 = (Jerry *)val2;

    if (strcmp(j1->id,j2->id)==0) //0 == true
        return true;
    else
        return false;

}

//function that free Jerry from hash table
status freeVHash(Element value){

    if (value == NULL)
        return failure;

    free_Jerry((Jerry*)value); //casting to Jerry
    return success;

}

//function that determine the size of the hash table
int hashSize(int planetsNumber){

    if (planetsNumber == 0)
        return 0;

    int temp = planetsNumber*planetsNumber+1;
    for (int i=2;i<10;i++) {
        if (temp % i == 0){
            temp++;
            i=1;}

        else
            continue;
    }
    return temp;
}

//fictive function to free nothing (used for the pcmultihash and jerryList)
status freenothing(Element value){
    return success;
}


int main(int arg_num, char* arg_num_list[]) {

    int planetsNumber = atoi(arg_num_list[1]);
    FILE *newfile = fopen(arg_num_list[2], "r");

    if (newfile == NULL) { //check if the file is empty
        printf("The file is empty");
        fclose(newfile); //close the file and exit from the script
        exit(1);
    }

    Planet **planet_list = (Planet **) malloc(sizeof(Planet *) * planetsNumber);
    if (planet_list == NULL) { //check if the planet list is empty
        printf("The planet list is empty");
        fclose(newfile); //close the file and exit from the script
        exit(1);
    }


    //adt 3 - linkedlist contain all the jerries
    LinkedList jerryList = createLinkedList(copyV, freenothing, (PrintFunction) printJerry, equalV, equalV);

    //adt 1 - hash conatin all the jerry existed. key: id of the jerry, value: jerry object
    hashTable jerryhash = createHashTable(copysk, freek, printK, copyV, freeVHash,
                                          (PrintFunction) printJerry, equalK, transform, hashSize(planetsNumber));

    //adt 2 - multihash conatin all the pc existed. key: pc, value: list of jerries that have this pc;
    MultiValueHashTable pcMultiHash = createMultiValueHashTable(copysk, freek, printK, copyV,
                                                                freenothing,
                                                                (PrintFunction) printJerry, equalK,
                                                                equalV, transform, hashSize(planetsNumber));


char wordcheck[300];
int i = 1; //number of line if file
int jerry_find = 0;
char *key;
while (fgets(wordcheck, 300, newfile) != NULL) {
    if (i == 1) {
        i++;
        continue;
    }
    if (strcmp(wordcheck, "Jerries\n") == 0) {
        jerry_find++;
        i++;
        continue;
    }
    if (jerry_find == 0) {
        char *splited = strtok(wordcheck, ",");
        double x = atof(strtok(NULL, ",")); //split the dimension of the Jerry
        double y = atof(strtok(NULL, ","));
        double z = atof(strtok(NULL, ","));
        Planet *newplanet = initPlanet(x, y, z, splited); //create new planet
        if (newplanet == NULL) {
            printf("Memory Problem");
            free_all_Planets(planet_list, planetsNumber);
            destroyMultiValueHashTable(pcMultiHash);
            destroyList(jerryList);
            destroyHashTable(jerryhash);
            fclose(newfile);
            exit(1);
        } else {
            planet_list[i-2] = newplanet; //add the new planet to the planets list
            i++;
        }

    } else { //for every pc in Jerry
        char *splited = strtok(wordcheck, ",");
        if (splited[0] == '\t') {
            char *pcname = strtok(wordcheck, ":");
            double pcvalue = atof(strtok(NULL, ":"));
            char *newpcname = strtok(pcname, "\t");
            PC *mypc = initPC(newpcname, pcvalue); //create new pc
            Jerry *jerry = lookupInHashTable(jerryhash, key); //search the Jerry by pc
            addPC(jerry, mypc); //add the new pc to the Jerry pc list
            status add = addToMultiValueHashTable(pcMultiHash, copydk(newpcname), jerry); //add to pcmultihash the new pc with it Jerry
            if (add == failure) {
                printf("Memory Problem");
                deletePC(jerry, newpcname);
                free_Jerry(jerry);
                destroyMultiValueHashTable(pcMultiHash);
                destroyList(jerryList);
                destroyHashTable(jerryhash);
                free_all_Planets(planet_list,planetsNumber);
                fclose(newfile);
                exit(1);
            }

        }

        else { //arrange the characteristics to create Jerry
            char *dimension = strtok(NULL, ",");
            char *planet = strtok(NULL, ",");
            int bliss_level = atoi(strtok(NULL, ","));
            Planet *newplanet = NULL;
            for (int k = 0; k < planetsNumber; k++) {
                if (strcmp(planet_list[k]->name, planet) == 0) {
                    newplanet = planet_list[k];
                    break;
                }
            } //create new Jerry
            Jerry *newjerry = initJerry(splited, bliss_level, newplanet, dimension);
            if (newjerry == NULL) {
                printf("Memory Problem");
                free_Jerry(newjerry);
                destroyMultiValueHashTable(pcMultiHash);
                destroyList(jerryList);
                destroyHashTable(jerryhash);
                free_all_Planets(planet_list,planetsNumber);
                fclose(newfile);
                exit(1);
            } else {
                key = copydk(splited);
                addToHashTable(jerryhash, key, newjerry); //add Jerry to the Jerryhash
                appendNode(jerryList, newjerry); //append the new Jerry to the jerries list

            }
        }
    }

}
fclose(newfile);


char input[300];
char input1[300];
char input2[300];
double double_input;
char ch = '0';
while (ch != '9') { //printing all the menu
    printf("Welcome Rick, what are your Jerry's needs today ?\n");
    printf("1 : Take this Jerry away from me\n");
    printf("2 : I think I remember something about my Jerry\n");
    printf("3 : Oh wait. That can't be right\n");
    printf("4 : I guess I will take back my Jerry now\n");
    printf("5 : I can't find my Jerry. Just give me a similar one\n");
    printf("6 : I lost a bet. Give me your saddest Jerry\n");
    printf("7 : Show me what you got\n");
    printf("8 : Let the Jerries play\n");
    printf("9 : I had enough. Close this place\n");
    scanf("%s", &ch);
    if (strlen(&ch)>1){
        printf("Rick this option is not known to the daycare !\n");
        continue;
    }
    switch (ch) {
    case '1': //Take this Jerry away from me - add new Jerry to the daycare
        printf("What is your Jerry's ID ? \n");
        scanf("%s", input);
        Jerry *jerry = lookupInHashTable(jerryhash, input); //search the jerry in jerryhash
        if (jerry != NULL) {
            printf("Rick did you forgot ? you already left him here !\n");
            break;
        } else {
            char *jerryid = input;
            printf("What planet is your Jerry from ? \n");
            scanf("%s", input1);
            int counter = 0;
            Planet *jerryplanet = NULL;
            for (int a = 0; a < planetsNumber; a++) { //search the planet of the jerry
                if (strcmp(input1, planet_list[a]->name) == 0) {
                    jerryplanet = planet_list[a];
                    counter++;
                }
            }
            if (counter == 0) {
                printf("%s is not a known planet !\n", input1);
                break;
            } else {
                printf("What is your Jerry's dimension ?\n");
                scanf("%s", input2);
                char *jerrydimension = input2;
                printf("How happy is your Jerry now ?\n");
                scanf("%lf", &double_input);
                int jerrybliss_level = double_input;
                Jerry *newJerry = initJerry(jerryid, jerrybliss_level, jerryplanet, jerrydimension);
                if (newJerry == NULL){
                    free_Jerry(newJerry);
                    destroyMultiValueHashTable(pcMultiHash);
                    destroyHashTable(jerryhash);
                    destroyList(jerryList);
                    free_all_Planets(planet_list,planetsNumber);
                    exit(1);}
                addToHashTable(jerryhash, newJerry->id, newJerry); //add the new Jerry to Jerry hash
                appendNode(jerryList, newJerry); //append the new Jerry to the jerries list
                printJerry(newJerry); //print the new Jerry after the addition to the adts
                break;
            }
        }

    case '2': //I think I remember something about my Jerry - add new pc to Jerry
        printf("What is your Jerry's ID ?\n");
        scanf("%s", input);
        Jerry *newjerry = lookupInHashTable(jerryhash, input); //search the jerry in jerryhash
        if (newjerry == NULL) {
            printf("Rick this Jerry is not in the daycare !\n");
            break;
        } else {
            printf("What physical characteristic can you add to Jerry - %s ?\n", input);
            scanf("%s", input);
            if (isPCexist(newjerry, input) == true) {
                printf("The information about his %s already available to the daycare !\n", input);
                break;
            } else {
                char *pcname = input;
                printf("What is the value of his %s ?\n", input);
                scanf("%lf", &double_input);
                PC *newpc = initPC(pcname, double_input); //create the pc
                addPC(newjerry, newpc); //add the new pc to the pc list of the jerry
                addToMultiValueHashTable(pcMultiHash, copysk(pcname), newjerry); //add the pc to the adt of all the pcs
                printf("%s :\n", pcname); //print the name of the pc
                displayMultiValueHashElementsByKey(pcMultiHash,pcname);
                break;

            }
        }

    case '3': //Oh wait. That can't be right - remove pc from Jerry
        printf("What is your Jerry's ID ?\n");
        scanf("%s", input);
        Jerry *newjerry1 = lookupInHashTable(jerryhash, input); //find the jerry in jerryhash
        if (newjerry1 == NULL) {
            printf("Rick this Jerry is not in the daycare !\n");
            break;
        } else {
            printf("What physical characteristic do you want to remove from Jerry - %s ?\n", input);
            scanf("%s", input1);
            char *pcname1 = input1;
            if (isPCexist(newjerry1, pcname1) == false) { //check if the pc found in jerry
                printf("The information about his %s not available to the daycare !\n", pcname1);
                break;
            } else {
                removeFromMultiValueHashTable(pcMultiHash,pcname1,newjerry1); //remove the jerry from the pcmultihash
                deletePC(newjerry1, pcname1); //delete the pc from the jerry itself
                printJerry(newjerry1); //print the jerry without the pc
                break;
            }
        }

    case '4': //I guess I will take back my Jerry now - give Rick his Jerry back
        printf("What is your Jerry's ID ? \n");
        scanf("%s", input);
        Jerry *newjerry2 = lookupInHashTable(jerryhash, input); //find the jerry in jerryhash
        if (newjerry2 == NULL) {
            printf("Rick this Jerry is not in the daycare !\n");
            break;
        } else {
            for (int g=0; g < newjerry2->val_num; g++) { //remove every pc that belonk to this Jerry
                removeFromMultiValueHashTable(pcMultiHash, newjerry2->physchar_arr[g]->name, newjerry2);
            }
            deleteNode(jerryList,newjerry2);
            removeFromHashTable(jerryhash, newjerry2->id);
            printf("Rick thank you for using our daycare service ! Your Jerry awaits !\n");
            break;
        }

    case '5': //I can't find my Jerry. Just give me a similar one - give to rick similar jerry
        printf("What do you remember about your Jerry ? \n");
        scanf("%s", input);
        char *pcname = input;
        LinkedList vallist = lookupInMultiValueHashTable(pcMultiHash, pcname); //search the pc list
        if (vallist == NULL) {
            printf("Rick we can not help you - we do not know any Jerry's %s !\n", pcname);
            break;
        } else {
            printf("What do you remember about the value of his %s ? \n", pcname);
            scanf("%lf", &double_input);
            Jerry *similarJerry = (Jerry*) (getDataByIndex(vallist, 0)); //declare the firs Jerry as the similar temporary Jerry
            PC *pctocheck;
            for (int y = 0; y < similarJerry->val_num; y++) {
                if (strcmp(pcname, similarJerry->physchar_arr[y]->name) == 0) {
                    pctocheck = similarJerry->physchar_arr[y]; //get pc to check
                }
            }
            double abssimilarcheck = fabs(double_input - (pctocheck->value)); //using abs
            for (int j = 1; j < getLengthList(vallist); j++) {
                Jerry *nowjerry = (Jerry *) (getDataByIndex(vallist, j)); //get another Jerry to determine if he is similar than the similar temporary Jerry
                for (int x = 0; x < nowjerry->val_num; x++) {
                    if (strcmp(pcname, nowjerry->physchar_arr[x]->name) == 0) {
                        PC *pctocheck1 = nowjerry->physchar_arr[x]; //get pc to check
                        double abscheck = fabs(double_input - (pctocheck1->value));
                        if (abscheck < abssimilarcheck) { //if the nowjerry similar than the similar temporary Jerry,replace them
                            similarJerry = nowjerry;
                        }
                    }
                }
            }
            printf("Rick this is the most suitable Jerry we found : \n");
            printJerry(similarJerry); //print the similar jerry that found
            for (int y=0; y < similarJerry->val_num; y++) { //remove every pc that belonk to this Jerry
                removeFromMultiValueHashTable(pcMultiHash, similarJerry->physchar_arr[y]->name, similarJerry);
            }
            deleteNode(jerryList,similarJerry);
            removeFromHashTable(jerryhash,similarJerry->id); //remove the similar jerry that taken by Rick
            printf("Rick thank you for using our daycare service ! Your Jerry awaits !\n");
            break;

        }

    case '6': //I lost my bet. Give me your saddest Jerry - give to rick the saddest jerry
        if (getLengthList(jerryList)== 0) {
            printf("Rick we can not help you - we currently have no Jerries in the daycare !\n");
            break;
        }
        else {
            Jerry *saddest_jerry = NULL; //initialize the saddest Jerry to NULL;
            for (int b=0; b< getLengthList(jerryList); b++) {
                Jerry *jerrycheck = getDataByIndex(jerryList, b);
                if (saddest_jerry == NULL) { //if there is no saddest Jerry the first will be the temporary
                    saddest_jerry = jerrycheck;
                } else {
                    if (jerrycheck != NULL){
                        if (jerrycheck->bliss_level < saddest_jerry->bliss_level) {
                            saddest_jerry = jerrycheck;
                        }

                }}
            }

            printf("Rick this is the most suitable Jerry we found : \n");
            printJerry(saddest_jerry);
            for (int y=0; y < saddest_jerry->val_num; y++) { //remove every pc that belonk to this Jerry
                removeFromMultiValueHashTable(pcMultiHash, saddest_jerry->physchar_arr[y]->name, saddest_jerry);
            }
            deleteNode(jerryList,saddest_jerry);
            removeFromHashTable(jerryhash,saddest_jerry->id);
            printf("Rick thank you for using our daycare service ! Your Jerry awaits !\n");
            break;

            }

    case '7': //show me what you got - show information about the daycare
    {
        char ch1 = '0';
        printf("What information do you want to know ?\n");
        printf("1 : All Jerries\n");
        printf("2 : All Jerries by physical characteristics\n");
        printf("3 : All known planets\n");
        scanf("%s", &ch1);
        if (strlen(&ch1)>1) { //if the input is number bigger than one number
            printf("Rick this option is not known to the daycare !\n");
            continue;
        }
        switch (ch1) {
            case '1': {
                status display = displayList(jerryList); //print all the jerries
                if (display == failure) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare !\n");
                    break;
                }
                break;
            }

            case '2': {
                printf("What physical characteristics ?\n");
                scanf("%s", input);
                LinkedList pcvaluelist = lookupInMultiValueHashTable(pcMultiHash, input); //search the pc list in pcmultihash
                if (pcvaluelist == NULL) {
                    printf("Rick we can not help you - we do not know any Jerry's %s !\n", input);
                    break;
                } else {
                    printf("%s : \n", input);
                    displayMultiValueHashElementsByKey(pcMultiHash,input); //print the list contain all the jerries with this pc
                    break;
                }
            }

            case '3': {
                print_all_Planets(planetsNumber, planet_list); //print all the planets in the daycare
                break;
            }

            default: //if the input number is different from '1'/'2'/'3'
                printf("Rick this option is not known to the daycare !\n");
                break;
        }
        break;
    }

    case '8': //Let the Jerries play
    {
    if (getLengthList(jerryList)== 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare !\n");
        break;
    }
    else {
        char ch1 = '0';
        printf("What activity do you want the Jerries to partake in ?\n");
        printf("1 : Interact with fake Beth\n");
        printf("2 : Play golf\n");
        printf("3 : Adjust the picture settings on the TV\n");
        scanf("%s", &ch1);
        if (strlen(&ch1)>1) { //if the input is number bigger than one number
            printf("Rick this option is not known to the daycare !\n");
            continue;
        }
        switch (ch1) {
            case '1': //Interact with fake Beth - add 15 if bliss_level>19, subtract 15 else
                for (int j=0; j< getLengthList(jerryList); j++) {
                    Jerry *jerrycheck = getDataByIndex(jerryList, j); //find the jerry to check is bliss level
                    if (jerrycheck->bliss_level >= 20) {
                        jerrycheck->bliss_level = jerrycheck->bliss_level + 15;
                        if ((jerrycheck->bliss_level) > 100) { //if jerry bliss level exceeded over 100
                            jerrycheck->bliss_level = 100;
                        }
                    } else {
                        jerrycheck->bliss_level = jerrycheck->bliss_level - 5;
                        if (jerrycheck->bliss_level < 0) { //if jerry bliss level decrease under 0
                            jerrycheck->bliss_level = 0;
                        }
                    }
                }
                printf("The activity is now over !\n");
                displayList(jerryList);
                break;

            case '2': //Play golf - add 10 if bliss_level>50, subtract 10 else
                for (int j=0; j< getLengthList(jerryList); j++) {
                    Jerry *jerrycheck = getDataByIndex(jerryList, j);
                    if (jerrycheck->bliss_level >= 50) {
                        jerrycheck->bliss_level = jerrycheck->bliss_level + 10;
                        if ((jerrycheck->bliss_level) > 100) { //if jerry bliss level exceeded over 100
                            jerrycheck->bliss_level = 100;
                        }
                    } else {
                        jerrycheck->bliss_level = jerrycheck->bliss_level - 10;
                        if (jerrycheck->bliss_level < 0) { //if jerry bliss level decrease under 0
                            jerrycheck->bliss_level = 0;
                        }
                    }
                }
                printf("The activity is now over !\n");
                displayList(jerryList);
                break;

            case '3': //Adjust the picture settings on the TV - add 20 to every Jerry
                for (int j=0; j< getLengthList(jerryList); j++) {
                    Jerry *jerrycheck = getDataByIndex(jerryList, j);
                    jerrycheck->bliss_level = jerrycheck->bliss_level + 20;
                    if (jerrycheck->bliss_level > 100) //if jerry bliss level exceeded over 100
                        jerrycheck->bliss_level = 100;
                }
                printf("The activity is now over !\n");
                displayList(jerryList);
                break;

            default: //if the input number is different from '1'/'2'/'3'
                printf("Rick this option is not known to the daycare !\n");
                break;
        }
        break;
        }
    }


    case '9': //close the program - free all the adts
        destroyMultiValueHashTable(pcMultiHash);
        destroyList(jerryList);
        destroyHashTable(jerryhash);
        free_all_Planets(planet_list,planetsNumber);
        printf("The daycare is now clean and close !\n");
        break;


    default: //if the input number is different from '1'-'9'
        printf("Rick this option is not known to the daycare !\n");
        break;

} //menu switch
} //while
} //main
