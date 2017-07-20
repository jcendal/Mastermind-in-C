#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gestion_juego.h"
#include "pantalla.h"



void jugarpartida(int try,int modo, int idioma,int bienc,int regc,int malc)
{	
	int x,s,j,ast,barra,a,resO,repe,m=4;
	float nota;
	char aux[m],num[m],prueba[m];
	FILE *txt;
	if((txt=fopen("aux.txt","w"))==NULL){
		if(idioma==1)printf("\nNo puedo escribir el fichero de historial\n\n");
		if(idioma==2)printf("\nNon podo escribir no ficheiro de historial\n\n");
		if(idioma==3)printf("\nHistory file can't be written\n\n");
		return;	//Abrimos el fichero auxiliar que nos ayudará a guardar partidas
	}
	fprintf(txt,"%s","------------\n");
	srand(time(NULL));
	if(modo==1){                                        //JUGAR PARTIDA
		do{                                             //generación del número aleatorio y llamada a la función para comprobar que no se repitan enteros
			repe=0;
			a=rand()%9755+122;
			sprintf(aux,"%.4d",a);
			repe=comprobarcadenas(aux,aux);
		}while(repe!=0);	                            //si el número no es correcto se genera otro y lo volvemos a comprobar
	}
	if(modo==2){
		strcpy(aux,"1234");                             //JUGAR PARTIDA DE PRUEBA
	}                                                   //número secreto 1234

		fprintf(txt,"%s",aux);	

	for(j=0;j<try;j++){                                 	                                            
		nota=10.00-10.00*(j-2.00)/9.00;                 //ecuación para el cálculo de puntuación
		if(j<3)nota=10;
		if(j>10)nota=0;
		if(idioma==1)printf("\nEscriba un número de 4 dígitos diferentes + ENTER:\t");
		if(idioma==2)printf("\nEscriba un número de 4 díxitos diferentes + ENTER:\t");
		if(idioma==3)printf("\nType a number with 4 different digits + ENTER:\t");
		scanf("%s",prueba);
		strcpy(num,aux);		
		if(strlen(prueba)!=4){                          //Comprobación de la longitud del string prueba
			if(idioma==1)printf("\nLa longitud de la apuesta es incorrecta\n");
			if(idioma==2)printf("\nA lonxitude da aposta é incorrecta\n");
			if(idioma==3)printf("\nYou have not typed 4 digits\n");
			while(getchar()!='\n');                     //Debido a problemas a la hora de representar contenido por pantalla añadimos este getchar
			setbuf(stdin,NULL);                         //y vaciamos el buffer de entrada
			j--;
			continue;
		}
		x=0;
		for(s=0;s<4;s++){
			if((prueba[s]<'0')||(prueba[s]>'9')){           //Comprobamos que el string solo contenga números enteros de 0 a 9
				if(x!=1){
					if(idioma==1)printf("\nLa apuesta solo debe contener dígitos\n");
					if(idioma==2)printf("\nA aposta só debe conter díxitos\n");
					if(idioma==3)printf("\nThe guess can only contain digits\n");
					j--;
					x=1;
				}
			}
		}
		if(x==1)continue;
		if(comprobarcadenas(prueba,prueba)!=0){             //Comprobamos que no existan enteros repetidos en el string
		j--;
			if(idioma==1)printf("\nLos dígitos de la apuesta deben ser diferentes\n");
			if(idioma==2)printf("\nOs díxitos da aposta deben ser diferentes\n");
			if(idioma==3)printf("\nThe guess digits must be different\n");
			continue;
		}
		if(idioma==1)printf("\nSu apuesta es: ");
		if(idioma==2)printf("\nA súa aposta é: ");
		if(idioma==3)printf("\nYour guess: ");
		printf("%c[%d;%dm%s\t<%c[%dm",27,1,37,prueba,27,0);    //Realce en negrita de la apuesta
		fprintf(txt,"\n%s\t<",prueba);
		ast=0;
		resO=0;
		for(s=0;s<4;s++){
			if(prueba[s]==num[s]){  //Comprobamos los enteros iguales en las mismas posiciones
				printf("%c[%d;%dm*%c[%dm",27,1,bienc,27,0);  //Cambio color: 1(negrita),31(color),0(ajustar a color de fondo)
				fprintf(txt,"*");
				ast++;
			}
		}
		barra=comprobarcadenas(prueba,num); //Calculamos en número de enteros iguales en diferentes posiciones y lo guardamos en barra
		for(s=0;s<barra;s++){
		    printf("%c[%d;%dm|%c[%dm",27,1,regc,27,0);  //Cambio color: 1(negrita),34(color),0(ajustar a color de fondo)
			fprintf(txt,"|");
		}
		for(s=0;s<4-ast-barra;s++){                         //Teniendo 4 enteros en el string restamos los que hemos acertado en las posiciones correctas e incorrectas 
			printf("%c[%d;%dm_%c[%dm",27,1,malc,27,0);      //y tenemos el número de enteros no acertados
			fprintf(txt,"_");
		}
		printf(">\n\n");
		fprintf(txt,">");
		if(ast==4){                                         //Si acertamos todos en sus posiciones (4 asteriscos) imprimimos en pantalla la siguiente información
			if(idioma==1)printf("Ha descubierto el código secreto ");
			if(idioma==2)printf("Descubriu o código secreto ");
			if(idioma==3)printf("You have discovered the secret code ");
			printf("(%c[%d;%dm%s%c[%dm)",27,1,32,num,27,0); 
			if(j==0){
				if(nota>=5){                                //Simplemente cambiamos el color de los intentos en función de si apruebas o suspendes(verde o rojo)
					if(idioma!=3)printf(" en %c[%d;%dm1%c[%dm intento\n",27,1,32,27,0);
					if(idioma==3)printf(" in %c[%d;%dm1%c[%dm attempt\n",27,1,32,27,0);
				}
				if(nota<5){
					if(idioma!=3)printf(" en %c[%d;%dm1%c[%dm intento\n",27,1,31,27,0);
					if(idioma==3)printf(" in %c[%d;%dm1%c[%dm attempt\n",27,1,31,27,0);
				}
			}else {
				if(nota>=5){
					if(idioma!=3)printf(" en %c[%d;%dm%d%c[%dm intentos\n",27,1,32,j+1,27,0);
					if(idioma==3)printf(" in %c[%d;%dm%d%c[%dm attempts\n",27,1,32,j+1,27,0);
				}
				if(nota<5){
					if(idioma!=3)printf(" en %c[%d;%dm%d%c[%dm intentos\n",27,1,31,j+1,27,0);
					if(idioma==3)printf(" in %c[%d;%dm%d%c[%dm attempts\n",27,1,31,j+1,27,0);
				}			
			}
			if(idioma==1)printf("Ha obtenido ");
			if(idioma==2)printf("Obtivo ");
			if(idioma==3)printf("You have got ");
			if(nota>=5)printf("%c[%d;%dm%.2f%c[%dm",27,1,32,nota,27,0);  //Verde si apuebas y rojo si suspendes
			if(nota<5)printf("%c[%d;%dm%.2f%c[%dm",27,1,31,nota,27,0);
			if(idioma!=3)printf(" puntos\n\n");
			if(idioma==3)printf(" points\n\n");
			fprintf(txt,"\n%d\n%.2f\n",j+1,nota);
			getchar();
			fclose(txt);			
			return;
		}
	}
	if(idioma==1)printf("NO ha descubierto el código secreto ");
	if(idioma==2)printf("NON descubriu o código secreto ");
	if(idioma==3)printf("You have FAILED to discover the secret code ");
	printf("(%c[%d;%dm%s%c[%dm)",27,1,32,num,27,0);
	if(try==1){ 
		if(idioma!=3)printf(" tras %c[%d;%dm1%c[%dm intento\n",27,1,31,27,0);
		if(idioma==3)printf(" after %c[%d;%dm1%c[%dm attempt\n",27,1,31,27,0);
	}
	else {
		if(idioma!=3)printf(" en %c[%d;%dm%d%c[%dm intentos\n",27,1,31,try,27,0);
		if(idioma==3)printf(" after %c[%d;%dm%d%c[%dm attemts\n",27,1,31,try,27,0);
	}
	if(idioma==1)printf("Ha obtenido ");
	if(idioma==2)printf("Obtivo ");
	if(idioma==3)printf("You have got ");
	printf("%c[%d;%dm0.00%c[%dm",27,1,31,27,0);
	if(idioma!=3)printf(" puntos\n\n");
	if(idioma==3)printf(" points\n\n");
	fprintf(txt,"\n%d\n0.00\n",try);
	getchar();
	fclose(txt);
	return;
}

