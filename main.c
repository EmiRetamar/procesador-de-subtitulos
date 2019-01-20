#include "main.h"
#include "lista.h"

int main(int argc, char** argv) {
	FILE *archEntrada, *archSalida;
	lista l = NULL;
	int i, oOk = 0, posFileIn = 0, posFileOut = 0, codError, webVTT = 0; // oOk para saber si se ingreso el archivo de entrada y el de salida. posFileIn y posFileOut para saber en que numero de parametro se encontro el archivo de entrada y de salida, webVTT es para saber si el archivo de entrada es un webVTT en vez de un subRip
	if((codError = verificarParametros(argc, argv, &oOk, &posFileIn, &posFileOut, &webVTT)) == 0) { // La funcion devuelve 0 en caso de que los parametros sean validos. 0 es true (ya que los demas numeros se usan para el salir informando algun tipo de error)
		if(formatoArchEntradaEsValido(argv[posFileIn], webVTT) == 0) { // La funcion retorna 0 en caso de que el formato del archivo de entrada sea invalido, 0 es false en este caso
				printf("Sale con codigo 5. El formato del archivo recibido es incorrecto. Si el programa se ejecuta con el parametro -Ω debe recibir como entrada un .vtt y si no recibe dicho parametro debe recibir un .srt \n");
				return (5); // Si el formato del archivo recibido es invalido, el programa termina con codigo de salida 5 (agregue un nuevo codigo de salida a los que ya estaban)
		}
		if((archEntrada = fopen(argv[posFileIn], "r")) != NULL) {
			if(posFileOut != 0 && oOk != 0) { // Pregunta si recibio el parametro -o y si se recibieron parametros que modifiquen el archivo, porque el archivo de salida solo debe abrirse en caso de que se reciban parametros que modifiquen el archivo (Se verifica en la funcion que parsea los parametros que -o no se repita)
				if((archSalida = fopen(argv[posFileOut], "w")) == NULL) { // Si no se puede abrir el archivo de salida, devuelve el error
					printf("Sale con codigo 4. Se produjo un error, no se pudo abrir el archivo %s \n", argv[posFileOut]);
					return (4);
				}
			}
			l = copiarArch(archEntrada, l, webVTT); // Copio todo el archivo a una estructura de datos de tipo lista
			fclose(archEntrada);
			if(webVTT == 1) { // webVTT es 1 si se recibio el -Ω entonces se hace el procesamiento correspondiente para el formato vtt
				verificarEtiquetasWebVTT(l);
				convertirVTTaSubRip(l); // Asigna los indices para terminar de convertir el formato WebVTT a SubRip
			}
			for(i = 1; i < argc; i++) {
				switch(argv[i][1]) {
					case 'd':
						i++;
						desplazarSub(l, atol(argv[i]));
						break;
					case 's':
						separarSubSolapados(l);
						break;
					case 'b':
						i++;
						eliminarSub(l, atol(argv[i]));
						break;
					case 'i':
						insertarSub(l, atol(argv[i+1]), atol(argv[i+2]), argv[i+3]);
						i += 3;
						break;
					case 'm':
						i++;
						duracionMinSub(l, atol(argv[i]));
						break;
					case 'c':
						aumentarDuracionSub(l);
						break;
					case 'M':
						i++;
						reducirTiemposSub(l, atol(argv[i]));
						break;
					case 'v':
						validarSub(l);
				}
			} // Fin del for
			if(posFileOut != 0 && oOk != 0) { // Pregunto otra vez para saber si se abrio el archivo de modificacion
				escribirArch(archSalida, l);
				fclose(archSalida);					
			}
		}
		else {
			printf("Sale con codigo 4. Se produjo un error, no se pudo abrir el archivo %s \n", argv[posFileIn]);
			return (4);
		}
	}
	else {
		ayuda();
		return (codError);
	}
	liberarLista(l); // liberarLista libera toda la memoria alocada para la lista y devuelve NULL
	return (0);
}
