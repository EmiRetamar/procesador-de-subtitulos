#include "leerArchivo.h"
#include "lista.h"
#include "liberarMemoria.h"

lista copiarArch(FILE* archEntrada, lista l, int webVTT) {
	struct nodo datos;
	crearLista(&l);
	while(fgetc(archEntrada) && !feof(archEntrada)) { // Leo primero para saber si llegue a EOF, ya que para que feof sea true se debe realizar una lectura adicional cuando estamos en EOF
		fseek(archEntrada, -1, SEEK_CUR); // Vuelvo una posicion en el archivo por la lectura anterior
		if(webVTT == 0) // Si es igual a 0 interpreta el archivo de entrada como SubRip
			asignarValoresSubRip(archEntrada, &datos, webVTT); // Asigna los datos que representaran un nodo de la lista
		else // Si es igual a 1 interpreta el archivo de entrada como webVTT
			asignarValoresWebVTT(archEntrada, &datos, webVTT); // Asigna los datos que representaran un nodo de la lista
		agregarALista(&l, datos); // Agrega un nodo a la lista con sus valores correspondientes
		liberarMemoria(&(datos.sub)); // Libera lo alocado en memoria dinamica del array de punteros
	}
	return (l);
}

void asignarValoresSubRip(FILE* archEntrada, struct nodo* datos, int webVTT) {
	char buffer[tam];
	int i = 0;
	fgets(buffer, tam, archEntrada); // Toma la primera linea del subtitulo
	asignarIndice(&(datos->indice), buffer);
	fgets(buffer, tam, archEntrada); // Toma la segunda linea del subtitulo
	asignarTiempos(datos, buffer);
	datos->startMilis = calcularTiemposEnMilis(datos->tiempos, &i); // La funcion devuelve el tiempo total inicial en formato de milisegundos (convierte horas, minutos y segundos a milisegundos y los totaliza a los milisegundos que ya se tenian)
	datos->endMilis = calcularTiemposEnMilis(datos->tiempos, &i); // La funcion devuelve el tiempo total final en formato de milisegundos (convierte horas, minutos y segundos a milisegundos y los totaliza a los milisegundos que ya se tenian)
	asignarSubtitulo(archEntrada, datos, webVTT);
}

void asignarValoresWebVTT(FILE* archEntrada, struct nodo* datos, int webVTT) {
	char buffer[tam];
	int i = 0, hora = 0; // Ya que en el formato vtt la hora puede no venir, "hora" va a indicar si se recibe el tiempo con la hora incluida o no
	fgets(buffer, tam, archEntrada);
	while(esTiempo(buffer, &hora) == 0) // Mientras no sea el tiempo la linea leida, se seguira leyendo hasta que se lo encuentre y se ignorara todo lo demas
		fgets(buffer, tam, archEntrada); // En caso de que exista indice, se lee de nuevo y se toma el tiempo
	asignarTiempos(datos, buffer);
	if(hora == 0) // Si hora vale 0 significa que no vino la hora en el tiempo
		agregarHora(datos->tiempos);
	datos->startMilis = calcularTiemposEnMilis(datos->tiempos, &i); // La funcion devuelve el tiempo total inicial en formato de milisegundos (convierte horas, minutos y segundos a milisegundos y los totaliza a los milisegundos que ya se tenian)
	datos->endMilis = calcularTiemposEnMilis(datos->tiempos, &i); // La funcion devuelve el tiempo total final en formato de milisegundos (convierte horas, minutos y segundos a milisegundos y los totaliza a los milisegundos que ya se tenian)
	asignarSubtitulo(archEntrada, datos, webVTT);
}

int esTiempo(char* linea, int* hora) { // La pelicula mas larga dura 87 horas, entonces con eso puedo saber que si no me viene la hora como maximo voy a tener 4 digitos en los minutos
	int i = 0;
	int contTiemposSubIni = 0; // mmmm:ss.mmm --> mmmm:ss:mmm
	int contTiemposSubFinal = 0; // hh:mm:ss.mmm --> hh:mm:ss.mmm
	if(strlen(linea) >= 24 && strlen(linea) <= 30) {
		while(linea[i] != ' ') { // Recorro todo el tiempo inicial. En la posicion 12 deberia terminar el tiempo inicial y deberia haber un espacio en blanco
			while(linea[i] >= '0' && linea[i] <= '9') // Mientras lo que haya en la posicion actual sea un numero
				i++;
			contTiemposSubIni++;
			if(linea[i] != ':' && linea[i] != '.' && linea[i] != ' ') // Si lo que hay en la posicion actual no es un ':', un '.' o un espacio en blanco devuelvo falso
				return (0);
			if(linea[i] == ' ' && !(i >= 9 && i <= 12)) // Con la hora cuando se llegue al espacio en blanco "i" deberia estar en 12, y sin la hora deberia estar con un valor entre 9 y 11
				return (0);
			if(linea[i] != ' ')
				i++;
		} // Hasta aca proceso el tiempo inicial
		i++;
		if(linea[i] != '-')
			return (0);
		i++;
		if(linea[i] != '-')
			return (0);
		i++;
		if(linea[i] != '>')
			return (0);
		i++;
		if(linea[i] != ' ')
			return (0);
		i++;
		while(linea[i] != '\0') { // Recorro todo el tiempo final, es hasta 29 porque el arreglo empieza de 0
			while(linea[i] >= '0' && linea[i] <= '9') // Mientras lo que haya en la posicion actual sea un numero
				i++;
			contTiemposSubFinal++;
			if(linea[i] != ':' && linea[i] != '.' && linea[i] != '\n') // Si lo que hay en la posicion actual no es un ':', un '.' o un fin de string devuelvo falso
				return (0);
			if(linea[i] == '\n' && !(i >= 23 && i <= 29))
				return (0);
			i++;
		}
		if(contTiemposSubIni == 4 && contTiemposSubFinal == 4) // Si viene la hora, la variable hora se cambia a true
			*hora = 1;
	}
	else
		return (0);
	return (1);
}

