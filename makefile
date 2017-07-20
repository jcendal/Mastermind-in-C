#********************************************************#
#*************** Compilación Master Mind ****************#
#***************** Cendal Prego, Jorge ******************#
#****************** Yáñez Mesía, Raúl *******************#
#********************************************************#

CC= gcc -Wall

all: mastermind_avanzado gestion_juego.o pantalla.o

LIBS: -lm

pantalla.o: pantalla.c pantalla.h
	$(CC) -c pantalla.c

gestion_juego.o: gestion_juego.c gestion_juego.h
	$(CC) -c gestion_juego.c

mastermind_avanzado: mastermind_avanzado.c pantalla.o gestion_juego.o
	$(CC) -o mastermind_avanzado mastermind_avanzado.c pantalla.o gestion_juego.o $(LIBS)

clean:
	rm -f mastermind_avanzado *.o *~ *.bak
