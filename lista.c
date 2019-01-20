#include "lista.h"
#include "liberarMemoria.h"

void crearLista(lista* l) {
	*l = NULL;
}

void agregarALista(lista* l, struct nodo datos) {
	lista nue, act, ult;
	nue = (struct nodo*) malloc(sizeof(struct nodo));
	asignarANodo(nue, datos);
	if(*l == NULL)
		*l = nue;
	else {
		act = *l;
		while(act != NULL) {
			ult = act;
			act = act->sig;
		}
		ult->sig = nue;
	}
}

void asignarANodo(lista nue, struct nodo datos) {
	int i;
	nue->indice = datos.indice;
	for(i = 0; i < 8; i++) 
		nue->tiempos[i] = datos.tiempos[i];
	nue->sub = NULL;
	for(i = 0; datos.sub[i] != NULL; i++) {
		nue->sub = (char**) realloc(nue->sub, sizeof(char*) * (i+1));
		nue->sub[i] = (char*) malloc(sizeof(char) * strlen(datos.sub[i]) + 1); // Aloco un byte mas del tamaño del string para que cuando se asigne el \0 en el strcpy no se superen los limites del arreglo
		strcpy(nue->sub[i], datos.sub[i]);
	}
	nue->sub = (char**) realloc(nue->sub, sizeof(char*) * (i+1));
	nue->sub[i] = NULL; // Para saber en donde termina el arreglo de punteros
	nue->startMilis = datos.startMilis;
	nue->endMilis = datos.endMilis;
	nue->sig = NULL;
}

void insertarNodo(lista l, struct nodo datos) {
	lista nue, ant, act;
	nue = (lista) malloc(sizeof(struct nodo));
	asignarANodo(nue, datos);
	act = l;
	while(act != NULL && act->startMilis < datos.startMilis) {
		ant = act;
		act = act->sig;
	}
	ant->sig = nue;
	nue->sig = act;
}

lista eliminarNodo(lista l, long numNodo) {
	lista act, ant, ult;
	act = l;
	while(act != NULL && act->indice < numNodo) {
		ant = act;
		act = act->sig;
	}
	if(act == NULL)
		printf("No existe el numero de subtitulo que se quiere eliminar \n");
	else {
		ult = act->sig;
		ant->sig = ult;
		liberarMemoria(&(act->sub));
		free(act);
	}
	return (ult);
}
