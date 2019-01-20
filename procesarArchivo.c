#include "procesarArchivo.h"
#include "lista.h"
#include "liberarMemoria.h"

lista desplazarSub(lista l, long milis) {
	lista act;
	long tiempo[4];
	act = l;
	convertirMillisAFormatoSubRip(milis, tiempo);
	while(act != NULL) {
		totalizarTiempos(act->tiempos, tiempo);
		act->startMilis += milis;
		act->endMilis += milis;
		act = act->sig;
	}
	return (l);
}

void totalizarTiempos(long* tiempos, long* tiemposAux) {
	int i, j;
	for(i = 0, j = 0; i < 8; i++, j++) {
		if(j > 3) // Si j supera 3 la inicializo a 0 porque mi arreglo tiemposAux solo llega hasta la posicion 3
			j = 0;
		switch (i) {
			case 0:
				tiempos[i] += tiemposAux[j]; // Totaliza las horas de inicio del subtitulo (en este caso no puede suceder overflow)
				break;
			case 1:
				if((tiempos[i] + tiemposAux[j]) < 60) // Si no hay overflow sumo normalmente, sino acomodo los tiempos como debe ser
					tiempos[i] += tiemposAux[j]; // Totaliza los minutos de inicio del subtitulo
				else {
					tiempos[i] += tiemposAux[j]; // Totaliza los minutos de inicio del subtitulo
					tiempos[i] -= 60;
					(tiempos[i-1])++; // No se puede producir overflow en las horas asi que no se verifica nada en este caso
				}
				break;
			case 2:
				if((tiempos[i] + tiemposAux[j]) <  60) // Si no hay overflow sumo normalmente, sino acomodo los tiempos como debe ser
					tiempos[i] += tiemposAux[j]; // Totaliza los segundos de inicio del subtitulo
				else {
					tiempos[i] += tiemposAux[j]; // Totaliza los segundos de inicio del subtitulo
					tiempos[i] -= 60;
					(tiempos[i-1])++;
					if(tiempos[i-1] == 60) { // Los minutos podrian estar en 59 y en ese caso habria overflow en los minutos
						tiempos[i-1] -= 60;
						tiempos[i-2]++;
					}
				}
				break;
			case 3:
				if((tiempos[i] + tiemposAux[j]) < 1000) // Si no hay overflow sumo normalmente, sino acomodo los tiempos como debe ser
					tiempos[i] += tiemposAux[j]; // Totaliza los milisegundos de inicio del subtitulo
				else {
					tiempos[i] += tiemposAux[j]; // Totaliza los milisegundos de inicio del subtitulo
					tiempos[i] -= 1000;
					(tiempos[i-1])++;
					if(tiempos[i-1] == 60) { // Los segundos podrian estar en 59 y en ese caso habria overflow en los segundos
						tiempos[i-1] -= 60;
						tiempos[i-2]++;
					}
				}
				break;
			case 4:
				tiempos[i] += tiemposAux[j]; // Totaliza las horas de inicio del subtitulo (en este caso no puede suceder overflow)
				break;
			case 5:
				if((tiempos[i] + tiemposAux[j]) < 60) // Si no hay overflow sumo normalmente, sino acomodo los tiempos como debe ser
					tiempos[i] += tiemposAux[j]; // Totaliza los minutos de inicio del subtitulo
				else {
					tiempos[i] += tiemposAux[j]; // Totaliza los minutos de inicio del subtitulo
					tiempos[i] -= 60;
					(tiempos[i-1])++; // No se puede producir overflow en las horas asi que no se verifica nada en este caso
				}
				break;
			case 6:
				if((tiempos[i] + tiemposAux[j]) <  60) // Si no hay overflow sumo normalmente, sino acomodo los tiempos como debe ser
					tiempos[i] += tiemposAux[j]; // Totaliza los segundos de inicio del subtitulo
				else {
					tiempos[i] += tiemposAux[j]; // Totaliza los segundos de inicio del subtitulo
					tiempos[i] -= 60;
					(tiempos[i-1])++;
					if(tiempos[i-1] == 60) { // Los minutos podrian estar en 59 y en ese caso habria overflow en los minutos
						tiempos[i-1] -= 60;
						tiempos[i-2]++;
					}
				}
				break;
			case 7:
				if((tiempos[i] + tiemposAux[j]) < 1000) // Si no hay overflow sumo normalmente, sino acomodo los tiempos como debe ser
					tiempos[i] += tiemposAux[j]; // Totaliza los milisegundos de inicio del subtitulo
				else {
					tiempos[i] += tiemposAux[j]; // Totaliza los milisegundos de inicio del subtitulo
					tiempos[i] -= 1000;
					(tiempos[i-1])++;
					if(tiempos[i-1] == 60) { // Los segundos podrian estar en 59 y en ese caso habria overflow en los segundos
						tiempos[i-1] -= 60;
						tiempos[i-2]++;
					}
				}
				break;
		}
	}
}

