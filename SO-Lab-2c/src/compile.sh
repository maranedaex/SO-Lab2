#!/bin/bash
echo "welcome compile in Ubuntu"

make

 gcc lab/funciones/LeerImagen.c -o leerimagen.o
 gcc lab/funciones/ConvertirGris.c -o  convertirGris.o
 gcc lab/funciones/Binarizacion.c -o  binarizacion.o
 gcc lab/funciones/Filtro.c -o  filtro.o