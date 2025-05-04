#ifndef _TRAINS_CONTROL_H_
#define _TRAINS_CONTROL_H_

// Defines Trains and Wagons structs
struct train {
	//Train ID
	int idT;
	//Wagons Amount of this Train
	int wagonsAmount;
	// Pointer to first train
	struct train* next;
	// Pointer to first wagon
	struct wagons* wagons;
};
typedef struct train Train;

struct wagons {
	//Wagons ID
	int idW;
	//Product Type from Wagon
	char productType[31];
	//Doubly linked List
	struct wagons* next;
	struct wagons* prev;
};
typedef struct wagons Wagons;

// Functions
void createTrainList(Train** t);
void addTrain(Train** t, int idT);
void removeTrain(Train** t, int idT);
int addWagon(Train** t, int idT, int idW, char* productType, int position);
Wagons* removeWagon(Train** t, int idT, int position);
void copyWagonToAnotherTrain(Train** t, int idT, int id2T, int positionToRemove, int positionToAdd);
void changeOrderWagon(Train** t, int idT, int idW, int newPosition);
void printTrainList(Train** t);
int checkChar(char *input);
int checkNum(int input);
int checkNum(int input);
Train *searchForTrain(Train **t, int idT);

#endif
