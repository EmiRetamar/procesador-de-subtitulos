#ifndef procesarArchivo_h
#define procesarArchivo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long* convertirMillisAFormatoSubRip(long, long*);
void totalizarTiempos(long*, long*);
char** strConvert(char***, const char*);
int contarSaltosDeLinea(char*);
int* obtenerTamLineas(char*, int, int*);
char** copiarLineas(char*, char**, int);
struct nodo* asignarDatos(struct nodo*, long, long*, long*, long, long, char**);

#endif
