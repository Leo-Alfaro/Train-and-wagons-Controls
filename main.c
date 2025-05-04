#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trainsControl.h"

int main()
{
	Train *l = NULL;
	createTrainList(&l);
	int n = 0;
	char input[15];
	int id;
	int tam;
	int idT;
	int idW;
	int p;
	int id2T;
	int pR;
	int pA;

	while (n != 8)
	{
		setbuf(stdin, NULL);

		printf("1-> add train\n2-> remove train\n3-> add wagon\n4-> remove wagon\n5-> change wagon to another train\n6-> change the order of the wagons\n7-> print train list\n8-> Exit\n");
		n = checkChar(input);

		switch (n)
		{
		case 1:
			id = 0;
			tam = 0;

			printf("-> How many trains will be added?:\n");
			tam = checkChar(input);

			for (int i = 0; i < tam; i++)
			{
				printf("-> Type the %dº: train id:\n", i + 1);

				id = checkChar(input);
				addTrain(&l, id);
			}
			break;
		case 2:
			id = 0;

			printf("-> Type the id of the train that will be removed:\n");
			id = checkChar(input);

			removeTrain(&l, id);
			printf("\n-> Train removed successfully! --\n\n");
			break;
		case 3:
			idT = 0;
			idW = 0;
			char c[31];
			p = 0;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			printf("\n-> Type the wagon's id:\n");
			idW = checkChar(input);

			printf("-> Type the wagon's product type:\n");
			printf("-- Enter your answer: --\n");
			scanf("%s", c);

			Train *aux = searchForTrain(&l, idT);
			if(aux == NULL) {
				break;
			}

			printf("-> Type the wagon's position between 1 and %d:\n", aux->wagonsAmount + 1);
			scanf("%d", &p);

			while(1) {
				if(p >= 1 && p <= (aux->wagonsAmount+1)) {
					break;
				}
				printf("-> Invalid position");
				printf("-> Type the wagon's position between 1 and %d:\n", aux->wagonsAmount + 1);
				scanf("%d", &p);
			}

			if (aux->wagonsAmount == 0)
			{
				p = 1;
			}

			addWagon(&aux, idW, c, p);
			break;
		case 4:
			idT = 0;
			idW = 0;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			aux = searchForTrain(&l, idT);
			if(aux == NULL) {
				break;
			}

			printf("\n-> Type the wagon's position between 1 and %d:\n", aux->wagonsAmount);
			scanf("%d", &idW);

			while(1) {
				if(idW >= 1 && idW <= (aux->wagonsAmount)) {
					break;
				}
				printf("-> Invalid position");
				printf("-> Type the wagon's position between 1 and %d:\n", aux->wagonsAmount);
				scanf("%d", &idW);
			}


			removeWagon(&aux, idW);
			break;
		case 5:
			idT = 0;
			id2T = 0;
			pR = 0;
			pA = 0;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			aux = searchForTrain(&l, idT);
			if(aux == NULL) {
				break;
			}

			printf("\n-> Type the id of the second train:\n");
			id2T = checkChar(input);

			Train* aux2 = searchForTrain(&l, id2T);
			if(aux2 == NULL) {
				break;
			}

			printf("\n-> Type the position of the wagon to removed:\n");
			scanf("%d", &pR);

			while(1) {
				if(pR >= 1 && pR <= (aux->wagonsAmount+1)) {
					break;
				}
				printf("-> Invalid position");
				printf("-> Type the wagon's position between 1 and %d:\n", aux->wagonsAmount + 1);
				scanf("%d", &pR);
			}

			printf("\n-> Type the position of the wagon to added:\n");
			scanf("%d", &pA);

			while(1) {
				if(pA >= 1 && pA <= (aux2->wagonsAmount+1)) {
					break;
				}
				printf("-> Invalid position");
				printf("-> Type the wagon's position between 1 and %d:\n", aux2->wagonsAmount + 1);
				scanf("%d", &pA);
			}

			copyWagonToAnotherTrain(&aux, &aux2, pR, pA);

			break;
		case 6:
			idT = 0;
			idW = 0;
			int nP;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			printf("\n-> Type the wagon's id:\n");
			idW = checkChar(input);

			aux = searchForTrain(&l, idT);
			if(aux == NULL) {
				break;
			}
			printf("\n-> Type the wagon's new position between 1 and %d:\n", aux->wagonsAmount);
			scanf("%d", &nP);

			while(1) {
				if(nP >= 1 && nP <= (aux->wagonsAmount)) {
					break;
				}
				printf("-> Invalid position");
				printf("-> Type the wagon's position between 1 and %d:\n", aux->wagonsAmount);
				scanf("%d", &nP);
			}

			changeOrderWagon(&aux, idW, nP);
			break;
		case 7:
			printf("\n-- Train List --\n");
			printTrainList(&l);
			printf("-- Train List --\n\n");
			break;
		default:
			break;
		}
		printf("\n");
	}
	return 0;
}
