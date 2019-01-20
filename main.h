#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>

#ifndef tipoLista
#define tipoLista
typedef struct nodo* lista;
#endif

int verificarParametros(int, char**, int*, int*, int*, int*);
int formatoArchEntradaEsValido(char*, int);
lista copiarArch(FILE*, lista, int);
lista verificarEtiquetasWebVTT(lista);
lista convertirVTTaSubRip(lista);
void ayuda();
lista desplazarSub(lista, long);
lista separarSubSolapados(lista);
lista eliminarSub(lista, long);
lista insertarSub(lista, long, long, char*);
lista duracionMinSub(lista, long);
lista aumentarDuracionSub(lista);
lista reducirTiemposSub(lista, long);
void validarSub(lista);
void escribirArch(FILE*, lista);
void liberarLista(lista);

#endif
