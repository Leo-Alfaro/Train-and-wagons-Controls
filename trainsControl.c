#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trainsControl.h"

void createTrainList(Train** t) {
	//allocate memory to the train list
	*t = (Train*)malloc(sizeof(Train));

	//set the pointers of the list
	(*t) -> next = NULL;
	(*t) -> wagons = NULL;
}

void addTrain(Train** t, int idT) {
	//if list is NULL, error
	if(*t == NULL) {
		return;
	}

	//allocate memory to the object
	Train *no = (Train*)malloc(sizeof(Train));
	Train *aux;

	//set the object's id with the new id
	no -> idT = idT;
	//set the wagon's pointer
	no -> wagons = NULL;
	//insert the object at the beginning of the list
	no -> next = *t;

	Train* TTemp = *t;
	while(TTemp != NULL && TTemp->idT != idT) {
		TTemp = TTemp->next;
	}
	if(TTemp == NULL) {
		*t = no;
		printf("\n-- Train added successfully! --\n\n");
	} else {
		printf("\n-- This id already exists --\n");
        free(no);
	}
}

void removeTrain(Train** t, int idT) {
	//if list is NULL, error
	if(*t == NULL) {
		return;
	}

	//create auxiliary pointers
	Train *temp = (*t) -> next;
	Train *aux = NULL;
	Train *aux2 = *t;

	//case where the object to remove is at the list's beginning
	if((*t) -> idT == idT) {
		aux = *t;
		*t = temp;
	} else {
		//search for the train with set id
		while(temp != NULL) {
			if(temp -> idT == idT) {
				aux2 -> next = temp -> next;
				//saves the object in the variable aux
				aux = temp;
				break;
			}
			//walks through the list
			temp = temp -> next;
			aux2 = aux2 -> next;
		}
		if(temp == NULL) {
			//object not found
			printf("\n-- This train does not exist --\n");
			return;
		} else {
			printf("\n-- Trains removed successfully! --\n\n");
		}
	}
	//free the object
	free(aux);
}

void printTrainList(Train** t) {
	//set a auxiliary pointer pointed to the list's start
	Train *aux = *t;

	//walks through the list untill aux -> next is NULL
	while(aux -> next != NULL) {
		//prints the train instance
		printf("[%d]", aux -> idT);

		int i = 0;
		Wagons *w = aux -> wagons;

		//print the train wagons
		while(i < aux -> wagonsAmount) {
			printf("[product: %s | id: %d]", w -> productType, w -> idW);
			i++;
			w = w -> next;
		}

		//changes the train instance
		aux = aux -> next;
		printf("\n");
	}
}

int addWagon(Train** t, int idW, char* productType, int position) {
	//Space allocation of the new Wagon
	Wagons* new = (Wagons*) malloc(sizeof(Wagons));
	if(new == NULL) {
		printf("Allocation memory error.");
		return 0;
	}

	//Data of new Wagon
	new->idW = idW;
	new->next = NULL;
	new->prev = NULL;
	strcpy(new->productType, productType);


	//Search the position
	Wagons* WTemp = (*t)->wagons;
	Wagons* prevWTemp = NULL;
	if(WTemp == NULL) {
		(*t)->wagons = new;
		(*t)->wagonsAmount++;
		return 1;
	}
	int i = 1;
	while(i != position) {
		prevWTemp = WTemp;
		WTemp = WTemp->next;
		i++;
	}

	//Add in position
	if(i == 1) {
		new->next = WTemp;
		(*t)->wagons->prev = new;
		(*t)->wagons = new;
		(*t)->wagonsAmount++;
		return 1;
	}
	new->next = WTemp;
	new->prev = prevWTemp;
	prevWTemp->next = new;
	if(WTemp != NULL) WTemp->prev = new;
	(*t)->wagonsAmount++;

	return 1;
}

