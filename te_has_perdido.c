#include<stdio.h>
#include <stdbool.h>

int laberintos(void);
void laberinto1(int salida[]);
void laberinto2(int salida[]);
void laberinto3(int salida[]);
//int registrarse_iniciarsesion(void);
void estadisticas(void);
int menu_salir(void);
void moverse(char matriz[][100], int *fila, int *columna);

//menu principal
int main()
{
    int tecla_menu, tecla_menu_salir, tecla_laberintos, tecla_volverajugar;
    int numero_movimientos=0;
    int posicion[2]; //posicion del jugador
    int salida_laberinto[2]; //punto del laberinto en el que se encuentra la salida, no lo conoce el usuario,
                            //solo el programador
    FILE *pLaberinto1, *pLaberinto2, *pLaberinto3;
    char matriz_laberinto[20][100];
    char matriz_laberinto1[20][100], matriz_laberinto2[20][100], matriz_laberinto3[20][100];//matrices de caracteres para almacenar
    int fila=0, columna=0;

    //ABRIMOS FICHERO laberinto1 E INTRODUCIMOS LOS CARACTERES EN LA matriz_laberinto1
    pLaberinto1=fopen("lab.txt", "r");
    if(pLaberinto1==NULL)
    {
         printf("Error al abrir fichero\n");
         return -1;
    }
    else
    {
        while(fscanf(pLaberinto1, "%c", &matriz_laberinto1[fila][columna])!=EOF)//guardar laberinto en una matriz
        {
            columna++;
            if(columna==100)
            {
                fila++;
                columna=0;
            }
        }
        columna=0, fila=0;
        fclose(pLaberinto1);
    }

    do
    {
        printf("\t\t                                       |------------|\n");
        printf("\t\t                                       | Bienvenido |\n");
        printf("\t\t                                       |------------|\n\n\n\n");
        printf("\t\t  |-------------------------------|                     |------------------------|\n");
        printf("\t\t  | Registrarse o iniciar sesion  |                     | Estadisticas jugadores |\n");
        printf("\t\t  |              (1)              |                     |            (2)         |\n");
        printf("\t\t  |-------------------------------|                     |------------------------|\n\n\n\n\n\n\n");
        printf("\t\t\t                                                                  |----------|\n");
        printf("\t\t\t                                                                  | Salir(0) |\n");
        printf("\t\t\t                                                                  |----------|\n\n\n");
        do
        {
            fflush(stdin);   //funcion para que no se sature el scanf
            scanf("%i", &tecla_menu);
            if((tecla_menu!=1)&&(tecla_menu!=2)&&(tecla_menu!=0))
                printf("Tecla incorrecta\n");
        }
        while((tecla_menu!=1)&&(tecla_menu!=2)&&(tecla_menu!=0));

        switch(tecla_menu)
        {
        case 1:
            //salida_registrarse_iniciarsesion=registrarse_iniciarsesion();
            //if(salida_registrarse_iniciarsesion==1)  //si devuelve un 1 se ha registrado/iniciado sesion correctamente
            //{
                do
                {
                    tecla_laberintos=laberintos();
                    switch(tecla_laberintos)
                    {
                    case 1:
                        laberinto1(salida_laberinto);//Inserto en el vector salida_laberinto la salida del laberinto 1
                        for(fila=0; fila<20; fila++) //Igualo los elementos de la matriz_laberinto1 a mi matriz generica
                        {                            //para poder trabajar con ella
                            for(columna=0; columna<100; columna++)
                            {
                                matriz_laberinto[fila][columna]=matriz_laberinto1[fila][columna];
                            }
                        }
                        break;
                    case 2:
                        laberinto2(salida_laberinto);//Dibujo laberinto 2 e inserto en el vector salida_laberinto
                        break;                       //la salida del laberinto 2
                    case 3:
                        laberinto3(salida_laberinto);//Dibujo laberinto 3 e inserto en el vector salida_laberinto
                        break;                       //la salida del laberinto 3
                    }
                    do//pedimos coordenadas iniciales
                    {
                        printf("Introduzca su posicion inicial (fila>0, columna>0): ");
                        scanf("%i %i", &posicion[0], &posicion[1]);//fila y columna en la que quiero estar
                        fflush(stdin);

                        if((posicion[0]>=20)||(posicion[0]<0)||(posicion[1]>=100)||(posicion[1]<0))
                        {
                            printf("Esa posicion se encuentra fuera del laberinto\n\n");
                        }
                        else if((matriz_laberinto[posicion[0]][posicion[1]]!=' ')&&(matriz_laberinto[posicion[0]][posicion[1]]!='?')&&
                                                                                    (matriz_laberinto[posicion[0]][posicion[1]]!='S'))
                        {
                            printf("Esa posicion es una pared\n");
                        }
                    }
                    while(posicion[0]>=20||(posicion[0]<0)||(posicion[1]>=100)||(posicion[1]<0)||
                          ((matriz_laberinto[posicion[0]][posicion[1]]!=' ')&&(matriz_laberinto[posicion[0]][posicion[1]]!='?')
                                                                             &&(matriz_laberinto[posicion[0]][posicion[1]]!='S')));
                    //si la posicion elegida es una pared o se encuentra fuera del laberinto se vuelven a pedir coordenadas

                    matriz_laberinto[posicion[0]][posicion[1]]='X';//Marcamos con una X nuestro posicion actual
                                                                   //La X va a ser nuestro cursor
                    //Aqui ira el dibujo de la zona del laberinto donde estamos
                    for(fila=posicion[0]-8; fila<=posicion[0]+8; fila++)//las interrogaciones son pistas
                    {
                        printf("\t\t\t\t\t");
                        for(columna=posicion[1]-8; columna<=posicion[1]+8; columna++)
                        {
                            if((fila>=0)&&(fila<20)&&(columna>=0)&&(columna<100)) //para que no se impriman caracteres aleatorios
                                printf("%c", matriz_laberinto[fila][columna]);    //que estan fuera del laberinto
                        }
                        printf("\n");
                    }

                    while((posicion[0]!=salida_laberinto[0])||(posicion[1]!=salida_laberinto[1]))//Si acierto a la primera
                    {                                                                            //no pide que me mueva
                        moverse(matriz_laberinto, &posicion[0], &posicion[1]);//mediante el bucle while repito la funcion
                                                                              //moverse hasta que encuentre la salida
                        //Aqui ira el dibujo de la zona del laberinto donde estamos
                        for(fila=posicion[0]-8; fila<=posicion[0]+8; fila++)//las interrogaciones son pistas
                        {
                            printf("\t\t\t\t\t");
                            for(columna=posicion[1]-8; columna<=posicion[1]+8; columna++)
                            {
                                if((fila>=0)&&(fila<20)&&(columna>=0)&&(columna<100))
                                    printf("%c", matriz_laberinto[fila][columna]);
                            }
                            printf("\n");
                        }
                        printf("\nfila: %i columna: %i\n", posicion[0], posicion[1]);//coordenadas(fila, columna)
                        numero_movimientos++;                                        // del punto actual
                    }
                    printf("\n\n\nEncontraste la salida!!\n\n\n");
                    printf("Numero de movimientos: %i\n\n", numero_movimientos);
                    numero_movimientos=0;//se resetea el numero de movimientos una vez hemos terminado de jugar
                    printf("\t\t                          ~~~~~~~Desea volver a jugar?~~~~~~~\n");//si desea volver a jugar
                    printf("\t\t                             ~~~~~~~Si(1)    No(0)~~~~~~~\n\n\n");//volvemos al menu de laberintos
                    do                                                                            //si no desea volver a jugar
                    {                                                                             //tenemos la opcion de menu o salir.
                        scanf("%i", &tecla_volverajugar);
                        fflush(stdin); //funcion para que no se sature el scanf
                        if((tecla_volverajugar!=1)&&(tecla_volverajugar!=0))
                            printf("Tecla incorrecta\n");
                    }
                    while((tecla_volverajugar!=1)&&(tecla_volverajugar!=0));
                }
                while(tecla_volverajugar!=0);
            //}
            tecla_menu_salir=menu_salir();
            break;
        case 2:
            //estadisticas();
            tecla_menu_salir=menu_salir();
            break;
        }
    }
    while((tecla_menu!=0)&&(tecla_menu_salir!=0));
    printf("\n\n\nHasta luego!!\n");
    return 0;
}
//Menu laberintos
int laberintos(void)
{
    int tecla_laberintos;
    printf("\t\t  |-----------------|               |-----------------|            |-----------------|\n");
    printf("\t\t  | Laberinto 1 (1) |               | Laberinto 2 (2) |            | Laberinto 3 (3) |\n");
    printf("\t\t  |-----------------|               |-----------------|            |-----------------|\n\n\n\n\n\n\n");
    do
    {
        scanf("%i", &tecla_laberintos);
        fflush(stdin);   //funcion para que no se sature el scanf
        if((tecla_laberintos!=1)&&(tecla_laberintos!=2)&&(tecla_laberintos!=3))
            printf("Tecla incorrecta\n");
    }
    while((tecla_laberintos!=1)&&(tecla_laberintos!=2)&&(tecla_laberintos!=3));
    return tecla_laberintos;
}
//laberinto 1
void laberinto1(int salida[])
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 1~~~~~~~~~~~~~~~\n\n\n");
    salida[0]=18;
    salida[1]=98;               //coordenadas salida laberinto 1
}
//laberinto 2
void laberinto2(int salida[])
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 2~~~~~~~~~~~~~~~\n\n\n");
    salida[0]=120;
    salida[1]=20;              //coordenadas salida laberinto 2
}
//laberinto 3
void laberinto3(int salida[])
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 3~~~~~~~~~~~~~~~\n\n\n");
    salida[0]=80;
    salida[1]=20;              //coordenadas salida laberinto 3
}
//opcion menu-salir
int menu_salir(void)
{
    int tecla;
    printf("\n\n\n\t\t                         ~~Menu(1)~~              ~~Salir(0)~~\n\n\n");
    do
    {
        fflush(stdin); //funcion para que no se sature el scanf
        scanf("%i", &tecla);
        if((tecla!=1)&&(tecla!=0))
            printf("Tecla incorrecta\n");
    }
    while((tecla!=1)&&(tecla!=0));
    return tecla;
}