int establecernivel(int *try, int idioma)               //Aquí se modifica el número máximo de intentos
{
	int a,i,k;
	char m;
	do{	
		i=0;a=0,k=1;
		if(idioma==1)printf("\n\tNivel actual:\t%d\n\tElige nuevo nivel [1..100]:\t",*try);
		if(idioma==2)printf("\n\tNivel actual:\t%d\n\tElixe novo nivel [1..100]:\t",*try);
		if(idioma==3)printf("\n\tCurrent level:\t%d\n\tSelect new level [1..100]:\t",*try);
		scanf("%d",&a);
		m=getchar();

		if(m!='\n')i=1;
		if((i==1)||(a<1)||(a>100)||(a==0)){         //Comprobamos que no se introduzca ningún caracter ni que el número esté fuera del rango
			if(i==1)while(getchar()!='\n');             
			if(idioma==1)printf("\tNivel seleccionado no válido");
			if(idioma==2)printf("\tNivel seleccionado non válido");
			if(idioma==3)printf("\tYou have selected an unvalid level");
			k=0;
			break;
		}else{
			if(idioma!=3)printf("\n\tNivel seleccionado:\t%d\n\n",a);
			if(idioma==3)printf("\n\tSelected level:\t%d\n\n",a);
			*try=a;                                 //Retornamos el nuevo número de intentos 
			break;
		}
	}while(1);

	return k;
}

