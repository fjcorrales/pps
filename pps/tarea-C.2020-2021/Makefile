 #
 # Makefile
 # Copyright (c) 2000, Francisco Rosales <frosal@fi.upm.es>
 # Copyright (c) 2009, Ángel Herranz <aherranz@fi.upm.es>
 #
 # NO MODIFIQUE ESTE FICHERO
 #

CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	= -lm

BINS	= ejemplo bocabajo 
#BINS	= ejemplo factores
# XTRA	= run

all:	autores.txt $(XTRA) auxiliar.o $(BINS)

auxiliar.o:	auxiliar.c auxiliar.h
	$(CC) $(CFLAGS) -c auxiliar.c

#run.o:	run.c
#	$(CC) $(CFLAGS) -c run.c

#run:	run.o
#	$(CC) $(CFLAGS) $@.o -o $@ -lutil

run: -lutil

Combinado: $(BINS)

$(BINS): auxiliar.o
	$(CC) $(CFLAGS) $@.c -o $@ auxiliar.o $(LDFLAGS)

clean:
	rm -f *.tab.? *.o *.bak *~ core

cleanall: clean
	rm -f $(XTRA) $(BINS)

autores.txt ::
	@echo 'Autores:'; \
	cont=0; \
	while IFS=: read M A1 A2 N R; \
        do \
                [ $$M ] && [ $$A1 ] && [ $$A2 ] && [ $$N ] || \
		echo "ERROR: Falta algun campo en la linea."; \
                [ $$R ] && \
                echo "ERROR: Demasiados campos en la linea."; \
		echo  "Matricula:       $$M";\
                echo  "Apellido 1:      $$A1";\
                echo  "Apellido 2:      $$A2";\
                echo  "Nombre:          $$N";\
                echo ""; \
        done < autores.txt && [ -s autores.txt ] || \
        echo "ERROR: El fichero \"autores.txt\" debe poder ser leido y \
tener el formato correcto."; \

# Dependencias...
#analiza:	auxiliar.o analiza.c
ejemplo:	auxiliar.o ejemplo.c
#factores:	auxiliar.o factores.c
bocabajo: auxiliar.o bocabajo.c
