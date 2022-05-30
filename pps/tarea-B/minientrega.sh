#!/bin/bash

#var globales

ID_PRACTICA=""
let ARGUM_REQUER=1

#---------------------------------------------------------------------------

#Compruebo si los argumentos que me pasan son válidos

        if [ $# -ne $ARGUM_REQUER ] ; then
                echo "minientrega.sh: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"" >&2
                echo "minientrega.sh+ debe ser invocado con un argumento que identifique la practica" >&2
                exit 64
        else
            	if [ $1 == "-h" ] || [ $1 == "--help" ] ; then
                        echo "minientrega.sh: Uso: minientrega.sh [-h | --help |ID_PRACTICA]" 
                        echo "minientrega.sh realiza la entrega de la practica ID_PRACTICA"
                        exit 0
                fi
        fi


#Compruebo si MINIENTREGA_CONF es un directorio accesible 

	if test ! -d $MINIENTREGA_CONF ; then
		echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
		echo "minientrega.sh+ no es accesible el directorio \"$MINIENTREGA_CONF\"" >&2
		exit 64
	fi



#Compruebo si el ID_PRACTICA es valido 
comp=0
	for ident in $MINIENTREGA_CONF/* ;  do 
		if [ $1 == "$( basename $ident )" ] ; then 
			if test ! -r $ident ; then
                        echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
                        echo "minientrega.sh+ no es accesible el fichero \"$ident\"" >&2
                        exit 66
			
			else
				comp=1
				ID_PRACTICA=$ident
				source $ID_PRACTICA	
			fi
		fi
	done
	if test $comp -eq 0 ; then
		echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
        echo "minientrega.sh+ no es accesible el fichero \"$1\"" >&2
        exit 66
	fi


#Comprobamos que estamos en el directorio adecuado y que los ficheros de MINIENTREGA_FICHEROS se pueden leer
	
	for fich in $MINIENTREGA_FICHEROS ; do
		if test ! -r $fich ; then
			echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
			echo "minientrega.sh+ no es accesible el fichero \"$fich\""  >&2
			exit 66
		fi
	done

#Comprobamos que el directorio destino es accesible y modificable

	if test ! -w $MINIENTREGA_DESTINO ; then 
		echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
		echo "minientrega.sh+ no se puede crear el subdirectorio de entrega en \"$MINIENTREGA_DESTINO\"" >&2
		exit 73
	else
		mkdir $MINIENTREGA_DESTINO/$USER
	fi 


#Si todo ha ido correctamente, copiamos los ficheros en la carpeta destino
		
	for fich in $MINIENTREGA_FICHEROS ; do
		cp $fich -t $MINIENTREGA_DESTINO/$USER
	done
	exit 0
