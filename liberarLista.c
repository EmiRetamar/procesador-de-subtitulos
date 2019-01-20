#include "liberarLista.h"
#include "lista.h"

void liberarLista(lista act) {
	lista ant;
	while(act != NULL) {
		liberarMemoria(&(act->sub));
		ant = act;
		act = act->sig;
		free(ant);
	}
}