void agregarHora(long* tiemposSub) {
	int tiemposAux[8];
	int i;
	for(i = 0; i < 8; i++) {
		switch (i) {
			case 0:
				tiemposAux[i] = tiemposSub[i] / 60;
				break;
			case 1:
				tiemposAux[i] = (tiemposSub[i-1]) - (tiemposAux[i-1] * 60);
				break;
			case 2:
				tiemposAux[i] = tiemposSub[i-1];
				break;
			case 3:
				tiemposAux[i] = tiemposSub[i-1];
				break;
			case 4:
				tiemposAux[i] = tiemposSub[i-1] / 60;
				break;
			case 5: 
				tiemposAux[i] = (tiemposSub[i-2]) - (tiemposAux[i-1] * 60);
				break;
			case 6:
				tiemposAux[i] = tiemposSub[i-2];
				break;
			case 7:
				tiemposAux[i] = tiemposSub[i-2];
				break;
		}
	}
	for(i = 0; i < 8; i++)
		tiemposSub[i] = tiemposAux[i];
}

void asignarIndice(long* indice, char* ptrBuffer) {
	*indice = atol(ptrBuffer);
}

void asignarTiempos(struct nodo* datos, char* ptrBuffer) {
	int i = 0;
	while(*ptrBuffer != '\0') { // Se supone que i no se va a pasar del limite del vector porque en esta linea del archivo hay 8 valores exactamente
		if((*ptrBuffer >= '0') && (*ptrBuffer <= '9')) // si ptrBuffer apunta a un numero, los convierto y lo asigno al vector de tiempos
			datos->tiempos[i++] = strtol(ptrBuffer, &ptrBuffer, base);
		else // Sino, hago que ptrBuffer apunte a la direccion de memoria siguiente
			ptrBuffer++;
	}
}

long calcularTiemposEnMilis(long* tiempos, int* i) {
	int j;
	long vecAux[4], acum = 0;
	for(j = 0; j <= 3; j++) {
		switch (j) {
			case 0:
				vecAux[j] = tiempos[*i] * 60 *60 *1000; // Guarda las horas convertidas a milisegundos
				break;
			case 1:
				vecAux[j] = tiempos[*i] *60 *1000; // Guarda los minutos convertidos a milisegundos
				break;
			case 2:
				vecAux[j] = tiempos[*i] *1000; // Guarda los segundos convertidos a milisegundos
				break;
			case 3:
				vecAux[j] = tiempos[*i]; // Guarda los milisegundos
				break;
		}
		(*i)++;
		acum = acum + vecAux[j]; // Voy acumulando las conversiones a milisegundos
	}
	return (acum);
}

void asignarSubtitulo(FILE* archEntrada, struct nodo* datos, int webVTT) {
	size_t tamLinea;
	int i = 0;
	datos->sub = (char**) malloc(sizeof(char*));
	datos->sub[i] = NULL;
	while((tamLinea = getline(&(datos->sub[i]), &tamLinea, archEntrada)) != 1 && tamLinea != -1 && !(tamLinea == 2 && datos->sub[i][0] == '\r' && datos->sub[i][1] == '\n')) { // Mientras no se lea salto de linea y no llegue a EOF, el salto de linea puede tener 1 o 2 caracteres depende del sistema operativo que se uso para crear el archivo
		i++;
		datos->sub = (char**) realloc(datos->sub, sizeof(char*) * (i+1));
		datos->sub[i] = NULL;
	}
	if(tamLinea == 1 || tamLinea == 2) { // Significa que salio porque encontro un salto de linea
		i++;
		datos->sub = (char**) realloc(datos->sub, sizeof(char*) * (i+1)); 
		datos->sub[i] = NULL; // Aloco memoria extra y dejo el ultimo puntero en NULL para saber donde termina mi arreglo de punteros en caso de que necesite recorrerlo
	}
	else { // Significa que salio porque encontro fin de archivo
		if(webVTT == 1) { // Si el archivo es vtt hay que agregar una linea en blanco en el subtitulo final, ya que el formato srt tiene el espacio en blanco al final en vez de al principio
			datos->sub[i][0] = '\n';
			datos->sub[i][1] = '\0';
			i++;
			datos->sub = (char**) realloc(datos->sub, sizeof(char*) * (i+1));
		}
		datos->sub[i] = NULL;
	}
}
