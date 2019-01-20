#include "lista.h"

lista convertirVTTaSubRip(lista l) { // Asigno los indices para completar la conversion a SubRip
	int indice = 1;
	lista act;
	act = l;
	while(act != NULL) {
		act->indice = indice++;
		act = act->sig;
	}
	return (l);
}
