//Librerias estandar
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>



//Librer�a propia
#include "registroVehiculos.h"

//Funci�n para may�sculas 
void strToLower(char *str){
	for(int i=0; str[i]; i++){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] += 'a' - 'A';
		}
	}
}
	
//Funci�n auxiliar para validar c�dula
int validarCedula(const char *ced){
	if(strlen(ced) != 10)
		return 0;
	for(int i = 0; i < 10; i++){
		if(!isdigit(ced[i]))
			return 0;
	}
	return 1;
}

//Funci�n auxiliar para validar el a�o	
int validarAnio(int anio) {
	return (anio >= 2000 && anio <= 2025);
}

//Funci�n auxiliar para validar tipo
int validarTipo(int tipo){
	return( tipo == 0 || tipo == 1 || tipo == 2 || tipo == 3);
}

//Funci�n auxiliar para mostrar en texto el tipo
const char* tipoTexto(int tipo){
	switch(tipo){
		case 0: return "Moto";
		case 1: return "Liviano";
		case 2: return "Mediano";
	    case 3: return "Pesado";
		default: return "Desconocido";
	}
}

//Funci�n auxiliar para validar Subtipo dependiendo el tipo
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

//Funci�n auxiliar para validar descuento
int validarDescuento(int opcion){
	return ( opcion == 0 || opcion == 1);
}

//Funci�n auxiliar para validar retenci�n
int validarRetencion(int opcion){
	return ( opcion == 0 || opcion == 1);
}

//Funci�n auxiliar para validar multas
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


