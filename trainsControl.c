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
    no -> wagons = NULL;
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
    Wagons *w = *t;
    
    while(aux -> next != NULL){
        printf("[%d]", aux -> idT);
        int i = 0;
        while(i < aux -> wagonsAmount){
            printf("[product: %s | id: %d]", w -> productType, w -> idW);
        }
        printf("\n");
        aux = aux -> next;
    }
}

void addWagon(Train** t, int idT, int idW, char* productType, int position){
    //Space allocation of the new Wagon
    Wagons* new = (Wagons*) malloc(sizeof(Wagons));

    //Data of new Wagon
    new->idW = idW;
    new->next = NULL;
    new->prev = NULL;
    strcpy(new->productType, productType);

    //Search for correct Train
    Train* TTemp = *t;
    if(TTemp == NULL){
        printf("Empty train list\n");
        return;
    }
    while(TTemp->idT != idT){
        TTemp = TTemp->next;
    }

    //Search the position
    Wagons* WTemp = TTemp->wagons;
    Wagons* prevWTemp = NULL;
    if(WTemp == NULL){
        TTemp->wagons = new;
        TTemp->wagonsAmount++;
        return;
    }
    int i = 1;
    while(i != position){
        prevWTemp = WTemp;
        WTemp = WTemp->next;
        i++;
    }
    
    //Add in position
    if(i == 1){
        new->next = WTemp;
        TTemp->wagons->prev = new;
        TTemp->wagons = new;
        TTemp->wagonsAmount++;
        return;
    }
    new->next = WTemp;
    new->prev = prevWTemp;
    prevWTemp->next = new;
    if(WTemp != NULL) WTemp->prev = new;
    TTemp->wagonsAmount++;
}

