/**
 * Labatorio 1: Sistemas Operativos
 * Fecha: Mayo-Junio 2020
 * Descripcipon:
 * Funciones utilizadas para procesar imagenes y desarrollar el laboratorio 1 de S.O
 *
 * Autores: Monica Arriagada y Diego Valladares
 */
#ifndef Funciones_h_
#define Funciones_h_
//#include "../variables/Variables.h"
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
void imprimirdebug(int c, char m[],int u, int n, int b);







/*
 * Function:  init
 * --------------------
 * esta funci�n iniciliza el arregle con la mascara,descripci�n de variables:
 * nombre = recibe el nombre del archivo a leer para la mascara, ejemplo mascara.txt
 * returns: no retorna valores
 */
void init(char* nombre);

/*
 * Function:  readF
 * --------------------
 * esta funci�n lee un archivo y carga los valores en arreglo de la mascara, posee  variables:
 * File:  puntero con nombre del arcjhivo mascara.txt
 * sizeCol : dimension del arreglo
 * 
 *  returns: retorna valores del arreglo
 */
int* readF(FILE* f,int sizeCol);
#endif
