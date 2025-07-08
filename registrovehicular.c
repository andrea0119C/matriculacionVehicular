//Librerias estandar
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>



//Librería propia
#include "registroVehiculos.h"

//Función para mayúsculas 
void strToLower(char *str){
	for(int i=0; str[i]; i++){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] += 'a' - 'A';
		}
	}
}
	
//Función auxiliar para validar cédula
int validarCedula(const char *ced){
	if(strlen(ced) != 10)
		return 0;
	for(int i = 0; i < 10; i++){
		if(!isdigit(ced[i]))
			return 0;
	}
	return 1;
}

//Función auxiliar para validar el año	
int validarAnio(int anio) {
	return (anio >= 2000 && anio <= 2025);
}

//Función auxiliar para validar tipo
int validarTipo(int tipo){
	return( tipo == 0 || tipo == 1 || tipo == 2 || tipo == 3);
}

//Función auxiliar para mostrar en texto el tipo
const char* tipoTexto(int tipo){
	switch(tipo){
		case 0: return "Moto";
		case 1: return "Liviano";
		case 2: return "Mediano";
	    case 3: return "Pesado";
		default: return "Desconocido";
	}
}

//Función auxiliar para validar Subtipo dependiendo el tipo
int validarSubtipo(int tipo, int subtipo){
	switch(tipo){
	case 0: return(subtipo >= 0 && subtipo <=1);
	case 1: return(subtipo >= 0 && subtipo <=1);
	case 2: return(subtipo >= 0 && subtipo <=1);
	case 3: return(subtipo >= 0 && subtipo <=1);
	default: return 0;
	}
}

//Mostrar cilindraje
void mostrarSubtipoYCilindraje(int tipo, int subtipo){
int cilindraje [4][2] ={
	{100, 200},
	{1200, 2000},
	{2500, 3000},
	{4000, 5000,}
};
printf("Subtipo: %d \nCilindraje: %dcc\n", subtipo, cilindraje[tipo][subtipo]);
}

//Función auxiliar para validar descuento
int validarDescuento(int opcion){
	return ( opcion == 0 || opcion == 1);
}

//Función auxiliar para validar retención
int validarRetencion(int opcion){
	return ( opcion == 0 || opcion == 1);
}

//Función auxiliar para validar multas
int validarMultas(int opcion){
	return ( opcion == 0 || opcion == 1 || opcion == 2 || opcion == 3);
}

int leerEnteroLimpio(const char *entrada, int *valor) {
	char temp;
	if (sscanf(entrada, "%d %c", valor, &temp) != 1)
		return 0;
	
	char limpio[10];
	strncpy(limpio, entrada, sizeof(limpio));
	limpio[strcspn(limpio, "\n")] = '\0';
	
	for (int i = 0; limpio[i] != '\0'; i++) {
		if (!isdigit(limpio[i]))
			return 0;
	}
	
	if (strlen(limpio) > 1 && limpio[0] == '0')
		return 0;
	
	return 1;
}


