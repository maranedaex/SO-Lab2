/**
 * Labatorio 1: Sistemas Operativos
 * Fecha: Mayo-Junio 2020
 * Descripcipon:
 * Funciones utilizadas para procesar imagenes y desarrollar el laboratorio 1 de S.O
 *
 * Autores: Monica Arriagada y Diego Valladares
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>
#include <string.h>
#include "../variables/Variables.h"
#include "Funciones.h"

/*
 * Function:  imprimirdebug 
 * --------------------
 * esta funci�n fue creada para imprimir los valores que ingreso el usuario por consola, descripci�n de variables:
 * c = cantidad de imagenes a procesar
 * m = recbie el nombre archivo marcara laplaciana, ej: archivo.txt
 * u = umbral para binarizar imagen
 * n = umbral clasificacion
 * b = bandera, indica si mostrar el resultado por pantalla
 *
 *  returns: no retorna valores
 */
void imprimirdebug(int c, char m[],int u, int n, int b){
  printf("El valor de c es: %i\nEl valor de m es: %s\nEl valor de u es: %i\nEl valor de n es: %i\nEl valor de b es: %i\n", c,m, u,n,b);
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
	strcpy( out, folder_output );
	strcat( out, "imagen_filtro_laplacian" );
	sprintf(char_aux, "%d", i);
	strcat( out, char_aux);
	strcat( out, ".jpeg");
	
	int gray_channels = channels == 4 ? 2 : 1;
	
	

	Image_to_convol_1D(img, width, height, channels, 3, 3, laplacian);
	stbi_write_png(out, width, height, gray_channels, img, width * gray_channels);
	stbi_image_free(img);
	//printf("\n CONVOLUCION! Imagen guardado en la carpeta: %s\n",out);
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
