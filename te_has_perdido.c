#include<stdio.h>
#include<string.h>

int laberintos(void);
void laberinto1(int salida[]);
void laberinto2(int salida[]);
void laberinto3(int salida[]);
int registrarse_iniciarsesion(char contra[]);
void estadisticas(void);
int menu_salir(void);
int moverse(char matriz[][100], int *fila, int *columna);
void informacion(void);


typedef struct //estructura jugador que almacena su nombre, contrasenha y
{              //movimientos en cada laberinto
    char nombre[20], contrasenna[20];
    int movimientos_laberinto1;
    int movimientos_laberinto2;
    int movimientos_laberinto3;
}jugador;


//menu principal
int main()
{
    jugador datos_jugador[100]; //vector de estructuras que almacena los datos de todos los jugadores
    FILE *pEstadisticas;
    int num_jugador=0, i=0, se_cumple, total_jugadores;
    char nombre[20], contrasenha[20];
    int contra;

    int tecla_menu, tecla_menu_salir, tecla_laberintos, tecla_volverajugar, tecla_moverse;
    int numero_movimientos=0;
    int posicion[2]; //posicion del jugador
    int salida_laberinto[2]; //punto del laberinto en el que se encuentra la salida, no lo conoce el usuario,
                            //solo el programador
    FILE *pLaberinto1, *pLaberinto2, *pLaberinto3;
    char matriz_laberinto[40][100];
    char matriz_laberinto1[40][100], matriz_laberinto2[40][100], matriz_laberinto3[40][100];//matrices de caracteres para almacenar
    int fila=0, columna=0;

    //ABRIMOS FICHERO laberinto1 E INTRODUCIMOS LOS CARACTERES EN LA matriz_laberinto1
    pLaberinto1=fopen("laberinto1.txt", "r");
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

    //ABRIMOS FICHERO Laberinto2 E INTRODUCIMOS LOS CARACTERES EN LA matriz_laberinto2
    pLaberinto2=fopen("laberinto2.txt", "r");
    if(pLaberinto2==NULL)
    {
         printf("Error al abrir fichero\n");
         return -2;
    }
    else
    {
        while(fscanf(pLaberinto2, "%c", &matriz_laberinto2[fila][columna])!=EOF)//guardar laberinto en una matriz
        {
            columna++;
            if(columna==100)
            {
                fila++;
                columna=0;
            }
        }
        columna=0, fila=0;
        fclose(pLaberinto2);
    }
    //ABRIMOS FICHERO Laberinto3 E INTRODUCIMOS LOS CARACTERES EN LA matriz_laberinto3
    pLaberinto3=fopen("laberinto3.txt", "r");
    if(pLaberinto3==NULL)
    {
         printf("Error al abrir fichero\n");
         return -3;
    }
    else
    {
        while(fscanf(pLaberinto3, "%c", &matriz_laberinto3[fila][columna])!=EOF)//guardar laberinto en una matriz
        {
            columna++;
            if(columna==100)
            {
                fila++;
                columna=0;
            }
        }
        columna=0, fila=0;
        fclose(pLaberinto3);
    }
    do
    {
        printf("\t                                            |------------|\n");
        printf("\t                                            | Bienvenido |\n");
        printf("\t                                            |------------|\n\n\n\n");
        printf("\t|-------------------------------|      |------------------------|        |------------------------|\n");
        printf("\t| Registrarse o iniciar sesion  |      | Estadisticas jugadores |        |        Informacion     |\n");
        printf("\t|              (1)              |      |            (2)         |        |            (3)         |\n");
        printf("\t|-------------------------------|      |------------------------|        |------------------------|\n\n\n\n\n\n\n");
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
        while((tecla_menu!=1)&&(tecla_menu!=2)&&(tecla_menu!=3)&&(tecla_menu!=0));

        switch(tecla_menu)
        {
        case 1:
            printf("Escriba su nombre y genere una contrasenha.\n");
            scanf("%19s %19s", nombre, contrasenha);
            fflush(stdin);
            printf("\n");

                do
                {
                    //AQUI PEDIMOS CONTRASENHA DEL USUARIO
                    do
                    {
                        contra = registrarse_iniciarsesion(contrasenha);
                    }while(contra != 1);

                    //ABRIMOS FICHERO ESTADISTICAS
                    pEstadisticas=fopen("estadisticas.txt", "r");
                    if(pEstadisticas==NULL)
                    {
                        printf("Error al abrir el fichero de estaditicas\n");
                        return -6;
                    }
                    else  //leemos el fichero estadisticas e introducimos su contenido en el vector de estructuras de los jugadores
                    {
                        i=0, num_jugador=0, se_cumple=0; //inicializamos las variables
                        while(fscanf(pEstadisticas, "%[^\t]\t\t\t%i\t\t\t%i\t\t\t%i\n", datos_jugador[i].nombre, &datos_jugador[i].movimientos_laberinto1,
                                     &datos_jugador[i].movimientos_laberinto2, &datos_jugador[i].movimientos_laberinto3)!=EOF)
                        {
                            if(strcmp(datos_jugador[i].nombre,nombre)==0)//comparo si son iguales al nombre introducido
                            {                                            //y el nombre del jugador que esta en el fichero para ver si ya existe
                                num_jugador=i;
                                se_cumple=1; //si hay un nombre ya registrado se_cumple vale 1 sino vale cero
                            }
                            i++;
                        }
                        if(se_cumple==0) //si no exite un jugador con ese nombre lo anhado
                        {
                            total_jugadores=i; //al añadir un jugador nuevo al numero total de jugadores de le suma 1, es decir es igual a i
                            num_jugador=i; //si es la primera vez que juega nuestro jugador se coloca en la ultima fila
                            strcpy(datos_jugador[num_jugador].nombre,nombre); //le asigno el nombre escrito a al jugador[num_jugador] del vector
                            datos_jugador[num_jugador].movimientos_laberinto1=10000; //si no juega al laberinto1 tiene 10000 movimientos
                            datos_jugador[num_jugador].movimientos_laberinto2=10000; //si no juega al laberinto2 tiene 10000 movimientos
                            datos_jugador[num_jugador].movimientos_laberinto3=10000; //si no juega al laberinto3 tiene 10000 movimientos
                        }
                        else
                        {
                            total_jugadores=i-1;//si no añado un jugador nuevo el numero total de jugadores va a ser i-1
                        }

                        fclose(pEstadisticas);
                    }


                    tecla_laberintos=laberintos();
                    switch(tecla_laberintos)
                    {
                    case 1:
                        laberinto1(salida_laberinto);//Inserto en el vector salida_laberinto la salida del laberinto 1
                        for(fila=0; fila<40; fila++) //Igualo los elementos de la matriz_laberinto1 a mi matriz generica
                        {                            //para poder trabajar con ella mas adelante
                            for(columna=0; columna<100; columna++)
                            {
                                matriz_laberinto[fila][columna]=matriz_laberinto1[fila][columna];
                            }
                        }
                        break;
                    case 2:
                        laberinto2(salida_laberinto);//Inserto en el vector salida_laberinto la salida del laberinto 2
                        for(fila=0; fila<40; fila++) //Igualo la matriz_laberinto2 a la matriz generica matriz_laberinto
                        {                            //para poder trabajar con ella mas adelante
                            for(columna=0; columna<100; columna++)
                            {
                                matriz_laberinto[fila][columna]=matriz_laberinto2[fila][columna];
                            }
                        }
                        break;
                    case 3:
                        laberinto3(salida_laberinto);//Inserto en el vector salida_laberinto la salida del laberinto 3
                        for(fila=0; fila<40; fila++) //Igualo los elementos de la matriz_laberinto3 a mi matriz generica
                        {                            //para poder trabajar con ella mas adelante
                            for(columna=0; columna<100; columna++)
                            {
                                matriz_laberinto[fila][columna]=matriz_laberinto3[fila][columna];
                            }
                        }
                        break;
                    }

                    do//pedimos coordenadas iniciales
                    {
                        printf("Introduzca su posicion inicial (fila>0, columna>0): ");
                        scanf("%i %i", &posicion[0], &posicion[1]);//fila y columna en la que quiero estar
                        fflush(stdin);

                        if((posicion[0]>=40)||(posicion[0]<0)||(posicion[1]>=100)||(posicion[1]<0))
                        {
                            printf("Esa posicion se encuentra fuera del laberinto\n\n");
                        }
                        else if((matriz_laberinto[posicion[0]][posicion[1]]!=' ')&&(matriz_laberinto[posicion[0]][posicion[1]]!='?')&&
                                (matriz_laberinto[posicion[0]][posicion[1]]!='S')&&(matriz_laberinto[posicion[0]][posicion[1]]!='!'))
                        {
                            printf("Esa posicion es una pared\n");
                        }
                    }
                    while(posicion[0]>=40||(posicion[0]<0)||(posicion[1]>=100)||(posicion[1]<0)||
                          ((matriz_laberinto[posicion[0]][posicion[1]]!=' ')&&(matriz_laberinto[posicion[0]][posicion[1]]!='?')
                            &&(matriz_laberinto[posicion[0]][posicion[1]]!='S')&&(matriz_laberinto[posicion[0]][posicion[1]]!='!')));
                    //si la posicion elegida es una pared o se encuentra fuera del laberinto se vuelven a pedir coordenadas

                    matriz_laberinto[posicion[0]][posicion[1]]='X';//Marcamos con una X nuestro posicion actual
                                                                   //La X va a ser nuestro cursor
                    //Aqui ira el dibujo de la zona del laberinto donde estamos
                    for(fila=posicion[0]-8; fila<=posicion[0]+8; fila++)//las interrogaciones son pistas
                    {
                        printf("\t\t\t\t\t");
                        for(columna=posicion[1]-8; columna<=posicion[1]+8; columna++)
                        {
                            if((fila>=0)&&(fila<40)&&(columna>=0)&&(columna<99)) //para que no se impriman caracteres aleatorios
                                printf("%c", matriz_laberinto[fila][columna]);    //que estan fuera del laberinto
                        }
                        printf("\n");
                    }

                    while((posicion[0]!=salida_laberinto[0])||(posicion[1]!=salida_laberinto[1]))//Si acierto a la primera
                    {                                                                            //no pide que me mueva
                        tecla_moverse=moverse(matriz_laberinto, &posicion[0], &posicion[1]);//mediante el bucle while repito la funcion
                                                                              //moverse hasta que encuentre la salida o pulse salir
                        //Aqui ira el dibujo de la zona del laberinto donde estamos
                        for(fila=posicion[0]-8; fila<=posicion[0]+8; fila++)//las interrogaciones son pistas
                        {
                            printf("\t\t\t\t\t");
                            for(columna=posicion[1]-8; columna<=posicion[1]+8; columna++)
                            {
                                if((fila>=0)&&(fila<40)&&(columna>=0)&&(columna<99))//hasta 99 para que no me imprima el salto de linea entre fila y fila
                                    printf("%c", matriz_laberinto[fila][columna]);
                            }
                            printf("\n");
                        }
                        printf("\nfila: %i columna: %i\n", posicion[0], posicion[1]);//coordenadas(fila, columna) del punto actual
                         if(tecla_moverse==0)//si moverse devuelve 0(salir) salgo del laberinto y el numero de movimientos es 10000
                        {
                            numero_movimientos=10000;
                            break;
                        }
                        else //si moverse no devuelve 0(salir) sigo en el laberinto y el contador de movimientos sigue sumando
                        {
                            numero_movimientos++;
                        }
                    }
                    if(tecla_moverse==0)
                    {
                        printf("\n\n\n----------------\n");
                        printf("Te has rendido!!\n");
                        printf("----------------\n\n");
                    }
                    else
                    {
                        printf("\n\n\n-----------------------\n");
                        printf("Encontraste la salida!!\n");
                        printf("-----------------------\n\n");
                    }
                    printf("Numero de movimientos: %i\n\n", numero_movimientos);

                    switch(tecla_laberintos)//comparo numero de movimientos actual con el valor de partidas
                    {                       //anteriores en el laberinto seleccionado
                    case 1:
                        if(numero_movimientos<datos_jugador[num_jugador].movimientos_laberinto1) //si el numero de movimientos es menor que el anterior
                            datos_jugador[num_jugador].movimientos_laberinto1=numero_movimientos;//registro se modifica el numero de movimientos anterior
                        break;
                    case 2:
                        if(numero_movimientos<datos_jugador[num_jugador].movimientos_laberinto2)//si el numero de movimientos es menor que el anterior
                            datos_jugador[num_jugador].movimientos_laberinto2=numero_movimientos;//registro se modifica el numero de movimientos anterior
                        break;
                    case 3:
                        if(numero_movimientos<datos_jugador[num_jugador].movimientos_laberinto3)//si el numero de movimientos es menor que el anterior
                            datos_jugador[num_jugador].movimientos_laberinto3=numero_movimientos;//registro se modifica el numero de movimientos anterior
                        break;
                    }
                    //APERTURA FICHERO ESTADISTICAS
                    pEstadisticas=fopen("estadisticas.txt", "w");
                    if(pEstadisticas==NULL)
                    {
                        printf("Error al abrir el fichero de estadisticas\n");
                        return -5;
                    }
                    else
                    {
                        i=0;
                        for(i=0; i<=total_jugadores; i++)//introduzco los valores actualizados en el fichero estadisticas
                        {
                            fprintf(pEstadisticas, "%s\t\t\t%i\t\t\t%i\t\t\t%i\n", datos_jugador[i].nombre, datos_jugador[i].movimientos_laberinto1,
                                datos_jugador[i].movimientos_laberinto2, datos_jugador[i].movimientos_laberinto3);
                        }
                        fclose(pEstadisticas);
                    }

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

            tecla_menu_salir=menu_salir();
            break;
        case 2:
            estadisticas();
            tecla_menu_salir=menu_salir();
            break;
        case 3:
            informacion();
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
    printf("\t                                              |------------|\n");
    printf("\t                                              | Laberintos |\n");
    printf("\t                                              |------------|\n\n\n\n");
    printf("\t\t  |-----------------|               |-----------------|            |-------------------|\n");
    printf("\t\t  |    Nivel 1 (1)  |               |    Nivel 2 (2)  |            |      Nivel 3 (3)  |\n");
    printf("\t\t  |-----------------|               |-----------------|            |-------------------|\n\n\n\n\n\n\n");
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
    salida[0]=31;
    salida[1]=98;               //coordenadas salida laberinto 1
}
//laberinto 2
void laberinto2(int salida[])
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 2~~~~~~~~~~~~~~~\n\n\n");
    salida[0]=38;
    salida[1]=98;              //coordenadas salida laberinto 2
}
//laberinto 3
void laberinto3(int salida[])
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 3~~~~~~~~~~~~~~~\n\n\n");
    salida[0]=38;
    salida[1]=98;              //coordenadas salida laberinto 3
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

//Funcion que imprime las estadisticas de los jugadores
void estadisticas(void)
{
    FILE *pEstadisticas;
    char letra;
    pEstadisticas=fopen("estadisticas.txt", "r");
    if(pEstadisticas==NULL)
    {
        printf("Error al abrir fichero estadisticas\n");
    }
    else
    {
        printf("\nUsuario\t\tMovimiento laberinto1\tMovimiento laberinto2\tMovimiento laberinto3\n");
        printf("-------\t\t---------------------\t---------------------\t---------------------\n");
        while(fscanf(pEstadisticas, "%c", &letra)!=EOF)
            printf("%c", letra);
        fclose(pEstadisticas);
    }

}

//Menu informacion
void informacion(void) //Funcion que imprime por pantalla el contenido el fichero informacion
{
    FILE *pInformacion;
    char letra;
    pInformacion=fopen("informacion.txt", "r");
    if(pInformacion==NULL)
    {
        printf("Error al abrir fichero informacion\n");
    }
    else
    {
        while(fscanf(pInformacion, "%c", &letra)!=EOF)
        {
            printf("%c", letra);
        }
        fclose(pInformacion);
    }
}

//Funcion para movernos por el laberinto
int moverse(char matriz[][100], int *fila, int *columna) //funcion para moverse por el laberinto, en la que vamos a
{                                                         //introducir como argumentos nuestra matriz_laberinto y la
    int i;
    char tecla;
    char auxiliar;
    printf("\nMuevete por el laberinto                                              Salir(0)\n");
    do
    {
        fflush(stdin); //funcion para que no se sature el scanf
        scanf("%c", &tecla);
        if((tecla!='w')&&(tecla!='W')&&(tecla!='a')&&(tecla!='A')&&(tecla!='d')&&(tecla!='D')&&(tecla!='s')&&(tecla!='S')&&(tecla!='0'))
        {
           printf("Tecla incorrecta\n");
        }

    }
    while((tecla!='w')&&(tecla!='W')&&(tecla!='a')&&(tecla!='A')&&(tecla!='d')&&(tecla!='D')&&(tecla!='s')&&(tecla!='S')&&(tecla!='0'));
    if(tecla=='0')
        return 0;
    else
    {
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
                printf("Pista: La salida esta hacia abajo\n");
                auxiliar=matriz[*fila][*columna];      //Nuestro punto actual se intercambia con el punto que esta encima de el
                matriz[*fila][*columna]=matriz[*fila-2][*columna];
                matriz[*fila-2][*columna]=auxiliar;
                *fila=*fila-2;
            }
            else if(matriz[*fila-1][*columna] == '!')
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
                    printf("Pista: La salida esta hacia abajo\n");
                    auxiliar=matriz[*fila][*columna];      //Nuestro punto actual se intercambia con el punto que esta encima de el
                    matriz[*fila][*columna]=matriz[*fila-2][*columna];
                    matriz[*fila-2][*columna]=auxiliar;
                    *fila=*fila-2;
                }
                else if(matriz[*fila-1][*columna] == '!')
                {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
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
                printf("Pista: La salida esta hacia abajo\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna+2];
                matriz[*fila][*columna+2]=auxiliar;
                *columna=*columna+2;
            }
            else if(matriz[*fila][*columna+1] == '!')
            {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
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
                    printf("Pista: La salida esta hacia abajo\n");
                    auxiliar=matriz[*fila][*columna];
                    matriz[*fila][*columna]=matriz[*fila][*columna+2];
                    matriz[*fila][*columna+2]=auxiliar;
                    *columna=*columna+2;
                }
                else if(matriz[*fila][*columna+1] == '!')
                {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
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
                printf("Pista: La salida esta hacia abajo\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila+2][*columna];
                matriz[*fila+2][*columna]=auxiliar;
                *fila=*fila+2;
            }
            else if(matriz[*fila+1][*columna] == '!')
            {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
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
                    printf("Pista: La salida esta hacia abajo\n");
                    auxiliar=matriz[*fila][*columna];
                    matriz[*fila][*columna]=matriz[*fila+2][*columna];
                    matriz[*fila+2][*columna]=auxiliar;
                    *fila=*fila+2;
                }
                else if(matriz[*fila+1][*columna] == '!')
                {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
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
                printf("Pista: La salida esta hacia abajo\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna-2];
                matriz[*fila][*columna-2]=auxiliar;
                *columna=*columna-2;
            }
            else if(matriz[*fila][*columna-1] == '!')
            {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna-2];
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
                    printf("Pista: La salida esta hacia abajo\n");
                    auxiliar=matriz[*fila][*columna];
                    matriz[*fila][*columna]=matriz[*fila][*columna-2];
                    matriz[*fila][*columna-2]=auxiliar;
                    *columna=*columna-2;
                }
                else if(matriz[*fila][*columna-1] == '!')
                {
                printf("Ya estas cerca!!! La salida esta hacia la derecha\n");
                auxiliar=matriz[*fila][*columna];
                matriz[*fila][*columna]=matriz[*fila][*columna-2];
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
        return 1;
    }

}

int registrarse_iniciarsesion(char contra[])
{
    char contrasenna[20];

    printf("Escriba su contrasenha para iniciar sesion.\n");
    scanf("%s", contrasenna);
    if(strcmp(contra, contrasenna) == 0)
        {
        printf("Sesion iniciada\n");
        return 1;
        }
    else
        {
        printf("Contrasenha incorrecta.\n");
        return 0;
        }


}