//Función para registrar los vehículos
void registroVehiculo(vehiculo *veh, vehiculo *vehiculos, int total){
	char buffer[100];
	int valida=0;
	int tipoValido;
	char entrada[10];
	while(!valida){
		
	 
	printf("Ingrese la placa del vehículo: \n");
	//Ingrese la placa del vehículo
	scanf("%s", veh->placa);
	fflush(stdin);
	
	if(strlen(veh->placa)==7){
		int letras = 1, numeros=1;
		
		for(int i=0; i < 3; i++){
			if(!isalpha(veh->placa[i])){
				letras=0;
				break;
			}
		}
		for (int i=3; i<7; i++){
			if(!isdigit(veh->placa[i])){
				numeros =0;
				break;
			}
		}
		// Verificar si ya existe la placa en vehiculos
		int placaRepetida = 0;
		for (int i = 0; i < total; i++) {
			if (strcasecmp(vehiculos[i].placa, veh->placa) == 0) {
				placaRepetida = 1;
				break;
			}
		}
		
		if (letras && numeros && !placaRepetida) {
			valida = 1;
		} else if (placaRepetida) {
			printf("Ya existe un vehículo registrado con esa placa.\n");
		} else {
			printf("Placa inválida. Intente nuevamente.\n");
		}
	} else {
		printf("La placa debe tener exactamente 7 caracteres.\n");
	}
	}
	
		
		//Ingrese el número de cédula del usuario
	do {
		printf("Ingrese la cédula del usuario (10 dígitos): \n");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0'; // Quita salto de línea
		
		if (validarCedula(buffer)) {
			strncpy(veh->cedula, buffer, sizeof(veh->cedula));
			break;
		} else {
			printf("Cédula inválida. Debe tener exactamente 10 dígitos numéricos.\n");
		}
	} while (1);
	
		
	//Ingrese el año del vehículo
	do {
		printf("Ingrese el año del vehículo: \n");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		// Verificamos que sea un número
		int esNumero = 1;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!isdigit(buffer[i])) {
				esNumero = 0;
				break;
			}
		}
		
		if (esNumero) {
			int anioIngresado = atoi(buffer);
			if (validarAnio(anioIngresado)) {
				veh->anio = anioIngresado;
				break;
			}
		}
		printf("Año inválido. Debe estar entre 2000 y 2025.\n");
	} while (1);
		
	//Ingrese el tipo de vehículo
	do {
		printf("Ingrese el tipo de vehículo \n 0.-Moto \n 1.-Liviano \n 2.-Mediano \n 3.-Pesado: \n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->tipo);
		
		
		
		if (tipoValido !=1 || !validarTipo (veh->tipo)) {
			printf("Tipo inválido. Solo se permite: 0, 1, 2 o 3.\n");
		}
	} while (tipoValido !=1 || !validarTipo (veh->tipo));
	limpiarPantalla();
 
	//Ingrese el subtipo
	int subtipoIngresado;
	do{
		printf("Ingrese el Cilindraje de vehículo para el tipo %s:\n", tipoTexto(veh->tipo));
		switch(veh->tipo){
		case 0:
			printf(" 0.- 100cc\n 1.-200cc\n");
			break;
		case 1:
			printf(" 0.- 1200cc\n 1.-2000cc\n");
			break;
		case 2:
			printf(" 0.- 2500cc\n 1.- 3000cc\n");
			break;
		case 3:
			printf(" 0.- 4000cc\n 1.-5000cc\n");
			break;
		}
	 fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &subtipoIngresado);
		if (tipoValido !=1 || !validarSubtipo (veh->tipo, subtipoIngresado)) {
			printf("Opción inválida. Intente de nuevo.Ingresar 0 o 1\n");
		}
		} while(tipoValido !=1 || !validarSubtipo(veh->tipo, subtipoIngresado));
	veh->subtipo = subtipoIngresado;
	
	int cilindraje[4][2] ={
		{100, 200},
	    {1200, 2000},
		{2500, 3000},
		{4000, 5000},
	};
	veh->cilindraje= cilindraje [veh->tipo][veh->subtipo];
	limpiarPantalla();
	do{
	    printf("Es ecológico: \n Ingrese:\n 0.- Si es escológico \n 1.- No es escológico:\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->esEcologico);
	    
	    if (tipoValido !=1 || !validarDescuento (veh->esEcologico)) {
		    printf("Opción inválido. Solo se permite:Ingresar 0 o 1.\n");
	}  
	} while (tipoValido !=1 || !validarDescuento (veh->esEcologico));
	limpiarPantalla();
	
	do{
	    printf("Realizo el pago antes de tiempo: \n Ingrese: \n 0.-Si es correcto \n 1.- No es correcto: \n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->pagoConAnticipo);
		if (tipoValido !=1 || !validarDescuento (veh->pagoConAnticipo)) {
			printf("Opción inválido. Solo se permite:Ingresar 0 o 1.\n");
		}  
	} while (tipoValido !=1 || !validarDescuento (veh->pagoConAnticipo));
	limpiarPantalla();
	
	do{
	    printf("Paso a la primera revisión técnica: \n Ingrese: \n 0.-Si es correcto \n 1.-No es correcto:\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->pasoRevisionTecnica);
		if (tipoValido !=1 || !validarRetencion (veh->pasoRevisionTecnica)) {
			printf("Opción inválido. Solo se permite:Ingresar 0 o 1.\n");
		}  
	} while (tipoValido !=1 || !validarRetencion (veh->pasoRevisionTecnica));
	limpiarPantalla();
	
	do{
	    printf("Pago a tiempo: \n Ingrese: \n 0.- Si es correcto \n 1.- No es correcto:\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->pagoATiempo);
		if (tipoValido !=1 || !validarRetencion (veh->pagoATiempo)) {
			printf("Opción inválido. Solo se permite:Ingresar 0 o 1.\n");
		}  
	} while (tipoValido !=1 || !validarRetencion (veh->pagoATiempo));
	limpiarPantalla();
	
	// MULTA POR ESTADO ETÍLICO
	do {
		printf("Multa por manejar en estado etílico:\n");
		printf("0.- Sin multa\n1.- Leve \n2.- Moderada \n3.- Grave\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorEstadoEtilico);
		if (tipoValido != 1 || !validarMultas(veh->multaPorEstadoEtilico)) {
			printf("Opción inválida. Solo se permite: 0 a 3.\n");
		}  
	} while (tipoValido != 1 || !validarMultas(veh->multaPorEstadoEtilico));
	limpiarPantalla();
	
	// MULTA POR NO USAR CINTURÓN
	do {
		printf("Multa por no usar cinturón de seguridad:\n");
		printf("0.- Sin multa\n1.- Un cinturón\n2.- Dos o tres cinturones\n3.- Cuatro o cinco cinturones\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorSinCinturon);
		if (tipoValido != 1 || !validarMultas(veh->multaPorSinCinturon)) {
			printf("Opción inválida. Solo se permite: 0 a 3.\n");
		}  
	} while (tipoValido != 1 || !validarMultas(veh->multaPorSinCinturon));
	limpiarPantalla();
	
	// MULTA POR EXCESO DE VELOCIDAD
	do {
		printf("Multa por sobrepasar el límite de velocidad:\n");
		printf("0.- Sin multa\n1.- Leve \n2.- Moderada\n3.- Grave\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorSobrepasarLimiteDeVelocidad);
		if (tipoValido != 1 || !validarMultas(veh->multaPorSobrepasarLimiteDeVelocidad)) {
			printf("Opción inválida. Solo se permite: 0 a 3.\n");
		}  
	} while (tipoValido != 1 || !validarMultas(veh->multaPorSobrepasarLimiteDeVelocidad));
	limpiarPantalla();
	
	veh->avaluo = calcularAvaluo(*veh);
   }
//Función principal para calcular Avaluo
float calcularAvaluo(vehiculo v){
	float base=0.0f;
	float depreciacion_anual = 0.0f;
	
	if(v.tipo == 0){
		base=2000;
		depreciacion_anual=0.08f;
	}else if(v.tipo == 1){
		base=15000;
		depreciacion_anual=0.10f;
	}else if (v.tipo == 2){
		base=25000;
		depreciacion_anual=0.12f;
	}else if (v.tipo == 3){
		base=40000;
		depreciacion_anual=0.15f;
	}else {
		base=10000;
		depreciacion_anual=0.10f;
	}
	
	if (v.cilindraje > 1000){
		base+= (v.cilindraje -1000)*10;
	}
	
	int antiguedad=2025-v.anio;
	float depreciacion=antiguedad * depreciacion_anual;
	float factor=1.0f - depreciacion;
	
	if(factor<0.3f){
		factor=0.3f;
	}
	return base*factor;
}
	
	// Función para obtener la fecha actual
	const char* obtenerFechaActual() {
		static char fecha[11]; // Formato: DD-MM-AAAA
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		sprintf(fecha, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		return fecha;
	}
	// Función auxiliar para validar entradas
	int leerPuntaje(const char *mensaje, int min, int max) {
		int valor;
		do {
			printf("%s (%d-%d): ", mensaje, min, max);
			if (scanf("%d", &valor) != 1) {
				printf("¡Error! Ingrese un número válido.\n");
				while (getchar() != '\n');
				continue;
			}
			if (valor < min || valor > max) {
				printf("¡Error! El valor debe estar entre %d y %d.\n", min, max);
			}
		} while (valor < min || valor > max);
		return valor;
	}
	
	// Función para evaluar las revisiones técnicas
	int evaluarRevisionTecnica(vehiculo *v) {
		
		// Validación para revisiones anteriores
		printf("¿Pasó la PRIMERA revisión técnica? (1 = sí, 0 = no): ");
		int pasada1;
		do {
			if (scanf("%d", &pasada1) != 1) {
				printf("Entrada no válida. Ingrese 1 (sí) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (pasada1 != 0 && pasada1 != 1);
		
		if (pasada1) {
			v->revision1 = leerPuntaje("Ingrese el puntaje obtenido", 0, 100);
		} else {
			printf("\nDebe realizar la revisión 1 antes de continuar.\n");
			printf("Por favor regrese cuando haya completado la revisión técnica 1.\n");
			return 0; // <-- retorna al menú
		}
		
		printf("¿Pasó la SEGUNDA revisión técnica? (1 = sí, 0 = no): ");
		int pasada2;
		do {
			if (scanf("%d", &pasada2) != 1) {
				printf("Entrada no válida. Ingrese 1 (sí) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (pasada2 != 0 && pasada2 != 1);
		
		if (pasada2) {
			v->revision2 = leerPuntaje("Ingrese el puntaje obtenido", 0, 100);
		} else {
			printf("\nDebe realizar la revisión 2 antes de continuar.\n");
			printf("Por favor regrese cuando haya completado la revisión técnica 2.\n");
			return 0;
		}
		
		// Evaluación técnica actual
		int puntajes[8];
		const char *categorias[8] = {
			"Frenos",
				"Luces",
				"Emisiones",
				"Neumáticos",
				"Espejos y parabrisas",
				"Cinturones",
				"Bocina y limpiaparabrisas",
				"Documentación al día"
		};
		int maxPuntajes[8] = {25, 15, 15, 10, 10, 10, 5, 10};
		
		printf("\nEvaluación técnica actual:\n");
		int puntajeTotal = 0;
		for (int i = 0; i < 8; i++) {
			puntajes[i] = leerPuntaje(categorias[i], 0, maxPuntajes[i]);
			puntajeTotal += puntajes[i];
		}
		v->revisionActual = puntajeTotal;
		printf("\nRevisión técnica %s.\n", (puntajeTotal >= 70) ? "APROBADA" : "REPROBADA");
		
		// Preguntar al final si desea comprobante
		int imprimir;
		printf("\n¿Desea imprimir el comprobante? (1 = Sí, 0 = No): ");
		do {
			if (scanf("%d", &imprimir) != 1 || (imprimir != 0 && imprimir != 1)) {
				printf("Entrada inválida. Ingrese 1 (sí) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (imprimir != 0 && imprimir != 1);
		
		if (!imprimir) {
			printf("No se generará el comprobante.\n");
			return (puntajeTotal >= 70);
		}
		// Calcular matrícula antes de imprimir
		v->matricula = calcularValorMatricula(*v);
		
		// Imprimir comprobante
		FILE *archivo = fopen("resultado_revision.txt", "w");
		if (!archivo) {
			printf("No se pudo crear el archivo de resultados.\n");
			return (puntajeTotal >= 70);
		}
		
		// Generar comprobante con formato
		fprintf(archivo, "============================================\n");
		fprintf(archivo, "      COMPROBANTE DE REVISIÓN TÉCNICA       \n");
		fprintf(archivo, "============================================\n");
		fprintf(archivo, "Placa: %s\n", v->placa);
		fprintf(archivo, "Fecha: %s\n", obtenerFechaActual());
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "Revisión anterior 1: %d/100\n", v->revision1);
		fprintf(archivo, "Revisión anterior 2: %d/100\n", v->revision2);
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "REVISIÓN ACTUAL:\n");
		for (int i = 0; i < 8; i++) {
			fprintf(archivo, "  - %-20s: %2d/%2d\n", categorias[i], puntajes[i], maxPuntajes[i]);
		}
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "PUNTAJE TOTAL: %d/100\n", puntajeTotal);
		fprintf(archivo, "RESULTADO: %s\n", (puntajeTotal >= 70) ? "APROBADO" : "REPROBADO");
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "AVALÚO: $%.2f\n", v->avaluo);
		fprintf(archivo, "VALOR DE MATRÍCULA: $%.2f\n", v->matricula);
		fprintf(archivo, "============================================\n");
		
		fclose(archivo);
		
		printf("\nRevisión técnica %s.\n", (puntajeTotal >= 70) ? "APROBADA" : "REPROBADA");
		printf("Los resultados se han guardado en 'resultado_revision.txt'.\n");
		system("notepad resultado_revision.txt");
		
		return (puntajeTotal >= 70);
	}	


	// Función para registrar por matrícula las revisiones técnicas
void registrarRevisionTecnica(vehiculo *vehiculos, int total) {
		char placa[8];
		int encontrado = 0;
		
		printf("Ingrese la placa del vehículo para registrar revisión técnica: ");
		scanf("%7s", placa);
		while (getchar() != '\n');  // Limpiar buffer
		
		for (int i = 0; i < total; i++) {
			if (strcasecmp(vehiculos[i].placa, placa) == 0) {
				encontrado = 1;
				
				if (vehiculos[i].revisionRegistrada) {
					printf("La revisión técnica para este vehículo ya fue registrada.\n");
					return; // Salir para no registrar otra vez
				}
				
				printf("\nVehículo encontrado: %s\n", vehiculos[i].placa);
				int resultado = evaluarRevisionTecnica(&vehiculos[i]);
				
				if (resultado) {
					printf("El vehículo %s ha APROBADO la revisión técnica.\n", vehiculos[i].placa);
				} else {
					printf("El vehículo %s ha REPROBADO la revisión técnica.\n", vehiculos[i].placa);
				}
				
				// Marcar que ya se registró la revisión
				vehiculos[i].revisionRegistrada = 1;
				break;
			}
		}
		
		if (!encontrado) {
			printf("Vehículo no encontrado.\n");
		}
	}
	
	//Función principal para buscar por placa
	void buscarPorPlaca(vehiculo *vehiculos, int total){
		char placaBuscada[8];
		int encontrado = 0;
		
		printf("Ingrese la placa del vehículo a buscar: ");
		scanf("%s", placaBuscada);
		fflush(stdin);
		
		for(int i = 0; i < total; i++){
			if(strcasecmp(vehiculos[i].placa, placaBuscada) == 0){
				printf("\nVehículo encontrado:\n");
				printf("Cédula: %s\n", vehiculos[i].cedula);
				printf("Año: %d\n", vehiculos[i].anio);
				printf("Tipo: %s\n", tipoTexto(vehiculos[i].tipo));
				printf("Subtipo - Cilindraje: %dcc\n", vehiculos[i].cilindraje);
				printf("Avalúo: $%.2f\n", vehiculos[i].avaluo);
				encontrado = 1;
				break;
			}
		}
		if(!encontrado){
			printf("No se encontró un vehículo con esa placa.\n");
		}
	}
		
//Función principal Listar Vehículos
void listarVehiculos(vehiculo *vehiculos, int total){
	if(total == 0){
	printf("No hay vehículos registrados.\n");
		return;
	}
	for(int i = 0; i < total; i++){
	printf("\nVehículo #%d:\n", i+1);
	printf("Placa: %s\n", vehiculos[i].placa);
	printf("Cédula: %s\n", vehiculos[i].cedula);
	printf("Año: %d\n", vehiculos[i].anio);
	printf("Tipo: %s\n", tipoTexto(vehiculos[i].tipo));
	printf("Subtipo-cilindraje: %dcc\n", vehiculos[i].cilindraje);
	printf("Avalúo: $%.2f\n", vehiculos[i].avaluo);
	}
}

//Función principal Calcular valor de matrícula
float calcularValorMatricula(vehiculo v){
	float total=0.0f;
	switch (v.tipo) {
	case 0: 
		switch (v.subtipo) {
		case 0: total = 30.0f; break; 
		case 1: total = 50.0f; break; 
		case 2: total = 80.0f; break; 
		default: total = 50.0f; 
		}
		break;
		
	case 1: 
		switch (v.subtipo) {
		case 0: total = 100.0f; break; 
		case 1: total = 150.0f; break; 
		case 2: total = 200.0f; break; 
		default: total = 150.0f;
		}
		break;
		
	case 2: 
		switch (v.subtipo) {
		case 0: total = 300.0f; break; 
		case 1: total = 350.0f; break; 
		default: total = 300.0f;
		}
		break;
		
	case 3: 
		switch (v.subtipo) {
		case 0: total = 400.0f; break; 
		case 1: total = 450.0f; break; 
		default: total = 400.0f;
		}
		break;
		
	default:
		total = 100.0f; 
	}
	
	// Calcular antigüedad
	int antiguedad = 2025 - v.anio;
	if(antiguedad > 10){
		total *= 0.7f; 
	} else if (antiguedad >= 8) {
		total *= 0.8f; 
	} else if (antiguedad >= 4) {
		total *= 0.9f; 
	}
	
	if(v.esEcologico ==0){
		total -=30.0;
	}
	
	if(v.pagoConAnticipo == 0){
		total -=10.0;
	}
	
	if(v.pasoRevisionTecnica == 1){
		total += 50.0;
	}
	
	if(v.pagoATiempo == 1){
		total += 25.0;
	}
	
	// Multas con niveles
	int montosEstadoEtilico[] =     {0, 100, 200, 350};
	int montosSinCinturon[] =       {0, 25,  50,  100};
	int montosExcesoVelocidad[] =   {0, 100, 250, 500};
	total += montosEstadoEtilico[v.multaPorEstadoEtilico];
	total += montosSinCinturon[v.multaPorSinCinturon];
	total += montosExcesoVelocidad[v.multaPorSobrepasarLimiteDeVelocidad];
	
	return total;
}
