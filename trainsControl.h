#ifndef _TRAINS_CONTROL_H_
#define _TRAINS_CONTROL_H_

// Defines Trains and Wagons structs
struct train{
    int idT;
    int trainsAmount;
    // Pointer to first train   
    struct train* next;
    // Pointer to last wagon
    struct wagons* wagons; 
};
typedef struct train Train;

struct wagons{
    int idW;
    int wagonsAmount;   
    char productType[31];
    struct wagons* next;
    struct wagons* prev;
};
typedef struct wagons Wagons;

// Functions
void createTrainList(Train** t);
void addTrain(Train** t, int idT);
void removeTrain(Train** t, int idT);
void addWagon(Train** t, int idT, int idW, char* productType, int position);
void removeWagon(Train** t, int idT, int idW);
void changeWagonToAnotherTrain(Train** t, int idT, int id2T, int idW);
void changeOrderWagon(Train** t, int idT);
void printTrainList(Train** t);

#endif