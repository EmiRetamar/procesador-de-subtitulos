#include "ayuda.h"

void ayuda() {
	printf("Pasaje de parametros incorrecto \n"); 
	printf("Los parametros validos son: \n");
	printf("-d tiempo ← desplaza todos los subtitulos tiempo milisegundos (tiempo puede ser negativo). ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-s ← separa subtitulos que esten solapados. ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-f filein ← file es el archivo a procesar. ES OBLIGATORIO Y NO SE PUEDE REPETIR. \n");
	printf("-o fileout ← fileout es el archivo donde se guardaran los cambios. SI SE INGRESAN PARAMETROS QUE MODIFIQUEN EL ARCHIVO, ES OBLIGATORIO Y NO SE PUEDE REPETIR. \n");
	printf("-b index ← borra el subtitulo numero index. ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-i startmilis endmillis texto ← inserta el subtitulo texto en startmilis con duracion hasta endmillis, corrige todos los indices de los subtitulos siguientes. ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-m millis ← establecer duracion minima de los subtitulos, cualquier subtitulo que dure menos se extendera hasta ocupar millis o hasta que este a 75 milisegundos del subtitulo siguiente (lo que suceda primero). ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-c ← aumenta la duracion de los subtitulos que tengan demasiados caracteres por segundo hasta que tengan 25 cps o menos o hasta que este a 75 milisegundos del subtitulo siguiente (lo que suceda primero). ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-M millis ← reduce el tiempo de los subtitulos que duren mas de millis milisegundos. ES OPCIONAL Y PUEDE REPETIRSE \n");
	printf("-v ← valida el subtitulo buscando errores. ES OPCIONAL Y PUEDE REPETIRSE \n");
}
	
