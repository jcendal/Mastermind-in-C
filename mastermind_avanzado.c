/*******************************************************
***************** Master Mind Avanzado *****************
***************** Cendal Prego, Jorge ******************
****************** Yáñez Mesía, Raúl *******************
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gestion_juego.h"
#include "pantalla.h"

int main()
	{
	
	char num[1];
	int try,y,idioma,bienc,regc,malc,notsaved;
	
	asteriscos(3,80,'*');           //Llamamos a la función de cabecera con el número de simbolos(asterisco en este caso) a imprimir
	printf("\n");	
	try=100;                        //Inicializamos en número de intentos a 100
	idioma=1;                       //Inicializamos el idioma a castellano
	bienc=32;
	regc=33;
	malc=31;
	notsaved=0;                     //Inicializamos el valor del parametro de control de guardado a 0 (nada que guardar)
	remove("aux.txt");              
	while(num[0]!='0'){             //Mientras no seleccionemos salir de partida mostramos menú

	if(idioma==1){
		printf("\n\t1) Jugar partida\n\t2) Jugar partida de prueba\n\t3) Establecer nivel de dificultad\n\t4) Listar historial de partidas");
		if(notsaved==1)printf("\n\t5) Guardar partida jugada");
		printf("\n\t6) Establecer idioma\n\t0) Salir\n\n\t¿Siguiente operación?\n\n");
	}
	if(idioma==2){
		printf("\n\t1) Xogar partida\n\t2) Xogar partida de proba\n\t3) Establecer nivel de dificultad\n\t4) Listar historial de partidas");
		if(notsaved==1)printf("\n\t5) Gardar partida xogada");
		printf("\n\t6) Establecer idioma\n\t0) Saír\n\n\t¿Seguinte operación?\n\n");
	}
	if(idioma==3){
		printf("\n\t1) Play game\n\t2) Play test game\n\t3) Set skill level\n\t4) List game history");
		if(notsaved==1)printf("\n\t5) Save played game");
		printf("\n\t6) Set language\n\t0) Quit\n\n\tNext command?\n\n");
	}
	scanf("%s",num);                                //Inserción por teclado de la opción y comprobamos que sea una opción válida 
	if(strlen(num)!=1) num[0]='9';
	if((notsaved==0)&&(num[0]=='5'))num[0]='9';
	switch(num[0])
		{
		case '1':                                   //Lanzamos la función de jugar partida, en caso de existir partida por guardar invocamos la función confirmar para
			if(notsaved==1){                        //saber si el usuario quiere guardar la partida o descartarla
				if(confirmar(idioma,1)==0)break;
			}
			jugarpartida(try,1,idioma,bienc,regc,malc);
			notsaved=1;
			break;

		case '2':                                   //Lo mismo pero con una partida de prueba con número secreto=1234
			if(notsaved==1){
				if(confirmar(idioma,1)==0)break;
			}
			jugarpartida(try,2,idioma,bienc,regc,malc);
			notsaved=1;
			break;

		case '3':                                   //Lanzamos la función para establecer el nivel de dificultad (número de intentos máximos)
			do{
				y=establecernivel(&try,idioma);
			}while(y==0);	
			break;

		case '4': listarpartidas(idioma); break;    //Lanzamos la función listarpartidas para mostrar el historial guardado en txt partidas.txt 

		case '5': notsaved=guardarpartida(idioma);break;    //En caso de existir partida sin guardar, lanzamos la función para guardar la última partida en el historial
		case '6': idioma=estableceridioma(idioma);break;    //Lanzamos función de cambio de idioma       

		case '0': if(notsaved==1){                          //Si se invoca la opción 0 y no existe ninguna partida sin guardar se sale, sino se lanza la función confirmar
				if(confirmar(idioma,0)==0)num[0]='o';       //en la cual el usuario puede elegir si volver al menu o salir sin guardar y descartar la partida
			  }
			  break;

		default:  if(idioma==1)printf("\n\t- Has realizado una selección no válida\n");
			  if(idioma==2)printf("\n\t- Realizaches unha selección non válida\n");
			  if(idioma==3)printf("\n\t- You have made an invalid selection\n");
			break;
		}
	}
	remove("aux.txt");					//Eliminamos el fichero auxiliar en el que guardamos las partidas
	system("clear");
	return 0;
}
