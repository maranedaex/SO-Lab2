/*
 * ConvertirGris.c
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
char orig[200];
char file[30];
char fdRead[30];
char sdRead[30];
int umbral_binario;
int umbral_clasificacion;
int cantidad;

/*
 * Function:  convertirGris
 * --------------------
 * esta funci�n fue creada para convertir la imagen a gris
 *
 * i = contador de imagen, ej: 1
 * width = ancho imagen
 * channels = canales imagen
 * returns: no retorna valores
 */
void convertirGris(char const *filename, int width, int height, int channels);
void readParam(FILE* f);
void proceso(char const *filename);
void splitCadena(char *str);
void concatCadenaFilename();


int main(int argc, char *argv[]) {
	char mensajeLeido[30];
	read(STDIN_FILENO, mensajeLeido, 30*sizeof(char));
	//printf("2.......Conversion a imagen en escala de grises: %s\n", mensajeLeido);
	strcpy(fdRead, mensajeLeido);
	splitCadena(fdRead);
	concatCadenaFilename();
	convertirGris(file, width, height, channels);
	proceso(mensajeLeido);
	return 0;
}

/*
 * Function:  convertirGris
 * --------------------
 * esta funci�n fue creada para convertir la imagen a gris
 *
 * i = contador de imagen, ej: 1
 * width = ancho imagen
 * channels = canales imagen
 * returns: no retorna valores
 */
void convertirGris(char const *filename, int width, int height, int channels){
	//printf("Entramos a convertirGris :::::");
	char desti[200];
	//concatenamos la variable carpeta con el nombre de la imagen_n
	strcpy( desti, folder_output );
	strcat( desti, filename );

    char orig[200];
    //concatenamos la variable carpeta con el nombre de la imagen_n
    strcpy( orig, folder_input );
    strcat( orig, filename );

    img = stbi_load(orig,&width,&height,&channels,0);
	size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;

    unsigned char *gray_img = malloc(gray_img_size);
    if(gray_img == NULL) {
        printf("\n No se puede asignar memoria para transformar la imagen en gris.\n");
    }

 	//*p 	= rojo
 	//*p+1 	= verde
 	//*p+2 	= azul
    for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
        *pg = (uint8_t)( (*p * 0.3) + (*(p + 1)*0.59) + (*(p + 2)*0.11)  );
        if(channels == 4) {
            *(pg + 1) = *(p + 3);
        }
    }
    stbi_write_png(desti, width, height, gray_channels, gray_img, width * gray_channels);
	//stbi_image_free(img);
	//printf("\n Imagen guardado en la carpeta: %s\n",desti);

}

void proceso(char const *filename){
	int valorFork;
	  	char* argumentos[2] = {"./filtro.o", NULL};
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
