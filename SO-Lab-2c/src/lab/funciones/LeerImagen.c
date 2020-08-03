/*
 * LeerImagen.c
 *
 *  Created on: Jul 24, 2020
 *      Author: monicaaraneda
 */

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "../variables/Variables.h"
#include "Funciones.h"

#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.

#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h> //define varios tipos de datos como pid_t


#define LECTURA 0
#define ESCRITURA 1
int width, height, channels,umbral_binario,umbral_clasificacion;
char fdRead[30];

/*
 * Function:  leerImagen
 * --------------------
 * funci�n principal que orquesta las dem�s funciones para convertir a gris, realizar la convoluci�n y detectar si una imagen es negra o no, recibe los siguientes par�metros
 *
 * cantidad = numero de imagenes a analizar
 * umbral_binario = umbral recibido desde pipeline
 * umbral_clasificacion = clasificaci�n recibido desde pipeline
 * returns: no retorna valores
 */
void leerImagen(int cantidad, int umbral_binario, int umbral_clasificacion);
void save(int cantidad, int sizeCol, int sizeRow,int channel,int umbral_binario, int umbral_clasificacion);
void proceso(char const *filename);
void splitCadena(char *str);

int umbral_binario;
int umbral_clasificacion;
int cantidad;


int main(int argc, char *argv[]) {
	char mensajeLeido[30];
	read(STDIN_FILENO, mensajeLeido, 30*sizeof(char));
	strcpy(fdRead, mensajeLeido);
	splitCadena(fdRead);
	//printf("\n1.......Lectura de imagen RGB: %s\n", mensajeLeido );

	leerImagen(cantidad, umbral_binario, umbral_clasificacion);
	proceso(mensajeLeido);
	return 0;
}

void proceso(char const *filename){
	int valorFork;
 	  	char* argumentos[2] = {"./convertirGris.o", NULL};
	  	//char mensajeEscrito1[30] = filename;
	  	int *pipes = (int*)malloc(sizeof(int)*2);
	  	pipe(pipes); //inicializa el pipe

	  	int status;
	    pid_t pid;


	  	pid = fork();
	  	if(pid > 0){
	  		close(pipes[LECTURA]); //El padre no va a leer, por lo tanto se cierra su descriptor
	  		write(pipes[ESCRITURA], fdRead, 30*sizeof(char));
 	  		waitpid(pid, &status,0);
	  	}
	  	else{

	  		close(pipes[ESCRITURA]); //Como el hijo no va a escribir, cierra el descriptor de escritura
 	   		dup2(pipes[LECTURA], STDIN_FILENO);

	  		execv(argumentos[0], argumentos);
	  	}
}


/*
 * Function:  leerImagen
 * --------------------
 * funci�n principal que orquesta las dem�s funciones para convertir a gris, realizar la convoluci�n y detectar si una imagen es negra o no, recibe los siguientes par�metros
 *
 * cantidad = numero de imagenes a analizar
 * umbral_binario = umbral recibido desde pipeline
 * umbral_clasificacion = clasificaci�n recibido desde pipeline
 * returns: no retorna valores
 */
void leerImagen(int cantidad, int umbral_binario, int umbral_clasificacion){
	char filename[30];
	//configuracion de filename
	sprintf(dest, "%s", "imagen_");
	strcpy( filename, dest );
	sprintf(char_aux, "%d", cantidad);
	strcpy( filename, char_aux );
	strcat( dest, char_aux);
	strcat( dest, ".jpg");
	strcpy( filename, dest );

 	//concatenamos la variable carpeta con el nombre de la imagen_n
	strcpy( dest, folder_input );
	strcat( dest, filename );

	img = stbi_load(dest,&width,&height,&channels,0);
 	save(cantidad,width,height,channels, umbral_binario,umbral_clasificacion);

}



void save(int cantidad, int sizeCol, int sizeRow,int channel,int umbral_binario, int umbral_clasificacion){
	int i,j;
	FILE *fichero;
	fichero = fopen("parametros.txt","w");
	fprintf(fichero,"%d %d %d %d %d %d",cantidad, sizeCol, sizeRow, channel,umbral_binario,umbral_clasificacion);

	fclose(fichero);
}

void splitCadena(char *str){
	    char s[256];
	    int i =0;
	    strcpy(s, fdRead);
	    char *token = strtok(s, ",");
	    while (token != NULL) {
	    	if(i == 0) cantidad = atoi(token);
	    	if(i == 1) umbral_binario = atoi(token);
	    	if(i == 2) umbral_clasificacion = atoi(token);
	        token = strtok(NULL, ",");
	        i++;
	    }
}


