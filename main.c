#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trainsControl.h"

int main()
{
    Train *l = NULL;
    createTrainList(&l);
    int n = 0;
    
    for(int i = 0; i < 1; ){
        printf("-- Type your action:\n1-> add train\n2-> remove train\n3-> add wagon\n4-> remove wagon\n5-> change wagon to another train\n6-> change the order of the wagons\n7-> print train list\n8-> Exit\n");              
        scanf("%d", &n);
        if(n == 1){
            int id = 0;
            int tam = 0;
            printf("-- How many trains will be added?:\n");
            scanf("%d", &tam);
            for(int i = 0; i < tam; i++){
                printf("-- Type the %dº train id:\n", i + 1);
                scanf("%d", &id);
                addTrain(&l, id);
            }
            printf("\n-- Trains added successfully! --\n\n");
        }
        else if(n == 2){
            int id = 0;
            printf("-- Type the id of the train that will be removed:\n");
            scanf("%d", &id);
            removeTrain(&l, id);
            printf("\n-- Train removed successfully! --\n\n");
        }
        else if(n == 3){
            int idT = 0;
            int idW = 0;
            char c[31];
            int p = 0;
            
            printf("-- Type the train id:\n");
            scanf("%d", &idT);
            
            printf("\n");
            
            printf("-- Type the %dº wagon id:\n", i + 1);
            scanf("%d", &idW);
            printf("-- Type the %dº wagon product type:\n", i + 1);
            scanf("%s", c);
            
            Train* TTemp = l;
            if(TTemp == NULL){
                printf("Empty train list\n");
                break;
            }
            while(TTemp->idT != idT){
                TTemp = TTemp->next;
            }
            
            printf("-- Type the %dº wagon position between 1 and %d:\n", i + 1, TTemp -> wagonsAmount + 1);
            scanf("%d", &p);
            
            if(TTemp -> wagonsAmount == 0){
                p = 1;
            }
            
            addWagon(&l, idT, idW, c, p);
        }
        else if(n == 4){
            int idT = 0;
            int idW = 0;
            
            //removeWagon(&l, idT, idW);
        }
        else if(n == 5){
            int idT = 0;
            int idW = 0;
            int id2T = 0;
            
            //changeWagonToAnotherTrain(&l, idT, id2T, idW);
            
        }
        else if(n == 6){
            int idT = 0;
        
            //changeOrderWagon(&l, idT);
        }
        else if(n == 7){
            printf("\n-- Train List --\n");
            printTrainList(&l);
            printf("-- Train List --\n\n");
        }
        else{
            break;
        }
    }

    printf("\n");

    return 0;
}
