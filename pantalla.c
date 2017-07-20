#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gestion_juego.h"
#include "pantalla.h"
#define gotoxy(x,y) printf("\x1b[%d;%dH",(y),(x))    


void asteriscos(int n, int l, char c)
{
	system("clear");                                 //Limpiamos la pantalla para evitar problemas con gotoxy
	srand(time(NULL));
	int a,k,ca,cm;                                   //Rand para conseguir tener los colores de forma aleatoria, este valor se lo sumamos a 29 para tener los valores de
	do{                                              //los colores
		ca=29+rand()%7;
		cm=29+rand()%7;
	}while(ca==cm);                                   //Rellenamos con asteriscos y utilizamos usleep para dar dinamismo a la aparición de filas de asteriscos
    for(a=0;a<n;a++){
        for(k=0;k<l;k++)
			printf("%c[%d;%dm%c%c[%dm",27,4,ca,c,27,0);
			printf("\n");
			usleep(300000);
		}
	if((l%2!=0)&&(l>13))printf("%c[%d;%dm%c%c[%dm",27,4,ca,c,27,0);
	for(a=0;a<l/2-7;a++) printf("%c[%d;%dm%c%c[%dm",27,4,ca,c,27,0);
	printf("%c[%d;%dm             %c[%dm",27,1,32,27,0);
   
	for(a=0;a<=l/2-7;a++)printf("%c[%d;%dm%c%c[%dm",27,4,ca,c,27,0);
	printf("\n");
	usleep(300000);
	for(a=0;a<n;a++){
		for(k=0;k<l;k++)
			printf("%c[%d;%dm%c%c[%dm",27,4,ca,c,27,0);
		printf("\n");
		usleep(300000);
	}	
	usleep(500000);
	gotoxy(35, 4);printf("%c[%d;%dmMASTER MIND%c[%dm",27,1,cm,27,0);   //Para imprimir MASTER MIND en la posición deseada
	gotoxy(0,7);
	return;
}

int confirmar(int idioma,int jop)
{ 
	char res[5];
	int i;
	do{
		if(jop==0){             //En caso de seleccionar salir con partida sin guardar
			if(idioma==1)printf("\nHay una partida sin guardar, ¿está seguro de que desea salir? (s/n)?\n");
			if(idioma==2)printf("\nHai unha partida sen gardar, está seguro de que desexa saír? (s/n)?\n");
			if(idioma==3)printf("\nThere is an unsaved game, are you sure you want to quit? (s/n)?\n");
		}
		if(jop==1){             //En caso de seleccionar jugar partida con una ya existente sin guardar
			if(idioma==1)printf("\nHay una partida sin guardar, ¿descartarla? (s/n)?\n");
			if(idioma==2)printf("\nHay unha partida sen gardar, descartala? (s/n)?\n");
			if(idioma==3)printf("\nThere is an unsaaved game, discard it? (s/n)?\n");
		}
		scanf("%s",res);                //Comprobamos si el valor introducido se corresponde con una sola posición en el string, sino el switch devolverá -1 y se volverá a
		if(strlen(res)!=1)res[0]='t';   //pedir una respuesta válida
		
		switch(res[0]){
			case 's':case 'S': return 1;
			case 'n':case 'N': return 0;
			default: i=-1;
		}
	}while(i==-1);
	return 0;
}

