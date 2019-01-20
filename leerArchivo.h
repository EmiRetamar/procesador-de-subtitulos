#ifndef leerArchivo_h
#define leerArchivo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam 100
#define base 10

#ifndef tipoLista
#define tipoLista
typedef struct nodo* lista;
#endif

void asignarIndice(long*, char*);
void asignarTiempos(struct nodo*, char*);
long calcularTiemposEnMilis(long*, int*);
void asignarSubtitulo(FILE*, struct nodo*, int);
void asignarValoresSubRip(FILE*, struct nodo*, int);
void asignarValoresWebVTT(FILE*, struct nodo*, int);
int esTiempo(char*, int*);
void agregarHora(long*);

#endif
