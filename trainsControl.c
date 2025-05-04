#include <stdio.h>
#include <stdlib.h>
#include "trainsControl.h"

void createTrainList(Train** t){
    //allocate memory to the train list
    *t = (Train*)malloc(sizeof(Train));
    
    //set the pointers of the list
    (*t) -> next = NULL;
    (*t) -> wagons = NULL;
}

void addTrain(Train** t, int idT){
    //if list is NULL, error
    if(*t == NULL){
        return;
    }
    
    //allocate memory to the object
    Train *no = (Train*)malloc(sizeof(Train));
    
    //set the object's id with the new id
    no -> idT = idT;
    //set the wagon's pointer 
    no -> wagons = NULL;
    //insert the object at the beginning of the list
    no -> next = *t;
    
    //change the list's beginning
    *t = no;
}

void removeTrain(Train** t, int idT){
    //if list is NULL, error
    if(*t == NULL){
        return;
    }
    
    //create auxiliary pointers
    Train *temp = (*t) -> next;
    Train *aux = NULL;
    Train *aux2 = *t;
    
    //case where the object to remove is at the list's beginning
    if((*t) -> idT == idT){
        aux = *t;
        *t = temp;
    } else{
        //search for the train with set id
        while(temp != NULL){
            if(temp -> idT == idT){
                aux2 -> next = temp -> next;
                //saves the object in the variable aux
                aux = temp;
                break;
            }
            //walks through the list
            temp = temp -> next;
            aux2 = aux2 -> next;
        }
        if(temp == NULL){
            //object not found
            printf("\nThis train does not exist\n");
        }
    }
    //free the object
    free(aux);
}

void printTrainList(Train** t){
    //set a auxiliary pointer pointed to the list's start
    Train *aux = *t;
    
    //walks through the list untill aux -> next is NULL
    while(aux -> next != NULL){
        //prints the train instance
        printf("[%d]", aux -> idT);
        
        int i = 0;
        Wagons *w = aux -> wagons;
        
        //print the train wagons
        while(i < aux -> wagonsAmount){
            printf("[product: %s | id: %d]", w -> productType, w -> idW);
            i++;
            w = w -> next;
        }
        
        //changes the train instance
        aux = aux -> next;
        printf("\n");
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

