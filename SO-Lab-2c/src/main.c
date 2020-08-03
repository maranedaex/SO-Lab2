/**
 * Labatorio 1: Sistemas Operativos
 * Fecha: Mayo-Junio 2020
 * Descripcipon:
 * funci�n principal para ejecutar labotorio de S.O
 *
 * Autor: Monica Araneda
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//archivos .h creados para el proyecto

#include "lab/funciones/Funciones.h"


#define LECTURA 0
#define ESCRITURA 1
char fdRead[30];
char sdRead[30];

void proceso(int cantidad, int umbral_binario, int umbral_clasificacion);
void concatCadena(int cantidad, int umbral_binario, int umbral_clasificacion);

int main (int argc, char **argv){
	
  int cValue = 1; //cantidad de imagenes
  char mValue[2000]; //nombre archivo marcara laplaciana
  int uValue = 0; //umbral para binarizar imagen
  int nValue = 0; //umbral clasificacion
  int bValue = 0; //bandera, indica si mostrar el resultado por pantalla
  int c; //variable utilizada para la funci�n getopt

  //el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
  while ((c = getopt (argc, argv, "c:m:u:n:b")) != -1){
  		switch (c){
	      	case 'c': //cantidad de imagenes
	        	sscanf(optarg, "%d", &cValue);
	        	break;
	      	case 'm': //nombre archivo marcara laplaciana
	        	sscanf(optarg, "%s", &mValue);
	        	break;
	        case 'u': //umbral para binarizar imagen
	        	sscanf(optarg, "%d", &uValue);
	        	break;
	        case 'n': //umbral clasificacion
	        	sscanf(optarg, "%d", &nValue);
	        	break;
	        case 'b': //bandera, indica si mostrar el resultado por pantalla
	        	bValue = 1;
	        	break;
	      	default:
	        	abort();
    	}
  }
  
  init(mValue);
  proceso(cValue,uValue,nValue);

  
  return 0;
}

void proceso(int cantidad, int umbral_binario, int umbral_clasificacion){
	int valorFork;
	  	concatCadena(cantidad, umbral_binario, umbral_clasificacion);
	  	char* argumentos[2] = {"./leerimagen.o", NULL};
	  	//char*  mensajeEscrito[30] = filename;
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

/**
 *  @param : cantidad numero secuencia de imagen
 *  @param : umbral_binario = umbral recibido desde pipeline
 *  @param : umbral_clasificacion = clasificaci�n recibido desde pipeline
 */
void concatCadena(int cantidad, int umbral_binario, int umbral_clasificacion){
	    char char_aux[10];
	    char dest[200];

		sprintf(dest, "%s", "");
		strcpy( fdRead, dest );
	    sprintf(char_aux, "%d", cantidad);
	    strcpy( fdRead, char_aux );
	    strcat( dest, char_aux);
		strcat( dest, ",");
		strcpy( fdRead, dest );
		sprintf(char_aux, "%d", umbral_binario);
		strcpy( fdRead, char_aux );
		strcat( dest, char_aux);
		strcat( dest, ",");
		strcpy( fdRead, dest );
		sprintf(char_aux, "%d", umbral_clasificacion);
		strcat( dest, char_aux);
		strcpy( fdRead, dest );
		//printf("\ncadena ::  %s\n",fdRead);

}
