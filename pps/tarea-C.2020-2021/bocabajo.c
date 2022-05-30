#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"

struct punt{
	char text[2048];
	struct punt *next;
};

struct punt *top = NULL;

void push(char* word){
	struct punt *newPunt =(struct punt*) malloc(sizeof(struct punt));
	if(newPunt == NULL){
		Error(EX_OSERR,"No se puede ubicar la memoria dinamica");
	}
	strcpy(newPunt -> text, word);
	newPunt -> next = top;
	top = newPunt;	
}//Fin push

void imprimir(){
	if(top != NULL){
		struct punt *aux =(struct punt*) malloc(sizeof(struct punt));
		while(top != NULL){		
			printf("%s", top -> text);
			aux = top;
			top = (*top).next;
			free(aux);
		}//Fin while
		free(top);
	}
}//Fin Imprimir

int main(int argc, char *argv[]){
	char aux[2048];
	int i;
	if((argc>1) && ((strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")== 0))){
		printf("bocabajo: Uso: bocabajo [ fichero... ]\n");
		printf("bocabajo: Invierte el orden de las lineas de los ficheros (o de la entrada).\n");
		return EX_OK;
	}
		for(i = 1 ; i<argc ; i++ ){					//For para abrir ficheros (tendra otro bucle dentro para leer cada fichero)
		FILE *f;
		f = fopen(argv[i], "r");

		if(f == NULL){  						//If de comprobacion de si se ha abierto correctamente el fichero
			Error(EX_NOINPUT, "\"%s\" no puede ser leido.", argv[i]);
		}//Fin if
			while(fgets(aux, 2048, f) != NULL){	//While para leer el fichero, tambien guardare durante este proceso los datos en la pila
			push(aux);
		}//Fin while
			fclose(f);
	}//Fin for

	if(argc <= 1){
		while(fgets(aux, 2048, stdin)){
			push(aux);
		}//fin while
	}//Fin if
	imprimir();
	return EX_OK;
}//Fin main
