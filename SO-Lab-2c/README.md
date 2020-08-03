# README
 
Autores: Monica Araneda  
Sistema Operativo
Labatorio 2
Fecha: 1 Agosto 2020

# COMPILAR
 
_Se compile con la shell :  

```
 ./compile.sh
``` 

## CARPETAS


```
-input	: carpeta donde se encuentran las imagenes a procesar y archivo de la mascara
-output	: carpeta donde saldran las imagenes procesadas
-lab	: carpeta donde se encuentran las funciones y librerías utilizados para este laboratorio
``` 
 



## IMAGENES
 
_Las imagenes deben estar ubicadas en la carpeta input, cuyo nombre debe ser imagen_1, imagen_2, imagen_3, etc.._


## MASCARA
 
_El archivo de la mascara laplaciana debe estar en la carpeta input en formato .txt. Para este labarotorio se encuentran el archivo: mascara.txt para hacer las pruebas_

_Es importante que los digitos de la mascara deben estar separados por un espacio, ej: 0 1 0 -1 -4 -1 0 -1 0_


# RESTRICCIONES
 
_Sólo se pueden leer imagenes con extension .jpg_


# EJECUCION
 
_Paso 1:  Escribir ./compile.sh_
_Paso 2:  Escribir instrucción de ejecucion. Por defecto lee la mascara.txt_

```
Ejemplo #1: ./pipeline -c 1  -u 50 -n 10000 -b   // parametro -c 1 lee imagen_1.jpg
Ejemplo #2: ./pipeline -c 2  -u 50 -n 10000 -b   // parametro -c 2 lee imagen_2.jpg
Ejemplo #3: ./pipeline -c 3  -u 50 -n 10000 -b   // parametro -c 3 lee imagen_3.jpg

``` 




