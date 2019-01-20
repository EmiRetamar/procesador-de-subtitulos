long* convertirMillisAFormatoSubRip(long milis, long* tiempo) {
	int i;
	for(i = 0; i < 4; i++) {
		switch (i) {
			case 0:
				tiempo[i] = (((milis / 1000) / 60) / 60); // Convierto los milis a horas y lo asigno en la posicion de 0
				break;
			case 1:
				tiempo[i] = ((milis / 1000) / 60) - (tiempo[i-1] * 60);  // Convierto los milis a minutos, le resto las horas convertidas en minutos a los minutos obtenidos en la conversion de milis y asigno el resultado en la posicion 1
				break;
			case 2:
				tiempo[i] = (milis / 1000) - (tiempo[i-1] * 60) - (tiempo[i-2] * 60 * 60); // Convierto los milis a segundos, le resto los minutos convertidos en segundos, le resto las horas convertidas en segundos y asigno el resultado en la posicion 2
				break;
			case 3:
				tiempo[i] = milis - (tiempo[i-1] * 1000) - (tiempo[i-2] * 60 * 1000) - (tiempo[i-3] * 60 * 60 * 1000); // Convierto los segundos, los minutos y las horas que tenia anteriormente a milisegundos y se lo resto a los milisegundos totales
				break;
		}
	}
	return (tiempo);
}
