/*
 * Binarizacion.c
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

char orig[200];
char file[30];
char fdRead[30];
char sdRead[30];
int umbral_binario;
int umbral_clasificacion;
int cantidad;

/*
 * Function:  nearly_black
 * --------------------
 * esta funci�n fue creada para identificar si una imaben es nearly black, donde recibe las siguientes variables:
 * umbral_binario = umbral recibido desde pipeline
 * umbral_clasificacion = clasificaci�n recibido desde pipeline
 * i = contador de imagen, ej: 1
 * width = ancho imagen
 * channels = canales imagen
 * returns: no retorna valores
 */
int nearly_black(int umbral_binario,int umbral_clasificacion,int i,int width, int height, int channels);
/*
 * Function:  imprimir
 * --------------------
 * Esta funci�n se usa para imprimir el resultado de las imagenes analizadas.
 * s�lo se ejecuta si el usuario escribio la opci�n "-b" en la ejecuci�n del proceso
 *
 *  returns: no retorna valores
 */
void imprimir(int num);
//comentar funcion
void insertarDataTabla(char nombre[100], int isNearlyBlack);

void readParam(FILE* f);
void splitCadena(char *str);
void concatCadenaFilename();

int width, height, channels,umbral_binario,umbral_clasificacion;
int bValue;

int main(int argc, char *argv[]) {
	int isNearlyBlack = 0;
	char mensajeLeido[30];
	read(STDIN_FILENO, mensajeLeido, 30*sizeof(char));
	//printf("4.......Binarizacion Mi padre dice: %s\n", mensajeLeido);
	strcpy(fdRead, mensajeLeido);
	splitCadena(fdRead);
	concatCadenaFilename();
    isNearlyBlack = nearly_black(umbral_binario,umbral_clasificacion,cantidad,width, height, channels);
     insertarDataTabla("imagen_",isNearlyBlack);

    if(bValue == 1){
     	imprimir(cantidad);
     }else{
   	//imprimirdebug(cValue,mValue,uValue,nValue,bValue);
     }

	return 0;
}

/*
 * Function:  nearly_black
 * --------------------
 * esta funci�n fue creada para identificar si una imaben es nearly black, donde recibe las siguientes variables:
 * umbral_binario = umbral recibido desde pipeline
 * umbral_clasificacion = clasificaci�n recibido desde pipeline
 * i = contador de imagen, ej: 1
 * width = ancho imagen
 * channels = canales imagen
 * returns: no retorna valores
 */
int nearly_black(int umbral_binario,int umbral_clasificacion,int i,int width, int height, int channels){
	int count_nearly_black = 0;
	int isNearlyBlack = 0;

	//concatenamos la variable carpeta con el nombre de la imagen_n
	strcpy( dest, folder_output );
	strcat( dest, "imagen_gris_binario_" );
	sprintf(char_aux, "%d", i);
	strcat( dest, char_aux);
	strcat( dest, ".jpg");

	char orig[200];
	//concatenamos la variable carpeta con el nombre de la imagen_n
	strcpy( orig, folder_input );
	strcat( orig, file );

	img = stbi_load(orig,&width,&height,&channels,0);
	size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;

    unsigned char *gray_img = malloc(gray_img_size);

	for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
        if(*p > umbral_binario){
        	*pg = 255;
		}else{
			*pg = 0;
			count_nearly_black++;
		}
    }

    //Verificaci?n si la imagen es Nearly Black
    if(count_nearly_black > umbral_clasificacion){
     	isNearlyBlack = 1;
	}else{
 		isNearlyBlack = 0;
	}

    stbi_write_png(dest, width, height, gray_channels, gray_img, width * gray_channels);
     bValue = 1;
	return isNearlyBlack;
}

//describir funcion
void insertarDataTabla(char* nombre, int isNearlyBlack){
	matriz[pos][0] = nombre;
	matriz[pos][1] = (isNearlyBlack == 1) ? "Yes" : "No";
	pos++;
}

/*
 * Function:  imprimir
 * --------------------
 * Esta funci�n se usa para imprimir el resultado de las imagenes analizadas.
 * s�lo se ejecuta si el usuario escribio la opci�n "-b" en la ejecuci�n del proceso
 *
 *  returns: no retorna valores
 */
void imprimir(int num){
	int i = 0;
	int aux=0;
	printf("\n");
	printf("|	Imagen		|	Nearly black 	|\n");
	printf("-------------------------------------------------\n");

	for(i = 0; i <= pos; i++){
		if(matriz[i][0] != NULL){
			aux = i+1;
			printf("|	imagen_%d	|	%s		|\n",num,matriz[i][1]);
		}
	}
	printf("\n");
}

void readParam(FILE* f){
 	char buffer[12];
 	fscanf(f,"%s %d %d %d %d %d",&buffer,&width, &height, &channels,&umbral_binario,&umbral_clasificacion);
 	filename = buffer;
	fclose (f);

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

void concatCadenaFilename(){
	sprintf(dest, "%s", "imagen_");
	strcpy( sdRead, dest );
	sprintf(char_aux, "%d", cantidad);
	strcpy( sdRead, char_aux );
	strcat( dest, char_aux);
	strcat( dest, ".jpg");
	strcpy( file, dest );
	strcpy( orig, folder_input );
	strcat( orig, file );

}
