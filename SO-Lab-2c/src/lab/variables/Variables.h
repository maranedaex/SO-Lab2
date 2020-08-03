#ifndef Variables_h_
#define Variables_h_

//Variables utilizadas por librer�a stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

char folder_input[100] = "input/"; //variable que define la carpeta donde se encuentran las imagenes
char folder_output[100] = "output/"; //variable que define donde se almacenar�n las imagenes procesadas
unsigned char* img; //puntero que permite leer las imagenes
char nombre_imagen[200]; //variable utilizado para setear el nombre de la imagen
char dest[200]; //variable utilizado para obtener la ruta final de la imagen
char dest_mask[200]; //variable utilizado para obtener la ruta final de la mascara.txt
char in[200]; //variable utilizado para obtener la ruta final de la imagen
char out[200]; //variable utilizado para obtener la ruta final de la imagen
char char_aux[10]; //variable utilizado para convertir int en char
char* matriz[5][2]; //matriz de 10 filas x 2 columnas utilizado para imprimir resultado de las imagenes
int pos = 0; //posicion de la fila de la matriz inicializada anteriormente
unsigned char** out2d;   // array 2D  imagen filtrada
unsigned char*  out1d;    // array 1D  imagen filtrada
int* laplacian; //utilizado para almacenar variable del archivo .txt
int leerMascara = 0; //flag que identifica si el archivo mascara.txt fu� leido
char const *filename;

#endif // Variables_h_
