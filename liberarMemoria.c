#include "liberarMemoria.h"

void liberarMemoria(char*** sub) {
	int i;
	for(i = 0; (*sub)[i] != NULL; i++) {
		free((*sub)[i]); // Libero la memoria reservada para cada uno de los punteros a char
	}
	free(*sub); // Libero la memoria reservada para el puntero al array de punteros
}
