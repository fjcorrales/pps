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
