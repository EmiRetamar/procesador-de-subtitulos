#include "verificarParametros.h"

int verificarParametros(int argc, char** argv, int* oOk, int* posFileIn, int* posFileOut, int* webVTT) {
	int i;
	char* omega = "-Ω";
	for(i = 1; i < argc; i++) { // Recorre todos los parametros al programa y verifica que sean correctos, cada i va a ser un string distinto
		if(argv[i][0] == '-' && (strlen(argv[i]) == 2 || strcmp(omega, argv[i]) == 0)) { // Para que el parametro pueda llegar a ser valido tiene que comenzar con '-' y tener longitud 2 (En esta condicion SOLO se verificaran parametros con formato "-x" donde x puede ser cualquier caracter)
			switch (argv[i][1]) {
				case 'f':
					if(*posFileIn == 0)
						*posFileIn = ++i; // Para saber si se ingreso el parametro -f solo basta con preguntar si posFileIn != 0, guardo en posFileIn la posicion del nombre del archivo de entrada
					else {
						printf("Sale con codigo 1. Se recibio mas de un -f o -o \n");
						return (1);
					}
					break;
				case 'o':
					if(*posFileOut == 0)
						*posFileOut = ++i; // Luego para saber si aparecio el parametro -o solo basta con preguntar si posFileOut != 0, guardo en posFileOut la posicion del nombre del archivo de salida
					else {
						printf("Sale con codigo 1. Se recibio mas de un -f o -o \n");
						return (1);
					}
					break;
				case 'd':
					i++;
					if(isNum(argv[i]) == 0) { // La funcion devuelve 0 en caso de que el parametro sea erroneo y devuelve 1 en caso de que sea correcto
						printf("Sale con codigo 3. Los parametros son invalidos \n");
						return (3);
					}
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 's':
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 'b':
					i++;
					if(isNum(argv[i]) == 0) { // La funcion devuelve 0 en caso de que el parametro sea erroneo y devuelve 1 en caso de que sea correcto
						printf("Sale con codigo 3. Los parametros son invalidos \n");
						return (3);
					}
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 'i':
					i++;
					if(isNum(argv[i++]) == 0 || isNum(argv[i++]) == 0) { // La funcion devuelve 0 en caso de que el parametro sea erroneo y devuelve 1 en caso de que sea correcto
						printf("Sale con codigo 3. Los parametros son invalidos \n"); // Solo en caso de que ambos parametros sean correctos la expresion no retorna error, si ambos o uno de los dos es incorrecto se retorna el error
						return (3);
					}
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 'm':
					i++;
					if(isNum(argv[i]) == 0) { // La funcion devuelve 0 en caso de que el parametro sea erroneo y devuelve 1 en caso de que sea correcto
						printf("Sale con codigo 3. Los parametros son invalidos \n");
						return (3);
					}
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 'c':
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 'M':
					i++;
					if(isNum(argv[i]) == 0) { // La funcion devuelve 0 en caso de que el parametro sea erroneo y devuelve 1 en caso de que sea correcto
						printf("Sale con codigo 3. Los parametros son invalidos \n");
						return (3);
					}
					if(*oOk == 0) // Para saber si es necesario que aparezca -o solo hay que preguntar si oOk != 0
						*oOk = 1;
					break;
				case 'v':
					break;
				default:
					if(strcmp(omega, argv[i]) == 0)
						*webVTT = 1;
					else {
						printf("Sale con codigo 3. Los parametros son invalidos \n");
						return (3);
					}
			}
		}
		else {
			printf("Sale con codigo 3. Los parametros son invalidos \n");
			return (3);
		}
	}
	if(*posFileIn == 0) { // Si no se recibe el parametro -f sale retornando 2
		printf("Sale con codigo 2. Faltan los parametros obligatorios \n");
		return (2);
	}
	else { // Si se recibe -f
		if((*posFileOut != 0 && *oOk == 0) || (*posFileOut == 0 && *oOk != 0)) { // Como se recibio el parametro -f solo en caso de que se reciba o no se reciba el parametro -o y algun parametro de modificacion el programa debera continuar, en caso de que uno se reciba y el otro no terminara retornando un error
			printf("Sale con codigo 2. Faltan los parametros obligatorios \n");
			return (2);
		}
	}
	return (0); // La funcion retorna un valor distinto de 0 si los parametros son validos y retorna 0 en caso de que sean invalidos
}

int isNum(char* param) {
	int i;
	if(param[0] == '-') {
		for(i = 1; i < strlen(param); i++) {
			if(!(param[i] >= '0' && param[i] <= '9'))
				return (0);
		}
	}
	else {
		for(i = 0; i < strlen(param); i++) {
			if(!(param[i] >= '0' && param[i] <= '9'))
				return (0);
		}
	}
	return (1);
}
