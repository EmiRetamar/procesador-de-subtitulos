#include "lista.h"

void escribirArch(FILE* archSalida, lista l) {
	lista act;
	int i;
	act = l;
	while(act != NULL) {
		fprintf(archSalida, "%ld\n", act->indice);
		fprintf(archSalida, "%.2ld:%.2ld:%.2ld,%.3ld --> %.2ld:%.2ld:%.2ld,%.3ld\n", act->tiempos[0], act->tiempos[1], act->tiempos[2], 
		act->tiempos[3], act->tiempos[4], act->tiempos[5], act->tiempos[6], act->tiempos[7]);
		for(i = 0; act->sub[i] != NULL; i++)
			fprintf(archSalida, "%s", act->sub[i]);
		act = act->sig;
	}
}