void listarpartidas(int idioma)
{
	FILE *txt;
	char c;

	if((txt=fopen("partidas.txt","r"))==NULL){          //Comprobamos que exista el fichero para poder leerse
		if(idioma==1)printf("\nNo puedo leer el fichero el fichero del historial\n\n");
		if(idioma==2)printf("\nNon podo ler o ficheiro de historial\n\n");
		if(idioma==3)printf("\nHistory file can't be read\n\n");
	}else{
		c=fgetc(txt);                                   //Leemos caracter
		while(c!=EOF){                                  //Comprobamos si llegamos al final del fichero, si no llegamos, imprimimos en pantalla el caracter leído y leemos
			printf("%c",c);                             //el siguiente        
			c=fgetc(txt);
		}
		fclose(txt);
	}
	return;
}

int comprobarcadenas(char cad1[],char cad2[])               //Comprobamos valores de las cadenas posición a posición exceptuando las posiciones iguales
{
	int ret=0;

	if((cad1[0]==cad2[1])||(cad1[0]==cad2[2])||(cad1[0]==cad2[3])){
		ret++;
	}
	if((cad1[1]==cad2[0])||(cad1[1]==cad2[2])||(cad1[1]==cad2[3])){
		ret++;
	}
	if((cad1[2]==cad2[0])||(cad1[2]==cad2[1])||(cad1[2]==cad2[3])){
		ret++;
	}
	if((cad1[3]==cad2[0])||(cad1[3]==cad2[1])||(cad1[3]==cad2[2])){
		ret++;
	}
	return ret;                                             //Utilizaremos ret para saber el número de barras que necesitamos imprimir 
}

int estableceridioma(int idioma)                            //Función para establecer el idioma deseado
{
	char num[20];
	do{
		if(idioma==1)printf("\n\t0) Español\n\t1) Gallego\n\t2) Inglés\n\n\tElige idioma: ");
		if(idioma==2)printf("\n\t0) Español\n\t1) Galego\n\t2) Inglés\n\n\tElixe idioma: ");
		if(idioma==3)printf("\n\t0) Spanish\n\t1) Galician\n\t2) English\n\n\tSelect language: ");
		scanf("%s",num);
		if(strlen(num)!=1)num[0]=3;                         //Comprobamos que el string contenga solo un valor(solo una posición ocupada).
		switch(num[0]){
			case '0':printf("\n\tNuevo idioma: Español\n");return 1;
			case '1':printf("\n\tNovo idioma: Galego\n");return 2;
			case '2':printf("\n\tNew idiom: English\n");return 3;
			default: if(idioma==1)printf("\n\tIdioma seleccionado no válido\n");
				 if(idioma==2)printf("\n\tIdioma seleccionado non válido\n");
				 if(idioma==3)printf("\n\tSelected language is not allowed\n");
				 break;
		}
	}while(1);
}

int guardarpartida(int idioma)
{	
	char c;
	FILE *copy,*paste;
	if(((copy=fopen("aux.txt","r"))==NULL)||((paste=fopen("partidas.txt","a"))==NULL)){      //Si no existe nada que leer o nada que escribir imprimimos en pantalla
		if(idioma==1)printf("\nNo puedo escribir el fichero de historial\n\n");              //un mensaje de aviso
		if(idioma==2)printf("\nNon podo escribir no ficheiro de historial\n\n");
		if(idioma==3)printf("\nHistory file can't be written\n\n");
		return 1;
	}else{
		c=fgetc(copy);
		while(c!=EOF){                                                                      //Mientras no llegamos a final de fichero pasamos los datos de aux.txt a
			fputc(c,paste);                                                                 //partidas.txt
			c=fgetc(copy);
		}

		fclose(copy);                                                                       //Cerramos los ficheros y borramos en fichero auxiliar
		fclose(paste);
		remove("aux.txt");
	}

	return 0;
}
