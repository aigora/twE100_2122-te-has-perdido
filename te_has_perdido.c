#include<stdio.h>

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
    FILE *pLaberinto;
    char matriz_laberinto[8][100]; //matriz de caracteres para almacenar los laberintos que escaneemos
    int fila=0, columna=0;

    //abrimos fichero laberinto e introducimos los caracteres en una matriz
    pLaberinto=fopen("lab.txt", "r");
    while(fscanf(pLaberinto, "%c", &matriz_laberinto[fila][columna])!=EOF)//guardar laberinto en una matriz
    {
        if(matriz_laberinto[fila][columna]=='\n')
        {
            fila++;
            columna=0;
        }
        else
            columna++;

    }
    fclose(pLaberinto);
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
            scanf("%i", &tecla_menu);
            fflush(stdin);   //funcion para que no se sature el scanf
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
                        laberinto1(salida_laberinto);//Dibujo laberinto 1 e inserto en el vector salida_laberinto
                        break;                       //la salida del laberinto 1
                    case 2:
                        laberinto2(salida_laberinto);//Dibujo laberinto 2 e inserto en el vector salida_laberinto
                        break;                       //la salida del laberinto 2
                    case 3:
                        laberinto3(salida_laberinto);//Dibujo laberinto 3 e inserto en el vector salida_laberinto
                        break;                       //la salida del laberinto 3
                    }
                    do //pedimos coordenadas iniciales
                    {
                        printf("Introduzca las coordenadas de su posicion inicial (X>0 Y>0): ");
                        scanf("%i %i", &posicion[0], &posicion[1]);//fila y columna en la que quiero estar
                        if((posicion[0]>=8)||(posicion[0]<0)||(posicion[1]>=100)||(posicion[1]<0))
                        {
                            printf("Esa posicion se encuentra fuera del laberinto\n\n");
                        }
                    }
                    while((posicion[0]>=8)||(posicion[0]<0)||(posicion[1]>=100)||(posicion[1]<0));

                    matriz_laberinto[posicion[0]][posicion[1]]='X';//Marcamos con una X nuestro posicion actual
                                                                   //La X va a ser nuestro cursor
                    //Aqui ira el dibujo de la zona del laberinto donde estamos
                    for(fila=0; fila<8; fila++)
                    {
                        for(columna=0; columna<100; columna++)//las interrogaciones son pistas
                        {
                            printf("%c", matriz_laberinto[fila][columna]);
                        }
                    }

                    while((posicion[0]!=salida_laberinto[0])||(posicion[1]!=salida_laberinto[1]))//Si acierto a la primera
                    {                                                                            //no pide que me mueva
                        moverse(matriz_laberinto, &posicion[0], &posicion[1]);//mediante el bucle while repito la funcion moverse hasta que encuentre la salida
                        for(fila=0; fila<8; fila++) //Aqui ira el dibujo de la zona del laberinto donde estamos
                        {
                            for(columna=0; columna<100; columna++)
                            {
                                printf("%c", matriz_laberinto[fila][columna]);
                            }
                        }
                        printf("\nfila: %i columna: %i\n", posicion[0], posicion[1]);//coordenadas(fila, columna) del punto actual
                        numero_movimientos++;
                    }
                    printf("\n\n\nEncontraste la salida!!\n\n\n");
                    printf("Numero de movimientos: %i\n\n", numero_movimientos);
                    numero_movimientos=0;//se resetea el numero de movimientos una vez hemos terminado de jugar
                    printf("\t\t                          ~~~~~~~Desea volver a jugar?~~~~~~~\n");//si desea volver a jugar
                    printf("\t\t                             ~~~~~~~Si(1)    No(0)~~~~~~~\n\n\n");//volvemos al menu de laberintos
                    do                                                                            //si no desea volver a jugar
                    {                                                                             //tenemos la opcion de menu o salir.
                        fflush(stdin); //funcion para que no se sature el scanf
                        scanf("%i", &tecla_volverajugar);
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
    }
    while((tecla_laberintos!=1)&&(tecla_laberintos!=2)&&(tecla_laberintos!=3));
    return tecla_laberintos;
}
//laberinto 1
void laberinto1(int salida[])
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 1~~~~~~~~~~~~~~~\n\n\n");
    salida[0]=6;
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
    scanf(" %c", &tecla);
    switch(tecla)
    {
    case 'w': //moverse una posicion hacia arriba
        auxiliar=matriz[*fila][*columna];      //Nuestro punto actual se intercambia con el punto que esta encima de el
        matriz[*fila][*columna]=matriz[*fila-1][*columna];
        matriz[*fila-1][*columna]=auxiliar;
        *fila=*fila-1;
        break;
    case 'W':
        for(i=0; i<5; i++)//Con la mayuscula avanzas 5 posiciones en vez de 1
        {
        auxiliar=matriz[*fila][*columna];
        matriz[*fila][*columna]=matriz[*fila-1][*columna];
        matriz[*fila-1][*columna]=auxiliar;
        *fila=*fila-1;
        }
        break;
    case 'd': //moverse una posicion hacia la derecha
        auxiliar=matriz[*fila][*columna];     //Nuestro punto actual se intercambia con el punto que esta a su derecha
        matriz[*fila][*columna]=matriz[*fila][*columna+1];
        matriz[*fila][*columna+1]=auxiliar;
        *columna=*columna+1;
        break;
    case 'D':
        for(i=0; i<5; i++)
        {
        auxiliar=matriz[*fila][*columna];
        matriz[*fila][*columna]=matriz[*fila][*columna+1];
        matriz[*fila][*columna+1]=auxiliar;
        *columna=*columna+1;
        }
        break;
    case 's': //moverse una posicion hacia abajo
        auxiliar=matriz[*fila][*columna];     //Nuestro punto actual se intercambia con el punto que esta debajo
        matriz[*fila][*columna]=matriz[*fila+1][*columna];
        matriz[*fila+1][*columna]=auxiliar;
        *fila=*fila+1;
        break;
    case 'S':
        for(i=0; i<5; i++)
        {
        auxiliar=matriz[*fila][*columna];
        matriz[*fila][*columna]=matriz[*fila+1][*columna];
        matriz[*fila+1][*columna]=auxiliar;
        *fila=*fila+1;
        }
        break;
    case 'a': //moverse una posicion hacia la izquierda
        auxiliar=matriz[*fila][*columna];     //Nuestro punto actual se intercambia con el punto que esta a su izquierda
        matriz[*fila][*columna]=matriz[*fila][*columna-1];
        matriz[*fila][*columna-1]=auxiliar;
        *columna=*columna-1;
        break;
    case 'A':
         for(i=0; i<5; i++)
         {
        auxiliar=matriz[*fila][*columna];
        matriz[*fila][*columna]=matriz[*fila][*columna-1];
        matriz[*fila][*columna-1]=auxiliar;
        *columna=*columna-1;
         }
        break;
    }

}

int registrarse_iniciarsesion(void)
{
    char nombre[20], contrasenna[20];

    printf("Escribe tu nombre y tu contraseņa.");
    scanf("%s\n %s", &nombre, &contrasenna);

}