lista separarSubSolapados(lista l) { // Separa subtitulos solapados, y los deja a 75 milisegundos entre uno y otro
	lista ant, act;
	long tiempo[4];
	int i, j;
	act = l;
	ant = act;
	act = act->sig;
	while(act != NULL) {
		if(ant->endMilis >= act->startMilis) { // Si el subtitulo anterior termina antes que comience su siguiente
			act->startMilis = ant->endMilis + 75; // Muevo el subtitulo inicial de act a 75 milisegundos de el final del subtitulo ant
			convertirMillisAFormatoSubRip(act->startMilis, tiempo);
			for(i = 0; i < 4; i++) // Modifico solo el tiempo de inicio del subtitulo porque fue el que cambie de lugar
				act->tiempos[i] = tiempo[i];
			if(act->startMilis >= act->endMilis) { // Porque puede pasar que al mover el tiempo de inicio del subtitulo actual quede mayor que el tiempo de fin de subtitulo, si el subtitulo tenia una duracion muy corta
				act->endMilis = act->startMilis + 75;
				convertirMillisAFormatoSubRip(act->endMilis, tiempo);
				for(j = 0; j < 4; i++, j++) // Modifico solo el tiempo de fin del subtitulo porque fue el que cambie de lugar
					act->tiempos[i] = tiempo[j];
			}
		}
		ant = act;
		act = act->sig;
	}
	return (l);
}

lista eliminarSub(lista l, long indice) {
	lista act;
	act = l;
	if((act = eliminarNodo(act, indice)) != NULL) {
		while(act != NULL) {
			act->indice--;
			act = act->sig;
		}
	}
	return(l);
}

lista insertarSub(lista l, long startmilis, long endmilis, char* texto) {
	struct nodo datos;
	lista ant, act;
	long tiempoInicial[4], tiempoFinal[4];
	char** textConvert;
	act = l;
	while(act != NULL && act->startMilis < startmilis) { // Mientras el puntero sea distinto de NULL y el startMilis del nodo sea menos que el startmilis buscado, voy avanzando en la lista
		ant = act;
		act = act->sig;
	}
	strConvert(&textConvert, texto);
	asignarDatos(&datos, ant->indice + 1, convertirMillisAFormatoSubRip(startmilis, tiempoInicial), convertirMillisAFormatoSubRip(endmilis, tiempoFinal), startmilis, endmilis, textConvert);
	insertarNodo(l, datos);
	while(act != NULL) { // Sigo avanzando para modificar los indices siguientes
		(act->indice)++;
		act = act->sig;
	}
	liberarMemoria(&textConvert); // Libero la memoria alocada para textConvert
	liberarMemoria(&(datos.sub)); // Libero toda la memoria alocada para el campo sub
	return (l);
}

char** strConvert(char*** dst, const char* src) { 
	int i, j, k;
	*dst = (char**) malloc(sizeof(char*)); // Para ingresar al contenido tengo que poner *** para el puntero al contenido ** (char*) y para el puntero al arreglo de punteros * (char**). Si no pongo nada estoy posicionado en la direccion donde esta alojado el puntero al arreglo de punteros.
	**dst = NULL;
	for(i = 0, j = 0, k = 0; src[k] != '\0'; k++) {
		if(!(src[k] == '\\' && src[k+1] == 'n')) {
			(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+1));
			(*dst)[i][j] = src[k];
			j++;
		}
		else {
			k++; // Descarta la n
			(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+1));
			(*dst)[i][j] = '\n';
			j++;
			(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+1));
			(*dst)[i][j] = '\0';
			j = 0;
			i++;
			*dst = (char**) realloc(*dst, sizeof(char*) * (i+1)); // Aumento el tamaño del arreglo de punteros
			(*dst)[i] = NULL;
		}
	}
	if((*dst)[i] == NULL) { // Significa que el ultimo caracter de src era un \n y en ese caso ya se aloco memoria para extender el arreglo de punteros
		if(strcmp((*dst)[i-1], "\n") != 0) {
			(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+2)); // +2 porque se debe copiar el \n y el \0 (j esta en 0)
			strcpy((*dst)[i], "\n");
			i++;
			*dst = (char**) realloc(*dst, sizeof(char*) * (i+1)); // Aumento el tamaño del arreglo de punteros
			(*dst)[i] = NULL; // Para saber cuando termina el arreglo de punteros
		}
	}
	else {
		(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+1)); // Aumento el tamaño del arreglo de punteros
		(*dst)[i][j] = '\n'; // Agrego un \n porque no habia uno al final
		j++;
		(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+1)); // Aumento tamaño y agrego un \0 para marcar fin del string
		(*dst)[i][j] = '\0';
		i++;
		*dst = (char**) realloc(*dst, sizeof(char*) * (i+1)); // Aumento el tamaño del arreglo de punteros
		(*dst)[i] = (char*) realloc((*dst)[i], sizeof(char) * (j+2)); // +2 porque se debe copiar el \n y el \0 (j esta en 0)
		strcpy((*dst)[i], "\n"); // Se agrega el salto de linea final, porque el formato SubRip establece que los subtitulos terminen con un \n
		i++;
		*dst = (char**) realloc(*dst, sizeof(char*) * (i+1)); // Aumento el tamaño del arreglo de punteros
		(*dst)[i] = NULL; // Para saber cuando termina el arreglo de punteros
		printf("Salio de strConvert por el else \n");
	}
	return (*dst);
}