//Funci�n para registrar los veh�culos
void registroVehiculo(vehiculo *veh, vehiculo *vehiculos, int total){
	char buffer[100];
	int valida=0;
	int tipoValido;
	char entrada[10];
	while(!valida){
		
	 
	printf("Ingrese la placa del veh�culo: \n");
	//Ingrese la placa del veh�culo
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
			printf("Ya existe un veh�culo registrado con esa placa.\n");
		} else {
			printf("Placa inv�lida. Intente nuevamente.\n");
		}
	} else {
		printf("La placa debe tener exactamente 7 caracteres.\n");
	}
	}
	
		
		//Ingrese el n�mero de c�dula del usuario
	do {
		printf("Ingrese la c�dula del usuario (10 d�gitos): \n");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0'; // Quita salto de l�nea
		
		if (validarCedula(buffer)) {
			strncpy(veh->cedula, buffer, sizeof(veh->cedula));
			break;
		} else {
			printf("C�dula inv�lida. Debe tener exactamente 10 d�gitos num�ricos.\n");
		}
	} while (1);
	
		
	//Ingrese el a�o del veh�culo
	do {
		printf("Ingrese el a�o del veh�culo: \n");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		// Verificamos que sea un n�mero
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
		printf("A�o inv�lido. Debe estar entre 2000 y 2025.\n");
	} while (1);
		
	//Ingrese el tipo de veh�culo
	do {
		printf("Ingrese el tipo de veh�culo \n 0.-Moto \n 1.-Liviano \n 2.-Mediano \n 3.-Pesado: \n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->tipo);
		
		
		
		if (tipoValido !=1 || !validarTipo (veh->tipo)) {
			printf("Tipo inv�lido. Solo se permite: 0, 1, 2 o 3.\n");
		}
	} while (tipoValido !=1 || !validarTipo (veh->tipo));
	limpiarPantalla();
 
	//Ingrese el subtipo
	int subtipoIngresado;
	do{
		printf("Ingrese el Cilindraje de veh�culo para el tipo %s:\n", tipoTexto(veh->tipo));
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
			printf("Opci�n inv�lida. Intente de nuevo.Ingresar 0 o 1\n");
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
	    printf("Es ecol�gico: \n Ingrese:\n 0.- Si es escol�gico \n 1.- No es escol�gico:\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->esEcologico);
	    
	    if (tipoValido !=1 || !validarDescuento (veh->esEcologico)) {
		    printf("Opci�n inv�lido. Solo se permite:Ingresar 0 o 1.\n");
	}  
	} while (tipoValido !=1 || !validarDescuento (veh->esEcologico));
	limpiarPantalla();
	
	do{
	    printf("Realizo el pago antes de tiempo: \n Ingrese: \n 0.-Si es correcto \n 1.- No es correcto: \n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->pagoConAnticipo);
		if (tipoValido !=1 || !validarDescuento (veh->pagoConAnticipo)) {
			printf("Opci�n inv�lido. Solo se permite:Ingresar 0 o 1.\n");
		}  
	} while (tipoValido !=1 || !validarDescuento (veh->pagoConAnticipo));
	limpiarPantalla();
	
	do{
	    printf("Paso a la primera revisi�n t�cnica: \n Ingrese: \n 0.-Si es correcto \n 1.-No es correcto:\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->pasoRevisionTecnica);
		if (tipoValido !=1 || !validarRetencion (veh->pasoRevisionTecnica)) {
			printf("Opci�n inv�lido. Solo se permite:Ingresar 0 o 1.\n");
		}  
	} while (tipoValido !=1 || !validarRetencion (veh->pasoRevisionTecnica));
	limpiarPantalla();
	
	do{
	    printf("Pago a tiempo: \n Ingrese: \n 0.- Si es correcto \n 1.- No es correcto:\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->pagoATiempo);
		if (tipoValido !=1 || !validarRetencion (veh->pagoATiempo)) {
			printf("Opci�n inv�lido. Solo se permite:Ingresar 0 o 1.\n");
		}  
	} while (tipoValido !=1 || !validarRetencion (veh->pagoATiempo));
	limpiarPantalla();
	
	// MULTA POR ESTADO ET�LICO
	do {
		printf("Multa por manejar en estado et�lico:\n");
		printf("0.- Sin multa\n1.- Leve \n2.- Moderada \n3.- Grave\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorEstadoEtilico);
		if (tipoValido != 1 || !validarMultas(veh->multaPorEstadoEtilico)) {
			printf("Opci�n inv�lida. Solo se permite: 0 a 3.\n");
		}  
	} while (tipoValido != 1 || !validarMultas(veh->multaPorEstadoEtilico));
	limpiarPantalla();
	
	// MULTA POR NO USAR CINTUR�N
	do {
		printf("Multa por no usar cintur�n de seguridad:\n");
		printf("0.- Sin multa\n1.- Un cintur�n\n2.- Dos o tres cinturones\n3.- Cuatro o cinco cinturones\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorSinCinturon);
		if (tipoValido != 1 || !validarMultas(veh->multaPorSinCinturon)) {
			printf("Opci�n inv�lida. Solo se permite: 0 a 3.\n");
		}  
	} while (tipoValido != 1 || !validarMultas(veh->multaPorSinCinturon));
	limpiarPantalla();
	
	// MULTA POR EXCESO DE VELOCIDAD
	do {
		printf("Multa por sobrepasar el l�mite de velocidad:\n");
		printf("0.- Sin multa\n1.- Leve \n2.- Moderada\n3.- Grave\n");
		fgets(entrada, sizeof(entrada), stdin);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorSobrepasarLimiteDeVelocidad);
		if (tipoValido != 1 || !validarMultas(veh->multaPorSobrepasarLimiteDeVelocidad)) {
			printf("Opci�n inv�lida. Solo se permite: 0 a 3.\n");
		}  
	} while (tipoValido != 1 || !validarMultas(veh->multaPorSobrepasarLimiteDeVelocidad));
	limpiarPantalla();
	
	veh->avaluo = calcularAvaluo(*veh);
   }
//Funci�n principal para calcular Avaluo
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
	
	// Funci�n para obtener la fecha actual
	const char* obtenerFechaActual() {
		static char fecha[11]; // Formato: DD-MM-AAAA
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		sprintf(fecha, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		return fecha;
	}
	// Funci�n auxiliar para validar entradas
	int leerPuntaje(const char *mensaje, int min, int max) {
		int valor;
		do {
			printf("%s (%d-%d): ", mensaje, min, max);
			if (scanf("%d", &valor) != 1) {
				printf("�Error! Ingrese un n�mero v�lido.\n");
				while (getchar() != '\n');
				continue;
			}
			if (valor < min || valor > max) {
				printf("�Error! El valor debe estar entre %d y %d.\n", min, max);
			}
		} while (valor < min || valor > max);
		return valor;
	}
	
	// Funci�n para evaluar las revisiones t�cnicas
	int evaluarRevisionTecnica(vehiculo *v) {
		
		// Validaci�n para revisiones anteriores
		printf("�Pas� la PRIMERA revisi�n t�cnica? (1 = s�, 0 = no): ");
		int pasada1;
		do {
			if (scanf("%d", &pasada1) != 1) {
				printf("Entrada no v�lida. Ingrese 1 (s�) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (pasada1 != 0 && pasada1 != 1);
		
		if (pasada1) {
			v->revision1 = leerPuntaje("Ingrese el puntaje obtenido", 0, 100);
		} else {
			printf("\nDebe realizar la revisi�n 1 antes de continuar.\n");
			printf("Por favor regrese cuando haya completado la revisi�n t�cnica 1.\n");
			return 0; // <-- retorna al men�
		}
		
		printf("�Pas� la SEGUNDA revisi�n t�cnica? (1 = s�, 0 = no): ");
		int pasada2;
		do {
			if (scanf("%d", &pasada2) != 1) {
				printf("Entrada no v�lida. Ingrese 1 (s�) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (pasada2 != 0 && pasada2 != 1);
		
		if (pasada2) {
			v->revision2 = leerPuntaje("Ingrese el puntaje obtenido", 0, 100);
		} else {
			printf("\nDebe realizar la revisi�n 2 antes de continuar.\n");
			printf("Por favor regrese cuando haya completado la revisi�n t�cnica 2.\n");
			return 0;
		}
		
		// Evaluaci�n t�cnica actual
		int puntajes[8];
		const char *categorias[8] = {
			"Frenos",
				"Luces",
				"Emisiones",
				"Neum�ticos",
				"Espejos y parabrisas",
				"Cinturones",
				"Bocina y limpiaparabrisas",
				"Documentaci�n al d�a"
		};
		int maxPuntajes[8] = {25, 15, 15, 10, 10, 10, 5, 10};
		
		printf("\nEvaluaci�n t�cnica actual:\n");
		int puntajeTotal = 0;
		for (int i = 0; i < 8; i++) {
			puntajes[i] = leerPuntaje(categorias[i], 0, maxPuntajes[i]);
			puntajeTotal += puntajes[i];
		}
		v->revisionActual = puntajeTotal;
		printf("\nRevisi�n t�cnica %s.\n", (puntajeTotal >= 70) ? "APROBADA" : "REPROBADA");
		
		// Preguntar al final si desea comprobante
		int imprimir;
		printf("\n�Desea imprimir el comprobante? (1 = S�, 0 = No): ");
		do {
			if (scanf("%d", &imprimir) != 1 || (imprimir != 0 && imprimir != 1)) {
				printf("Entrada inv�lida. Ingrese 1 (s�) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (imprimir != 0 && imprimir != 1);
		
		if (!imprimir) {
			printf("No se generar� el comprobante.\n");
			return (puntajeTotal >= 70);
		}
		// Calcular matr�cula antes de imprimir
		v->matricula = calcularValorMatricula(*v);
		
		// Imprimir comprobante
		FILE *archivo = fopen("resultado_revision.txt", "w");
		if (!archivo) {
			printf("No se pudo crear el archivo de resultados.\n");
			return (puntajeTotal >= 70);
		}
		
		// Generar comprobante con formato
		fprintf(archivo, "============================================\n");
		fprintf(archivo, "      COMPROBANTE DE REVISI�N T�CNICA       \n");
		fprintf(archivo, "============================================\n");
		fprintf(archivo, "Placa: %s\n", v->placa);
		fprintf(archivo, "Fecha: %s\n", obtenerFechaActual());
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "Revisi�n anterior 1: %d/100\n", v->revision1);
		fprintf(archivo, "Revisi�n anterior 2: %d/100\n", v->revision2);
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "REVISI�N ACTUAL:\n");
		for (int i = 0; i < 8; i++) {
			fprintf(archivo, "  - %-20s: %2d/%2d\n", categorias[i], puntajes[i], maxPuntajes[i]);
		}
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "PUNTAJE TOTAL: %d/100\n", puntajeTotal);
		fprintf(archivo, "RESULTADO: %s\n", (puntajeTotal >= 70) ? "APROBADO" : "REPROBADO");
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "AVAL�O: $%.2f\n", v->avaluo);
		fprintf(archivo, "VALOR DE MATR�CULA: $%.2f\n", v->matricula);
		fprintf(archivo, "============================================\n");
		
		fclose(archivo);
		
		printf("\nRevisi�n t�cnica %s.\n", (puntajeTotal >= 70) ? "APROBADA" : "REPROBADA");
		printf("Los resultados se han guardado en 'resultado_revision.txt'.\n");
		system("notepad resultado_revision.txt");
		
		return (puntajeTotal >= 70);
	}	


	// Funci�n para registrar por matr�cula las revisiones t�cnicas
void registrarRevisionTecnica(vehiculo *vehiculos, int total) {
		char placa[8];
		int encontrado = 0;
		
		printf("Ingrese la placa del veh�culo para registrar revisi�n t�cnica: ");
		scanf("%7s", placa);
		while (getchar() != '\n');  // Limpiar buffer
		
		for (int i = 0; i < total; i++) {
			if (strcasecmp(vehiculos[i].placa, placa) == 0) {
				encontrado = 1;
				
				if (vehiculos[i].revisionRegistrada) {
					printf("La revisi�n t�cnica para este veh�culo ya fue registrada.\n");
					return; // Salir para no registrar otra vez
				}
				
				printf("\nVeh�culo encontrado: %s\n", vehiculos[i].placa);
				int resultado = evaluarRevisionTecnica(&vehiculos[i]);
				
				if (resultado) {
					printf("El veh�culo %s ha APROBADO la revisi�n t�cnica.\n", vehiculos[i].placa);
				} else {
					printf("El veh�culo %s ha REPROBADO la revisi�n t�cnica.\n", vehiculos[i].placa);
				}
				
				// Marcar que ya se registr� la revisi�n
				vehiculos[i].revisionRegistrada = 1;
				break;
			}
		}
		
		if (!encontrado) {
			printf("Veh�culo no encontrado.\n");
		}
	}
	
	//Funci�n principal para buscar por placa
	void buscarPorPlaca(vehiculo *vehiculos, int total){
		char placaBuscada[8];
		int encontrado = 0;
		
		printf("Ingrese la placa del veh�culo a buscar: ");
		scanf("%s", placaBuscada);
		fflush(stdin);
		
		for(int i = 0; i < total; i++){
			if(strcasecmp(vehiculos[i].placa, placaBuscada) == 0){
				printf("\nVeh�culo encontrado:\n");
				printf("C�dula: %s\n", vehiculos[i].cedula);
				printf("A�o: %d\n", vehiculos[i].anio);
				printf("Tipo: %s\n", tipoTexto(vehiculos[i].tipo));
				printf("Subtipo - Cilindraje: %dcc\n", vehiculos[i].cilindraje);
				printf("Aval�o: $%.2f\n", vehiculos[i].avaluo);
				encontrado = 1;
				break;
			}
		}
		if(!encontrado){
			printf("No se encontr� un veh�culo con esa placa.\n");
		}
	}
		
//Funci�n principal Listar Veh�culos
void listarVehiculos(vehiculo *vehiculos, int total){
	if(total == 0){
	printf("No hay veh�culos registrados.\n");
		return;
	}
	for(int i = 0; i < total; i++){
	printf("\nVeh�culo #%d:\n", i+1);
	printf("Placa: %s\n", vehiculos[i].placa);
	printf("C�dula: %s\n", vehiculos[i].cedula);
	printf("A�o: %d\n", vehiculos[i].anio);
	printf("Tipo: %s\n", tipoTexto(vehiculos[i].tipo));
	printf("Subtipo-cilindraje: %dcc\n", vehiculos[i].cilindraje);
	printf("Aval�o: $%.2f\n", vehiculos[i].avaluo);
	}
}

//Funci�n principal Calcular valor de matr�cula
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
	
	// Calcular antig�edad
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
