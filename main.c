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

	for(int i = 0; i < 1; ) {
		setbuf(stdin, NULL);

		printf("1-> add train\n2-> remove train\n3-> add wagon\n4-> remove wagon\n5-> change wagon to another train\n6-> change the order of the wagons\n7-> print train list\n8-> Exit\n");
		//scanf("%d", &n);
		n = checkChar(input);

		if(n == 1) {
			int id = 0;
			int tam = 0;

			printf("-> How many trains will be added?:\n");
			tam = checkChar(input);

			for(int i = 0; i < tam; i++) {
				printf("-> Type the %dB: train id:\n", i + 1);

				id = checkChar(input);
				addTrain(&l, id);
			}
			printf("\n-> Trains added successfully! --\n\n");
		}
		else if(n == 2) {
			int id = 0;

			printf("-> Type the id of the train that will be removed:\n");
			id = checkChar(input);

			removeTrain(&l, id);
			printf("\n-> Train removed successfully! --\n\n");
		}
		else if(n == 3) {
			int idT = 0;
			int idW = 0;
			char c[31];
			int p = 0;


			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			printf("\n-> Type the wagon's id:\n");
			idW = checkChar(input);

			printf("-> Type the wagon's product type:\n");
			printf("-- Enter your answer: --\n");
			scanf("%s", c);

			Train* TTemp = l;
			if(TTemp == NULL) {
				printf("-- Empty train list --\n");
				break;
			}
			while(TTemp->idT != idT) {
				TTemp = TTemp->next;
			}

			printf("-> Type the wagon's position between 1 and %d:\n", TTemp -> wagonsAmount + 1);
			scanf("%d", &p);

			if(TTemp -> wagonsAmount == 0) {
				p = 1;
			}

			addWagon(&l, idT, idW, c, p);
		}
		else if(n == 4) {
			int idT = 0;
			int idW = 0;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			printf("\n-> Type the wagon's id:\n");
			idW = checkChar(input);

			removeWagon(&l, idT, idW);
		}
		else if(n == 5) {
			int idT = 0;
			int id2T = 0;
			int pR = 0;
			int pA = 0;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			printf("\n-> Type the id of the second train:\n");
			id2T = checkChar(input);

			printf("\n-> Type the position of the wagon:\n");
			pR = checkChar(input);

			copyWagonToAnotherTrain(&l, idT, id2T, pR, pA);

		}
		else if(n == 6) {
			int idT = 0;
			int idW = 0;
			int nP;

			printf("-> Type the train's id:\n");
			idT = checkChar(input);

			printf("\n-> Type the wagon's id:\n");
			idW = checkChar(input);

			Train *aux = searchForTrain(&l, idT);
			printf("\n-> Type the wagon's new position between 1 and %d:\n", aux -> wagonsAmount);
			nP = checkChar(input);

			changeOrderWagon(&l, idT, idW, nP);
		}
		else if(n == 7) {
			printf("\n-- Train List --\n");
			printTrainList(&l);
			printf("-- Train List --\n\n");
		}
		else {
			break;
		}
	}

	printf("\n");

	return 0;
}
