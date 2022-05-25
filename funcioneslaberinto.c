#include<stdio.h>
#include<string.h>
#include"funcioneslaberinto.h"


int registrarse_iniciarsesion(char contra[])
{
    char contrasenna[20];

    printf("Escriba su contrasenha para iniciar sesion.\n");
    scanf("%19s", contrasenna);
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