struct nodo* asignarDatos(struct nodo* datos, long indice, long* tiempoInicial, long* tiempoFinal, long startmilis, long endmilis, char** textConvert) {
	int i, j;
	datos->indice = indice; // El indice de datos sera el siguiente que el de ant
	for(i = 0, j = 0; i < 4; i++, j++)
		datos->tiempos[i] = tiempoInicial[j]; // Se asignan los tiempos
	for(j = 0; i < 8; i++, j++) 
		datos->tiempos[i] = tiempoFinal[j];
	datos->sub = NULL;
	for(i = 0; textConvert[i] != NULL; i++) { // Copio el subtitulo a la struct
		datos->sub = (char**) realloc(datos->sub, sizeof(char*) * (i+1)); // Extiendo el array de punteros de la struct
		datos->sub[i] = (char*) malloc(sizeof(char) * strlen(textConvert[i]) + 1); // Aloco memoria para cada uno de los punteros a string
		strcpy(datos->sub[i], textConvert[i]);
	}
	datos->sub = (char**) realloc(datos->sub, sizeof(char*) * (i+1)); // Extiendo el array de punteros de la struct
	datos->sub[i] = NULL;
	datos->startMilis = startmilis;
	datos->endMilis = endmilis;
	return (datos);
}

lista duracionMinSub(lista l, long milis) {
	lista act, ult; // Act es el subtitulo que se procesa y ult es su siguiente
	long tiempo[4];
	int i, j;
	ult = l;
	act = ult;
	ult = ult->sig;
	while(ult != NULL) {
		if((act->endMilis - act->startMilis) < milis) {
			if((ult->startMilis - act->endMilis) > 75) { // Solo hago el procesamiento si se puede aumentar el tiempo del subtitulo, en caso de que este a 75 milisegundos o menos de su siguiente no se puede hacer
				while((act->endMilis - act->startMilis) < milis && (ult->startMilis - act->endMilis) > 75)
					act->endMilis++;
				convertirMillisAFormatoSubRip(act->endMilis, tiempo); // El unico que modifico es endMilis entonces solo convierto ese campo a formato SubRip
				for(i = 7, j = 3; i > 3; i--, j--) // Actualizo el tiempo de fin del subtitulo
					act->tiempos[i] = tiempo[j];
			}
			else
				printf("En la funcion duracionMinSub. No se puede modificar el tiempo del subtitulo %ld porque esta a menos de 75 milisegundos de su siguiente \n", act->indice);
		}
		act = ult;
		ult = ult->sig;
	}
	while((act->endMilis - act->startMilis) < milis) // Procesa el ultimo subtitulo
		act->endMilis++; // En este caso se puede aumentar la duracion hasta milis sin ningun problema ya que este subtitulo no tiene un siguiente
	convertirMillisAFormatoSubRip(act->endMilis, tiempo); // El unico que modifico es endMilis entonces solo convierto ese campo a formato SubRip
	for(i = 7, j = 3; i > 3; i--, j--) // Actualizo el tiempo de fin del subtitulo
		act->tiempos[i] = tiempo[j];
	return (l);
}

