#include "formatoArchEntradaEsValido.h"

int formatoArchEntradaEsValido(char* archEntrada, int webVTT) {
	int i = 0;
	char* extension;
	if(webVTT == 0) { // Significa que el archivo de entrada deberia ser SubRip
		while(archEntrada[i] != '\0' && archEntrada[i] != '.')
			i++;
		if(archEntrada[i] == '.') {
			extension = archEntrada + i; // archEntrada apunta al principio del arreglo, entonces me muevo i direcciones de memoria para que quede apuntado a la direccion donde esta la extension del archivo
			if(strcmp(extension, ".srt") != 0)
				return (0);
		}
		else {
			printf("Aviso: El archivo de entrada no tiene extension. Se debe ingresar un .srt o .vtt segun corresponda \n");
			return (0);
		}
	}
	else { // Significa que el archivo de entrada deberia ser WebVTT
		while(archEntrada[i] != '\0' && archEntrada[i] != '.')
			i++;
		if(archEntrada[i] == '.') {
			extension = archEntrada + i; // archEntrada apunta al principio del arreglo, entonces me muevo i direcciones de memoria para que quede apuntado a la direccion donde esta la extension del archivo
			if(strcmp(extension, ".vtt") != 0)
				return (0);
		}
		else {
			printf("Aviso: El archivo de entrada no tiene extension. Se debe ingresar un .srt o .vtt segun corresponda \n");
			return (0);
		}
	}
	return (1);
}
