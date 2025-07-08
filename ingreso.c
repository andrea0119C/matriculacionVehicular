#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ingreso.h"

#define MAX_LINEA 100
#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_INTENTOS 3

// Función para leer contraseña mostrando asteriscos (Windows)
void leerContrasena(char *buffer, int max_len) {
	int i = 0;
	char c;
	while (1) {
		c = getch(); // Lee carácter sin mostrar en pantalla
		if (c == '\r' || c == '\n') { // Enter para terminar
			buffer[i] = '\0';
			printf("\n");
			break;
		} else if (c == '\b') { // Backspace
			if (i > 0) {
				i--;
				printf("\b \b"); // Borra el asterisco de pantalla
			}
		} else if (i < max_len - 1) {
			buffer[i++] = c;
			printf("*"); // Muestra asterisco
		}
	}
}

//Funcion para autentificar usuarios
int autenticar(const char *usuario, const char *clave) {
	FILE *archivo = fopen("usuarios.txt", "r");
	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		return -1;  // -1: error de archivo
	}
	
	char linea[MAX_LINEA];
	while (fgets(linea, sizeof(linea), archivo)) {
		linea[strcspn(linea, "\n")] = 0;
		
		char *usuario_archivo = strtok(linea, ":");
		char *clave_archivo = strtok(NULL, ":");
		
		if (usuario_archivo && strcmp(usuario, usuario_archivo) == 0) {
			fclose(archivo);
			if (clave_archivo && strcmp(clave, clave_archivo) == 0)
				return 1; // Usuario y clave correctos
			else
				return 0; // Usuario correcto, clave incorrecta
		}
	}
	
	fclose(archivo);
	return 2; // Usuario no encontrado
}

int registrarUsuario(const char *usuario, const char *clave) {
	FILE *archivo = fopen("usuarios.txt", "a"); // Abrir en modo añadir
	if (archivo == NULL) {
		perror("Error al abrir el archivo para registrar");
		return 0;
	}
	
	fprintf(archivo, "%s:%s\n", usuario, clave);
	fclose(archivo);
	return 1;
}