lista aumentarDuracionSub(lista l) {
	lista act, ult; // Act es el subtitulo que se procesa y ult es su siguiente
	long tiempo[4];
	int i, j, tamSub;
	ult = l;
	act = ult;
	ult = ult->sig;
	while(ult != NULL) {
		tamSub = 0;
		for(i = 0; act->sub[i] != NULL && strcmp(act->sub[i], "\n") != 0; i++) // Cuento el total de caracteres del subtitulo
			tamSub += (strlen(act->sub[i]) - 1); // No cuento el salto de linea de ninguna de las lineas
		if((tamSub / (act->endMilis - act->startMilis)) > 25) {
			if((ult->startMilis - act->endMilis) > 75) {
				while((tamSub / (act->endMilis - act->startMilis)) > 25 && (ult->startMilis - act->endMilis) > 75)
					act->endMilis++;
				convertirMillisAFormatoSubRip(act->endMilis, tiempo); // El unico que modifico es endMilis entonces solo convierto ese campo a formato SubRip
				for(i = 7, j = 3; i > 3; i--, j--) // Actualizo el tiempo de fin del subtitulo
					act->tiempos[i] = tiempo[j];
			}	
			else
				printf("En la funcion aumentarDuracionSub. No se puede modificar el tiempo del subtitulo %ld porque esta a menos de 75 milisegundos de su siguiente \n", act->indice);
		}
		act = ult;
		ult = ult->sig;
	}
	while((tamSub / (act->endMilis - act->startMilis)) > 25)
		act->endMilis++;
	convertirMillisAFormatoSubRip(act->endMilis, tiempo); // El unico que modifico es endMilis entonces solo convierto ese campo a formato SubRip
	for(i = 7, j = 3; i > 3; i--, j--) // Actualizo el tiempo de fin del subtitulo
		act->tiempos[i] = tiempo[j];
	return (l);
}

lista reducirTiemposSub(lista l, long milis) {
	lista act;
	long tiempo[4];
	int i, j;
	act = l;
	while(act != NULL) {
		if((act->endMilis - act->startMilis) > milis) {
			while((act->endMilis - act->startMilis) > milis)
				act->endMilis--;
			convertirMillisAFormatoSubRip(act->endMilis, tiempo); // El unico que modifico es endMilis entonces solo convierto ese campo a formato SubRip
			for(i = 7, j = 3; i > 3; i--, j--) // Actualizo el tiempo de fin del subtitulo
				act->tiempos[i] = tiempo[j];
		}
		act = act->sig;
	}
	return (l);
}

void validarSub(lista act) {
	lista ant;
	int i, tamSub;
	if(act->indice != 1)
		printf("Los numeros de indice no arrancan en 1 \n");
	while(act != NULL) {
		if((act->endMilis - act->startMilis) < 1000) // 1000 milisegundos = 1 segundo
			printf("El subtitulo %ld dura menos de 1 segundo \n", act->indice);
		if((act->endMilis - act->startMilis) > 7000) // 7000 milisegundos = 7 segundos
			printf("El subtitulo %ld dura mas de 7 segundos \n", act->indice);
		for(i = 0; act->sub[i] != NULL && strcmp(act->sub[i], "\n") != 0 && !(act->sub[i][0] == '\r' && act->sub[i][1] == '\n'); i++) { // Mientras no llege a salto de linea (sea en linux o en windows) se hace el procesamiento correspondiente
			if(strlen(act->sub[i]) > 36)
				printf("La linea %d del subtitulo %ld es demasiado larga, supera los 36 caracteres \n", (i+1), act->indice); // i + 1 porque los indices del arreglo arrancan de 0
		}
		tamSub = 0;
		for(i = 0; act->sub[i] != NULL && strcmp(act->sub[i], "\n") != 0 && !(act->sub[i][0] == '\r' && act->sub[i][1] == '\n'); i++) // Cuento el total de caracteres del subtitulo. Mientras no llege a salto de linea (sea en linux o en windows) se hace el procesamiento correspondiente
			tamSub += (strlen(act->sub[i]) - 1); // No cuento el salto de linea de ninguna de las lineas
		if((tamSub / (act->endMilis - act->startMilis)) > 25) // Calcula los cps y verifica si son mas de 25
			printf("El subtitulo %ld tiene demasiados caracteres por segundo \n", act->indice);
		if(i > 2)
			printf("El subtitulo %ld tiene mas de 2 lineas \n", act->indice);
		ant = act;
		act = act->sig;
		if(act != NULL) {
			if(ant->indice != (act->indice - 1)) // Si el indice actual no es el siguiente consecutivo del indice anterior
				printf("Los numeros de indice dentro del archivo no son numeros consecutivos ordenados. Informacion del Error: el indice %ld no es el consecutivo de %ld \n", ant->indice, act->indice);
			if(ant->endMilis >= act->startMilis)
				printf("El subtitulo %ld comienza antes de que termine el subtitulo %ld. Estan solapados \n", act->indice, ant->indice);
			if((act->startMilis - ant->endMilis) < 75) // Si hay menos de 75 milisegundos entre el final del subtitulo i y el principio del i + 1.
				printf("Hay menos de 75 milisegundos entre el final del subtitulo %ld y el principio del subtitulo %ld \n", ant->indice, act->indice);
		}
	}
}
