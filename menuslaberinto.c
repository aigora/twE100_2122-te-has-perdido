#include<stdio.h>
#include"funcioneslaberinto.h"  //para usar la estructura jugador
#include"menuslaberinto.h"


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
    jugador v[100];
    int i;
    FILE *pEstadisticas;
    pEstadisticas=fopen("estadisticas.txt", "r");
    if(pEstadisticas==NULL)
    {
        printf("Error al abrir fichero estadisticas\n");
    }
    else
    {
        printf("\nUsuario\t\tMovimientos laberinto1\tMovimientos laberinto2\tMovimientos laberinto3\n");
        printf("-------\t\t----------------------\t----------------------\t----------------------\n");
        i=0;
        while(fscanf(pEstadisticas, "%[^\t]\t\t\t%i\t\t\t%i\t\t\t%i\t\t\t%[^\n]\n", v[i].nombre, &v[i].movimientos_laberinto1,
                                           &v[i].movimientos_laberinto2, &v[i].movimientos_laberinto3, &v[i].contrasenna)!=EOF)
        {
            printf("%s\t\t\t%i\t\t\t%i\t\t\t%i\n", v[i].nombre, v[i].movimientos_laberinto1,
                                           v[i].movimientos_laberinto2, v[i].movimientos_laberinto3);
            i++;                            //imprimimos por pantalla todos los datos de los jugadores menos su contrasenha
        }
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

