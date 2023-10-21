#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_t //define struct for every node in the linked list
{
    Element data;
    struct Node_t *next;
}Node;

struct LinkedList_h //define struct for linked list
{
    Node *head;
    Node *tail;
    int listsize;
    CopyFunction copyElement;
    FreeFunction freeElement;
    PrintFunction printElement;
    EqualFunction equalfullElement;
    EqualFunction equalpartialElement;
};

Node* createNode(Element elem){ //function that create node and allocate it place in the memory

    if (elem == NULL)
        return NULL;
    Node *newnode=(Node*)malloc(sizeof(struct Node_t)); //allocate memory to the new node
    if (newnode == NULL)
        return NULL;
    newnode->data=elem;
    newnode->next=NULL;
    return newnode;

}

LinkedList createLinkedList(CopyFunction copyf, FreeFunction freef, PrintFunction printf, EqualFunction equalfull, EqualFunction equalpartial){

    if (copyf == NULL || freef == NULL || printf == NULL || equalfull == NULL || equalpartial == NULL)
        return NULL;

    LinkedList list=(LinkedList)malloc(sizeof(struct LinkedList_h)); //allocate memory to the linked list
    if (list == NULL)
        return NULL;


    //initialize every parameter in the linked list
    list->listsize=0;
    list->head=NULL;
    list->tail=NULL;
    list->copyElement=copyf;
    list->freeElement=freef;
    list->printElement=printf;
    list->equalfullElement=equalfull;
    list->equalpartialElement=equalpartial;

    return list;
}

status destroyNode(LinkedList list, Node *node){

    if(list==NULL || node==NULL)
        return failure;

    list->freeElement(node->data); //free the data of the node
    free(node); //free the node itself
    return success;
}


status destroyList(LinkedList list){

    if (list == NULL)
        return failure;

    if (list->listsize>0) {
        Node *current= list->head; //pointer to the head
        Node *next; //pointer to the next of the head
        while (current != NULL) {
            next = current->next;
            status temp = destroyNode(list, current); //try to free the node
            if (temp == failure)
                return failure;
            else {
                current = next; //continue to the next node to free
            }
        }
    }
    free(list); //free the memory of the list in the end
    return success;

}

status appendNode(LinkedList list,Element data){

    if (list == NULL || data == NULL)
        return failure;


    Node *newnode= createNode(data); //allocate memory to the data of the new node
    if (newnode == NULL)
        return failure;
    if (list->head == NULL){ //if the linked list is empty
        list->head = newnode;
        list->tail = newnode;
        list->listsize++;
        return success;
    }
    else{
        list->tail->next= newnode;
        list->tail=newnode; //if not empty, append the new node to the end of the linked list
        list->listsize++;
        return success;
    }

}

status deleteNode(LinkedList list,Element elem)
{
    if(list==NULL||elem==NULL)
    {
        return failure;
    }
    if(list->listsize==1) //if there is only one node in the list
    {
        status temp=destroyNode(list,list->head);
        if(temp==failure)
            return failure;
        list->head=NULL;
        list->tail=NULL;
        list->listsize=0;
    }
    else
    {
        if(list->listsize==0) //if there is no nodes in the list
            return success;
        else
        {
            if(list->equalfullElement(list->head->data,elem)==true) //if there is more than one node in the list
            {
                Node *temp=list->head;
                list->head=list->head->next;
                status check= destroyNode(list,temp);
                if(check==failure)
                    return failure;
                list->listsize--;
                return success;
            }
            Node *curr=list->head->next; //define new current and previous
            Node *prev=list->head;
            while(curr!=NULL)
            {
                if(list->equalfullElement(curr->data,elem)==true)
                {
                    if(curr==list->tail)
                    {
                        list->tail=prev;
                        prev->next=NULL;
                        status check=destroyNode(list,curr);
                        if(check==failure)
                            return failure;
                    }
                    else
                    {
                        prev->next=curr->next;
                        status check=destroyNode(list,curr);
                        if(check==failure)
                            return failure;
                    }
                    list->listsize--;
                    return success;
                }
                prev=curr;
                curr=curr->next;
            }
        }
    }
    return failure; //if there is no return of success in any of the cases
}

status displayList(LinkedList list){

    if (list == NULL)
        return failure;

    Node *currentnode = list->head; //pointer to the head of the linked list
    while (currentnode != NULL){
        list->printElement(currentnode->data); //print the value of the current node
        currentnode = currentnode->next;
    }
    return success;
}

Element getDataByIndex(LinkedList list,int index){

    if (list == NULL || index>list->listsize)
        return NULL;

    Node *current = list->head; //pointer to the head of the linked list
    int counter=0;
    while(current != NULL){
        if (counter == index){ //if the index of the key in the list found, return the data of the node
            return current->data;
        }
        else{
            counter++;
            current= (Node *) current->next;
        }
    }
    return NULL;

}

int getLengthList(LinkedList list){

    if (list == NULL)
        return -1;

    return list->listsize; //return the length of the list
}

Element searchByKeyInList(LinkedList list, Element info){

    if(list==NULL || info==NULL)
        return NULL;

    Node *current=list->head; //pointer to the head of the list to work with it
    while(current!=NULL){
        if(list->equalpartialElement(current->data,info)==true){ //if part of the data equal to the given element
            return current->data;
        }
        current= (Node *) current->next; //move to the next noe
    }
    return NULL;

}


