/*
 * Filtro.c
 *
 *  Created on: Aug 2, 2020
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


int width, height, channels;
unsigned char* img; //puntero que permite leer las imagenes
char orig[200];
char file[30];
char fdRead[30];
char sdRead[30];
int umbral_binario;
int umbral_clasificacion;
int cantidad;

/*
 * Function:  Image_to_convol_1D
 * --------------------
 * esta funci�n fue creada para hacer el calculo de convolucion, descripci�n de variables:
 * input = imagen a procesar
 * width = ancho imagen
 * height = alto imagen
 * channels = canales imagen
 * altom = dimension de mascara
 * anchom = dimension de mascasa
 * filter = arreglo con valores de mascara
 *  returns: no retorna valores
 */
void Image_to_convol_1D(unsigned char* input, int width, int height, int channels, int altom, int anchom, int* filter);

/*
 * Function:  convolucion
 * --------------------
 * esta funci�n fue creada para hacer la convoluci�n, donde se recibe las siguientes variables:
 * i = contador de imagen, ej: 1
 * width = ancho imagen
 * channels = canales imagen
 * returns: no retorna valores
 */
void convolucion(int i,int width, int height, int channels);
void proceso(char const *filename);
void init(char * nombre);
int* readF(FILE* f,int sizeCol);
void splitCadena(char *str);
void concatCadenaFilename();

int main(int argc, char *argv[]) {
	char mensajeLeido[30];
	read(STDIN_FILENO, mensajeLeido, 30*sizeof(char));
	//printf("3.......Filtro de realce: %s\n", mensajeLeido);
	strcpy(fdRead, mensajeLeido);
	splitCadena(fdRead);
	concatCadenaFilename();
	init("mascara.txt");

	img = stbi_load(orig,&width,&height,&channels,0);
 	convolucion(cantidad,width,height,channels);
	proceso(mensajeLeido);

	return 0;
}

void proceso(char const *filename){
	int valorFork;
	  	char* argumentos[2] = {"./binarizacion.o", NULL};
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
 * Function:  Image_to_convol_1D
 * --------------------
 * esta funci�n fue creada para hacer el calculo de convolucion, descripci�n de variables:
 * input = imagen a procesar
 * width = ancho imagen
 * height = alto imagen
 * channels = canales imagen
 * altom = dimension de mascara
 * anchom = dimension de mascasa
 * filter = arreglo con valores de mascara
 *  returns: no retorna valores
 */
void Image_to_convol_1D(unsigned char* input, int width, int height, int channels, int altom, int anchom, int* filter){
	size_t size = width * height * channels;
	out1d = malloc(size);

	int ancho = width ;  //206
	int alto = height;  //244

    int centroh=floor((double)(anchom/2));
    int centrov=floor((double)(altom/2));
  	int mv=0;
	int mh=0;
	int n=(alto-altom)+1;
	int m=(ancho-anchom)+1;
	for(int k=0;k<n;k++){
		mv=k;
		for (int l = 0;l<m;l++) {
 			mh=l;
			int con=0;
			int columna=0;
			int resultado=0;
			int linea= 0;
			for(int i=(0+mv); i<(altom+mv); i++){
				for(int j=(0+mh); j<(anchom+mh); j++){
					linea = j +(i* ancho);//(j+1)+(i*alto);
					resultado+= filter[con]*input[linea];
					con = con +1;

				}
			}
			columna = (centroh+mh)+((centrov+mv)*alto);
			if(resultado < 0){
				resultado = (uint8_t) 0;
			}if(resultado > 255){
				resultado =  (uint8_t)255;
			}
			out1d[columna]=(uint8_t)resultado;

		  }
		}
}

/*
 * Function:  convolucion
 * --------------------
 * esta funci�n fue creada para hacer la convoluci�n, donde se recibe las siguientes variables:
 * i = contador de imagen, ej: 1
 * width = ancho imagen
 * channels = canales imagen
 * returns: no retorna valores
 */
void convolucion(int i,int width, int height, int channels){
	//printf("\ninicio convol\n");
    char out[200];
    char char_aux[10];
	strcpy( out, "output/" );
	strcat( out, "imagen_filtro_laplacian_" );
	sprintf(char_aux, "%d", i);
	strcat( out, char_aux);
	strcat( out, ".jpg");
 	int gray_channels = channels == 4 ? 2 : 1;

	Image_to_convol_1D(img, width, height, channels, 3, 3, laplacian);
	stbi_write_png(out, width, height, gray_channels, img, width * gray_channels);
	stbi_image_free(img);
 }

/*
 * Function:  init
 * --------------------
 * esta funci�n iniciliza el arregle con la mascara,descripci�n de variables:
 * nombre = recibe el nombre del archivo a leer para la mascara, ejemplo mascara.txt
 * returns: no retorna valores
 */
void init(char * nombre){

	strcpy( dest_mask, folder_input );
	strcat( dest_mask, nombre);

	FILE* f = fopen(dest_mask,"r");
	if(f != NULL){
		leerMascara = 1;
		laplacian = readF(f,10);
		/*
		for(int z= 0; z <9; z++){
			printf("\n filtro[] %d ", laplacian[z]);
		}*/

	}
	//fclose(f);
}

/*
 * Function:  readF
 * --------------------
 * esta funci�n lee un archivo y carga los valores en arreglo de la mascara, posee  variables:
 * File:  puntero con nombre del arcjhivo mascara.txt
 * sizeCol : dimension del arreglo
 *
 *  returns: retorna valores del arreglo
 */
int* readF(FILE* f,int sizeCol){
	int i,j;
	int* array = malloc(sizeCol);
	if(array!=NULL){
		for (i = 0; i < sizeCol; i++){
			fscanf(f,"%d", &array[i]);
		}
	}
	return array;
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
