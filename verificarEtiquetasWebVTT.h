#ifndef verificarEtiquetasWebVTT_h
#define verificarEtiquetasWebVTT_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int esCorrecto(char*, char**);
int verificarCierreEtiqueta(char*, int*, char*);
void liberarMemoriaPila(char***, int);

#endif