//Funcion para movernos por el laberinto
void moverse(char matriz[][100], int *fila, int *columna) //funcion para moverse por el laberinto, en la que vamos a
{                                                         //introducir como argumentos nuestra matriz_laberinto y la
    int i;
    char tecla;
    char auxiliar;
    printf("\nMuevete por el laberinto.\n");
    do
    {
        fflush(stdin); //funcion para que no se sature el scanf
        scanf("%c", &tecla);
        if((tecla!='w')&&(tecla!='W')&&(tecla!='a')&&(tecla!='A')&&(tecla!='d')&&(tecla!='D')&&(tecla!='s')&&(tecla!='S'))
        {
           printf("Tecla incorrecta\n");
        }

    }
    while((tecla!='w')&&(tecla!='W')&&(tecla!='a')&&(tecla!='A')&&(tecla!='d')&&(tecla!='D')&&(tecla!='s')&&(tecla!='S'));

    switch(tecla)
    {
    case 'w': //moverse una posicion hacia arriba
        if(matriz[*fila-1][*columna] == ' ')
        {
            auxiliar=matriz[*fila][*columna];      //Nuestro punto actual se intercambia con el punto que esta encima de el
            matriz[*fila][*columna]=matriz[*fila-1][*columna];
            matriz[*fila-1][*columna]=auxiliar;
            *fila=*fila-1;
        }
        else if(matriz[*fila-1][*columna] == '?')
        {
            printf("Pista: La salida esta hacia la derecha\n");
            auxiliar=matriz[*fila][*columna];      //Nuestro punto actual se intercambia con el punto que esta encima de el
            matriz[*fila][*columna]=matriz[*fila-2][*columna];
            matriz[*fila-2][*columna]=auxiliar;
            *fila=*fila-2;
        }
        else if(matriz[*fila+1][*columna] == 'S')
        {
            printf("Encontraste la salida!!\n");
            auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=' ';
            matriz[*fila-1][*columna]=auxiliar;
            *fila=*fila-1;
        }
        else
        {
            printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
        }
        break;
    case 'W':
        for(i=0; i<5; i++)//Con la mayuscula avanzas 5 posiciones en vez de 1
        {
            if(matriz[*fila-1][*columna] == ' ')
            {
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila-1][*columna];
                matriz[*fila-1][*columna]=auxiliar;
                *fila=*fila-1;
            }
            else if(matriz[*fila-1][*columna] == '?')
            {
                printf("Pista: La salida esta hacia la derecha\n");
                auxiliar=matriz[*fila][*columna];      //Nuestro punto actual se intercambia con el punto que esta encima de el
                matriz[*fila][*columna]=matriz[*fila-2][*columna];
                matriz[*fila-2][*columna]=auxiliar;
                *fila=*fila-2;
            }
            else if(matriz[*fila+1][*columna] == 'S')
            {
                printf("Encontraste la salida!!\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=' ';
                matriz[*fila-1][*columna]=auxiliar;
                *fila=*fila-1;
            }
            else
            {
                printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
                break;
            }
        }
        break;
    case 'd': //moverse una posicion hacia la derecha
        if(matriz[*fila][*columna+1] == ' ')
        {
            auxiliar=matriz[*fila][*columna];     //Nuestro punto actual se intercambia con el punto que esta a su derecha
            matriz[*fila][*columna]=matriz[*fila][*columna+1];
            matriz[*fila][*columna+1]=auxiliar;
            *columna=*columna+1;
        }
        else if(matriz[*fila][*columna+1] == '?')
        {
            printf("Pista: La salida esta hacia la derecha\n");
            auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=matriz[*fila][*columna+2];
            matriz[*fila][*columna+2]=auxiliar;
            *columna=*columna+2;
        }
        else if(matriz[*fila][*columna+1] == 'S')
        {
            printf("Encontraste la salida!!\n");
             auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=' ';
            matriz[*fila][*columna+1]=auxiliar;
            *columna=*columna+1;
        }
        else
        {
            printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
        }
        break;
    case 'D':
        for(i=0; i<5; i++)
        {
            if(matriz[*fila][*columna+1] == ' ')
            {
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna+1];
                matriz[*fila][*columna+1]=auxiliar;
                *columna=*columna+1;
            }
            else if(matriz[*fila][*columna+1] == '?')
            {
                printf("Pista: La salida esta hacia la derecha\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna+2];
                matriz[*fila][*columna+2]=auxiliar;
                *columna=*columna+2;
            }
            else if(matriz[*fila][*columna+1] == 'S')
            {
                printf("Encontraste la salida!!\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=' ';
                matriz[*fila][*columna+1]=auxiliar;
                *columna=*columna+1;
            }else
            {
                printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
                break;
            }
        }
        break;
    case 's': //moverse una posicion hacia abajo
        if(matriz[*fila+1][*columna] == ' ')
        {
            auxiliar=matriz[*fila][*columna];     //Nuestro punto actual se intercambia con el punto que esta debajo
            matriz[*fila][*columna]=matriz[*fila+1][*columna];
            matriz[*fila+1][*columna]=auxiliar;
            *fila=*fila+1;
        }
        else if(matriz[*fila+1][*columna] == '?')
        {
            printf("Pista: La salida esta hacia la derecha\n");
            auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=matriz[*fila+2][*columna];
            matriz[*fila+2][*columna]=auxiliar;
            *fila=*fila+2;
        }
        else if(matriz[*fila+1][*columna] == 'S')
        {
            printf("Encontraste la salida!!\n");
            auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=' ';
            matriz[*fila+1][*columna]=auxiliar;
            *fila=*fila+1;
        }
        else
        {
            printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
        }
        break;
    case 'S':
        for(i=0; i<5; i++)
        {
            if(matriz[*fila+1][*columna] == ' ')
            {
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila+1][*columna];
                matriz[*fila+1][*columna]=auxiliar;
                *fila=*fila+1;
            }
            else if(matriz[*fila+1][*columna] == '?')
            {
                printf("Pista: La salida esta hacia la derecha\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila+2][*columna];
                matriz[*fila+2][*columna]=auxiliar;
                *fila=*fila+2;
            }
            else if(matriz[*fila+1][*columna] == 'S')
            {
                printf("Encontraste la salida!!\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=' ';
                matriz[*fila+1][*columna]=auxiliar;
                *fila=*fila+1;
            }
            else
            {
                printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
                break;
            }
        }
        break;
    case 'a': //moverse una posicion hacia la izquierda
        if(matriz[*fila][*columna-1] == ' ')
        {
            auxiliar=matriz[*fila][*columna];     //Nuestro punto actual se intercambia con el punto que esta a su izquierda
            matriz[*fila][*columna]=matriz[*fila][*columna-1];
            matriz[*fila][*columna-1]=auxiliar;
            *columna=*columna-1;
        }
        else if(matriz[*fila][*columna-1] == '?')
        {
            printf("Pista: La salida esta hacia la derecha\n");
            auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=matriz[*fila][*columna+2];
            matriz[*fila][*columna-2]=auxiliar;
            *columna=*columna-2;
        }
        else if(matriz[*fila][*columna-1] == 'S')
        {
            printf("Encontraste la salida!!\n");
            auxiliar=matriz[*fila][*columna];
            matriz[*fila][*columna]=' ';
            matriz[*fila][*columna-1]=auxiliar;
            *columna=*columna-1;
        }else
        {
            printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
        }
        break;
    case 'A':
        for(i=0; i<5; i++)
        {
            if(matriz[*fila][*columna-1] == ' ')
            {
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna-1];
                matriz[*fila][*columna-1]=auxiliar;
                *columna=*columna-1;
            }
            else if(matriz[*fila][*columna-1] == '?')
            {
                printf("Pista: La salida esta hacia la derecha\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna+2];
                matriz[*fila][*columna-2]=auxiliar;
                *columna=*columna-2;
            }
            else if(matriz[*fila][*columna-1] == 'S')
            {
                printf("Encontraste la salida!!\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=' ';
                matriz[*fila][*columna-1]=auxiliar;
                *columna=*columna-1;
            }else
            {
                printf("Estas chocando contra una pared desplazate hacia otro lugar.\n");
                break;
            }
        }
        break;
    }

}

int registrarse_iniciarsesion(void)
{
    char nombre[20], contrasenna[20];

    printf("Escribe tu nombre y tu contraseña.");
    scanf("%s\n %s", &nombre, &contrasenna);

}
void estadisticas ()
{
	FILE *pf;
	int movimientos[100], contador=0 ,n, numero_movimientos [3] = {0,0,0};
	bool total = 0;
	pf =fopen ("Estadisticas.txt", "r");
	if (pf==NULL)//
	{
		printf ("No hay estadisticas anteriores\n");
		fclose (pf);
		pf = fopen ("Estadisticas.txt", "w");
		fclose (pf);
		system ("pause");
		printf ("\n\n");
		return;
	}
	while (fscanf (pf, "%d", &movimientos[contador]) != EOF)// escanea
	{
		if (contador >= 99)
		{
			contador = 0;
			total = 1;
		}

	}

}

