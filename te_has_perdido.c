#include<stdio.h>

int laberinto1(void);
int laberinto2(void);
int laberinto3(void);
void moverse(int posicion[]);

int main() //menu principal
{
    int tecla_menu;
    int tecla_laberinto;
    do
    {
        printf("\t\t                                    ??????????????\n");
        printf("\t\t                                    ? Bienvenido ?\n");
        printf("\t\t                                    ??????????????\n\n\n\n");
        printf("\t\t???????????????????               ???????????????????            ??????????????????\n");
        printf("\t\t? Laberinto 1 (1) ?               ? Laberinto 2 (2) ?            ? Laberinto 3(3) ?\n");
        printf("\t\t???????????????????               ???????????????????            ??????????????????\n\n\n\n\n\n\n");
        printf("\t\t\t                                                                  ????????????\n");
        printf("\t\t\t                                                                  ? Salir(0) ?\n");
        printf("\t\t\t                                                                  ????????????\n\n\n");
        do
        {
            scanf("%i", &tecla_menu);
            fflush(stdin);   //funcion para que no se sature el scanf
        }
        while((tecla_menu!=1)&&(tecla_menu!=2)&&(tecla_menu!=3)&&(tecla_menu!=0));

        switch(tecla_menu)
        {
        case 1:
            tecla_laberinto=laberinto1();
            break;
        case 2:
            //tecla_laberinto=laberinto2();
            break;
        case 3:
            //tecla_laberinto=laberinto3();
            break;
        case 0:
            printf("\n\n\nHasta luego!!\n");
            break;
        }
    }
    while((tecla_menu!=0)&&(tecla_laberinto!=0));
    return 0;
}
int laberinto1(void)
{
    int posicion[2]; //posicion del jugador
    int salida[2]={100, 20}; //punto del laberinto en el que se encuentra la salida, no lo conoce el usuario,
    int tecla_laberinto;     //solo el programador
    printf("\t\t             ~~~~~~~~~~~~~~~~Has entrado en el laberinto 1~~~~~~~~~~~~~~~\n\n\n");
    printf("Introduzca su posicion inicial: ");
    scanf("%i %i", &posicion[0], &posicion[1]);//Aqui ir� el dibujo de la zona del laberinto donde estamos
    while((posicion[0]!=salida[0])||(posicion[1]!=salida[1]))
    {
        moverse(posicion);
        printf("%i %i\n", posicion[0], posicion[1]);
    }
    printf("\n\n\nEncontraste la salida!!\n\n\n");
    printf("\t\t                         ~~Menu(1)~~              ~~Salir(0)~~\n\n\n");
    do
    {
        fflush(stdin); //funcion para que no se sature el scanf
        scanf("%i", &tecla_laberinto);
    }
    while((tecla_laberinto!=1)&&(tecla_laberinto!=0));
    return tecla_laberinto;

}
//int laberinto2(void)
//{
//    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 2~~~~~~~~~~~~~~~\n\n\n");
//}
//int laberinto3(void)
//{
//    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 3~~~~~~~~~~~~~~~\n\n\n");
//}

void moverse(int posicion[]) //funcion para moverse por el laberinto, cuyo argumento es un vector
{                            //que indica la posicion en la que nos encontramos
    char tecla;
    printf("\nMuevete por el laberinto.\n");
    scanf(" %c", &tecla);
    switch(tecla)
    {
    case 'w': //moverse una posicion hacia arriba
    case 'W':
        //if(laberinto!=pared) se avanza
        posicion[1]++;
        break;
    case 'd': //moverse una posicion hacia la derecha
    case 'D':
        posicion[0]++;
        break;
    case 's': //moverse una posicion hacia abajo
    case 'S':
        posicion[1]--;
        break;
    case 'a': //moverse una posicion hacia la izquierda
    case 'A':
        posicion[0]--;
        break;
    }

}