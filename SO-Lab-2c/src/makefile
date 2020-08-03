salida_out = pipeline

salida_headers = lab/funciones/Funciones.h 
salida_source  = $(salida_headers:.h=.c) main.c
salida_objects = $(salida_source:.c=.o)


CFLAGS = -Wall
CC     = gcc

depends = .depends


build : $(salida_out) $(leerImagen) 

$(salida_out) : $(salida_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(salida_source) $(salida_headers)
	@$(CC) -MM $(salida_source) > $@
	


clean :
	$(RM) $(salida_out) $(salida_objects) $(zipfile) $(depends)

.PHONY : build zip clean

sinclude $(depends)
