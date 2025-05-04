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

int addWagon(Train** t, int idT, int idW, char* productType, int position){
    //Space allocation of the new Wagon
    Wagons* new = (Wagons*) malloc(sizeof(Wagons));
    if(new == NULL){
        printf("Allocation memory error.");
        return 0;
    }

    //Data of new Wagon
    new->idW = idW;
    new->next = NULL;
    new->prev = NULL;
    strcpy(new->productType, productType);

    //Search for correct Train
    Train* TTemp = *t;
    if(TTemp == NULL){
        printf("Empty train list.\n");
        return 0;
    }
    while(TTemp != NULL && TTemp->idT != idT){
        TTemp = TTemp->next;
    }
    if(TTemp == NULL){
        printf("Train ID non-existent.\n");
        return 0;
    }


    //Search the position
    Wagons* WTemp = TTemp->wagons;
    Wagons* prevWTemp = NULL;
    if(WTemp == NULL){
        TTemp->wagons = new;
        TTemp->wagonsAmount++;
        return 1;
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
        return 1;
    }
    new->next = WTemp;
    new->prev = prevWTemp;
    prevWTemp->next = new;
    if(WTemp != NULL) WTemp->prev = new;
    TTemp->wagonsAmount++;

    return 1;
}

Wagons* removeWagon(Train** t, int idT, int position){
    //Search for correct Train
    Train* TTemp = *t;
    if(TTemp == NULL){
        printf("Empty train list.\n");
        return NULL;
    }
    while(TTemp != NULL && TTemp->idT != idT){
        TTemp = TTemp->next;
    }
    if(TTemp == NULL){
        printf("Train ID non-existent.\n");
        return NULL;
    }

    //Search for correct Wagon
    Wagons* WTemp = TTemp->wagons;
    if(WTemp == NULL){
        printf("Empty wagon list\n");
        return NULL;
    }
    Wagons* prevWTemp = NULL;
    int i = 1;
    while(i != position && WTemp != NULL){
        prevWTemp = WTemp;
        WTemp = WTemp->next;
        i++;
    }

    //Change pointers
    if(prevWTemp != NULL) prevWTemp->next = WTemp->next;
    if(WTemp == TTemp->wagons) TTemp->wagons = WTemp->next;
    if(WTemp->next != NULL) WTemp->next->prev = prevWTemp;

    //Decrease Amount
    TTemp->wagonsAmount--;

    //Cleaning Wagon Pointers
    WTemp->next = NULL;
    WTemp->prev = NULL;

    return WTemp;
}

void copyWagonToAnotherTrain(Train** t, int idT, int id2T, int positionToRemove, int positionToAdd){
    //Remove from first Train
    Wagons* WTemp = removeWagon(t, idT, positionToRemove);
    if(WTemp == NULL){
        free(WTemp);
        return;
    }

    //Add in the second Train, only a copy
    int valid = addWagon(t, id2T, WTemp->idW, WTemp->productType, positionToAdd);
    if(!valid){
        free(WTemp);
        return;
    }
    
    //Free the memory
    free(WTemp);
}

void changeOrderWagon(Train** t, int idT, int idW, int newPosition){
    //Search for correct Train
    Train* TTemp = *t;
    if(TTemp == NULL){
        printf("Empty train list.\n");
        return;
    }
    while(TTemp != NULL && TTemp->idT != idT){
        TTemp = TTemp->next;
    }
    if(TTemp == NULL){
        printf("Train ID non-existent.\n");
        return;
    }

    //Search for correct Wagon
    Wagons* WTemp = TTemp->wagons;
    if(WTemp == NULL){
        printf("Empty wagon list\n");
        return;
    }
    Wagons* prevWTemp = NULL;
    int i = 1;
    while(WTemp != NULL && idW != WTemp->idW){
        prevWTemp = WTemp;
        WTemp = WTemp->next;
        i++;
    }
    if(WTemp == NULL){
        printf("Wagon ID non-existent.\n");
        return;
    }

    //Change pointers
    if(prevWTemp != NULL) prevWTemp->next = WTemp->next;
    if(WTemp == TTemp->wagons) TTemp->wagons = WTemp->next;
    if(WTemp->next != NULL) WTemp->next->prev = prevWTemp;

    //verify if the list its not empty
    Wagons* WTemp2 = TTemp->wagons;
    if(WTemp == NULL){
        TTemp->wagons = WTemp2;
        WTemp2->next = NULL;
        WTemp2->prev = NULL;
        return;
    }

    //Search for correct Wagon
    Wagons* PrevWTemp2 = NULL;
    int j = 1;
    while(j != newPosition && WTemp2 != NULL){
        PrevWTemp2 = WTemp2;
        WTemp2 = WTemp2->next;
        j++;
    }

    //Add in position
    if(j == 1){
        WTemp->next = WTemp2;
        TTemp->wagons->prev = WTemp;
        TTemp->wagons = WTemp;
        return;
    }
    WTemp->next = WTemp2;
    WTemp->prev = PrevWTemp2;
    PrevWTemp2->next = WTemp;
    if(WTemp2 != NULL) WTemp2->prev = WTemp;
}

