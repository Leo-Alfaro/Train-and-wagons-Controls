#include <stdio.h>
#include <stdlib.h>
#include "trainsControl.h"

void createTrainList(Train** t){
    *t = (Train*)malloc(sizeof(Train));
    (*t) -> next = NULL;
    (*t) -> wagons = NULL;
}

void addTrain(Train** t, int idT){
    if(*t == NULL){
        return;
    }
    
    Train *no = (Train*)malloc(sizeof(Train));
    
    no -> idT = idT;
    no -> wagons = (Wagons*)malloc(sizeof(Wagons));
    no -> next = *t;
    
    *t = no;
}

void removeTrain(Train** t, int idT){
    if(*t == NULL){
        return;
    }
    
    Train *temp = (*t) -> next;
    Train *aux = NULL;
    Train *aux2 = *t;
    
    if((*t) -> idT == idT){
        aux = *t;
        *t = temp;
    } else{
        while(temp != NULL){
            if(temp -> idT == idT){
                aux2 -> next = temp -> next;
                aux = temp;
                break;
            }
            temp = temp -> next;
            aux2 = aux2 -> next;
        }
    }
    free(aux);
}

void printTrainList(Train** t){
    Train *aux = *t;
    while(aux -> next != NULL){
        printf("[%d]\n", aux -> idT);
        aux = aux -> next;
    }
}





