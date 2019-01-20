#include "verificarEtiquetasWebVTT.h"
#include "lista.h"

lista verificarEtiquetasWebVTT(lista l) { // Basicamente lo que hace es que a las lineas de subtutulos que tengan errores se les reemplaza el texto por "Error de Formato" y a las que estan correctas solo se les quita las etiquetas y se les deja el texto restante
	lista act;
	char* linea; // Guarda temporalmete una linea de la parte del texto de un subtitulo
	int i;
	act = l;
	while(act != NULL) {
		for(i = 0; act->sub[i] != NULL; i++) {
			if(strcmp(act->sub[i], "\n") != 0) { // Si el string a procesar es un salto de linea lo ignoro porque es el espacio en blanco del subtitulo y se sabe que como es una seccion especial del formato webVTT no tiene etiquetas
				linea = NULL;
				if(esCorrecto(act->sub[i], &linea) == 1) { // esCorrecto devuelve 1 si es true y 0 si es false
					free(act->sub[i]); // Libero lo que habia porque ya no sirve, necesito asignar el texto de la linea sin las etiquetas
					act->sub[i] = (char*) malloc(sizeof(char) * strlen(linea) + 1); // Reservo memoria nuevamente para asignar el texto valido. El +1 es para luego asignar el fin de linea con \0
					strcpy(act->sub[i], linea);
				}
				else {
					free(act->sub[i]);
					act->sub[i] = (char*) malloc(sizeof(char) * strlen("Error de Formato.\n") + 1);
					strcpy(act->sub[i], "Error de Formato.\n");
				}
				free(linea);
			}
		}
		act = act->sig;
	}
	return (l);
}

int esCorrecto(char* lineaCompleta, char** lineaTexto) { // Se libera correctamente toda la memoria alocada para la pila de etiquetas
	int tope = 0, iEtiq = 0, i, j = 0, ok = 0; // ok es un booleano que cambia cuando aparece un "<" es para verificar si me viene un ">" y el ok esta en 0 entonces significa que el subtitulo tiene error, si esta en 1 significa que me vino el "<" entonces sigo procesando y cambio el ok a 0
	char** pila = NULL;
	for(i = 0; lineaCompleta[i] != '\0'; i++) { // <i><hola>- Det ar inte varmt.</hola></i>
		switch(lineaCompleta[i]) { 
			case '<':
				if(ok == 0) {
					ok = 1; // Cada vez que ok se cambie a 1 se va a extender el arreglo de punteros
					if(lineaCompleta[i+1] != '/') {  // Si el caracter siguiente no es un "/" significa que la etiqueta que se esta procesando es de apertura
						pila = (char**) realloc(pila, sizeof(char*) * (tope+1)); // Aloco memoria para el arreglo de punteros
						pila[tope] = NULL;
					}
				}
				else { // Porque puede pasar que me venga algo asi hola "<b hola </b>" osea que me llegue otro "<" antes del cierre del que aparecio anteriormente
					liberarMemoriaPila(&pila, tope-1);
					return (0);
				}
				break;
			case '/': // Aca deberia verificar con lo que tengo en el tope de la pila de etiquetas
				if(ok == 0) { // Para que venga '/' antes tiene que haber venido un '<'
					liberarMemoriaPila(&pila, tope-1);
					return (0);
				}
				else {
					tope--;
					if(tope >= 0) {
						i++;
						if(verificarCierreEtiqueta(lineaCompleta, &i, pila[tope]) == 0) { // Devuelve 0 si el cierre de la etiqueta es incorrecto, 1 en caso de que sea correcto
							liberarMemoriaPila(&pila, tope);
							return (0); 
						}
						else {
							free(pila[tope]); // Libero el puntero del string que ya procese
							ok = 0; // Cambio ok a 0 porque si viene por aca es que la etiqueta de cierre es correcta entonces significa que aparecio el ">"
						}
					}
					else {
						free(pila); // Como sale porque se encontro un cierre de etiqueta que esta demas porque la pila esta vacia, se libera la memoria alocada para el arreglo de punteros y devuelve false
						return (0);
					}
				}
				break;
			case '>':
				if(ok == 0) {
					liberarMemoriaPila(&pila, tope-1);
					return (0);
				}
				else {
					ok = 0;
					pila[tope] = (char*) realloc(pila[tope], sizeof(char) * (iEtiq+1));
					pila[tope][iEtiq] = '\0';
					tope++;
					iEtiq = 0;
				}
				break;
			default:
				if(ok == 0) { // Si ok es 0 significa que el caracter que se esta procesando no pertenece a una etiqueta
					*lineaTexto = (char*) realloc(*lineaTexto, sizeof(char) * (j+1));
					(*lineaTexto)[j++] = lineaCompleta[i];
				}
				else { // Si viene por aca significa que se esta procesando una etiqueta, entonces se copia el caracter a la pila de etiquetas
					pila[tope] = (char*) realloc(pila[tope], sizeof(char) * (iEtiq+1));
					pila[tope][iEtiq++] = lineaCompleta[i];
				}
		}
	}
	*lineaTexto = (char*) realloc(*lineaTexto, sizeof(char) * (j+1));
	(*lineaTexto)[j] = '\0';
	free(pila);
	return (1);
} // Caracteres especiales "<" "/" y ">" si viene alguno de esos hay que hacer algo segun corresponda

int verificarCierreEtiqueta(char* lineaCompleta, int* i, char* etiqueta) {
	int j;
	for(j = 0; etiqueta[j] != '\0'; j++) {
		if(etiqueta[j] != lineaCompleta[*i]) // No verifico si llegue al fin de linea en el string de lineaCompleta[*i] porque tiene un \n antes que el \0 entonces se que si llego a salto de linea no me va a coincidir con etiqueta[j] y va a retornar falso
			return (0);
		(*i)++;
	}
	if(lineaCompleta[*i] != '>')
		return (0);
	return (1);
}

void liberarMemoriaPila(char*** pila, int tope) {
	if(tope >= 0) {
		for(; tope >= 0; tope--)
			free((*pila)[tope]);
	}
	free(*pila);
}