Wagons* removeWagon(Train** t, int position) {
	//Search for correct Wagon
	Wagons* WTemp = (*t)->wagons;
	if(WTemp == NULL) {
		printf("-- Empty wagon list --\n");
		return NULL;
	}
	Wagons* prevWTemp = NULL;
	int i = 1;
	while(i != position && WTemp != NULL) {
		prevWTemp = WTemp;
		WTemp = WTemp->next;
		i++;
	}

	//Change pointers
	if(prevWTemp != NULL) prevWTemp->next = WTemp->next;
	if(WTemp == (*t)->wagons) (*t)->wagons = WTemp->next;
	if(WTemp->next != NULL) WTemp->next->prev = prevWTemp;

	//Decrease Amount
	(*t)->wagonsAmount--;

	//Cleaning Wagon Pointers
	WTemp->next = NULL;
	WTemp->prev = NULL;

	printf("\n-> Wagon removed successfully! --\n\n");
	return WTemp;
}

void copyWagonToAnotherTrain(Train** t, Train** t2, int positionToRemove, int positionToAdd) {
	//Remove from first Train
	Wagons* WTemp = removeWagon(t, positionToRemove);
	if(WTemp == NULL) {
		free(WTemp);
		return;
	}

	//Add in the second Train, only a copy
	int valid = addWagon(t2, WTemp->idW, WTemp->productType, positionToAdd);
	if(!valid) {
		free(WTemp);
		return;
	}

	//Free the memory
	free(WTemp);
}

int checkChar(char *input) {
	int num;
	while (1) {
		num = 0;
		printf("-- Enter your answer: --\n");
		if (fgets(input, sizeof(input), stdin) != NULL) {
			if (sscanf(input, "%d", &num) == 1) {
				num = atoi(input);
				break;
			} else {
				printf("------Invalid input, please enter an integer------\n");
			}
		} else {
			printf("-- Error reading input. --\n");
		}
	}
	memset(input, 0, strlen(input));
	setbuf(stdin, NULL);
	return num;
}

void changeOrderWagon(Train** t, int idW, int newPosition) {

	//Search for correct Wagon
	Wagons* WTemp = (*t)->wagons;
	if(WTemp == NULL) {
		printf("-- Empty wagon list --\n");
		return;
	}
	Wagons* prevWTemp = NULL;
	int i = 1;
	while(WTemp != NULL && idW != WTemp->idW) {
		prevWTemp = WTemp;
		WTemp = WTemp->next;
		i++;
	}
	if(WTemp == NULL) {
		printf("-- Wagon ID non-existent. --\n");
		return;
	}

	//Change pointers
	if(prevWTemp != NULL) prevWTemp->next = WTemp->next;
	if(WTemp == (*t)->wagons) (*t)->wagons = WTemp->next;
	if(WTemp->next != NULL) WTemp->next->prev = prevWTemp;

	//verify if the list its not empty
	Wagons* WTemp2 = (*t)->wagons;
	if(WTemp == NULL) {
		(*t)->wagons = WTemp2;
		WTemp2->next = NULL;
		WTemp2->prev = NULL;
		return;
	}

	//Search for correct Wagon
	Wagons* PrevWTemp2 = NULL;
	int j = 1;
	while(j != newPosition && WTemp2 != NULL) {
		PrevWTemp2 = WTemp2;
		WTemp2 = WTemp2->next;
		j++;
	}

	//Add in position
	if(j == 1) {
		WTemp->next = WTemp2;
		(*t)->wagons->prev = WTemp;
		(*t)->wagons = WTemp;
		return;
	}
	WTemp->next = WTemp2;
	WTemp->prev = PrevWTemp2;
	PrevWTemp2->next = WTemp;
	if(WTemp2 != NULL) WTemp2->prev = WTemp;
}

Train *searchForTrain(Train **t, int idT) {
	//Search for correct Train
	Train* TTemp = *t;
	if(TTemp == NULL) {
		printf("-- Empty train list. --\n");
		return NULL;
	}
	while(TTemp != NULL && TTemp->idT != idT) {
		TTemp = TTemp->next;
	}
	if(TTemp == NULL) {
		printf("-- Train ID non-existent. --\n");
		return NULL;
	}
	return TTemp;
}
