#ifndef lista_h
#define lista_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
		char** sub;
		long indice;
		long tiempos[8];
		long startMilis;
		long endMilis;
		struct nodo* sig;
};

#ifndef tipoLista
#define tipoLista
typedef struct nodo* lista;
#endif

void crearLista(lista*);
void agregarALista(lista*, struct nodo);
void asignarANodo(lista, struct nodo);
void insertarNodo(lista, struct nodo);
lista eliminarNodo(lista, long);

#endif
