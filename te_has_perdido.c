#include<stdio.h>

void laberinto1(void);
void laberinto2(void);
void laberinto3(void);

int main()
{
    char tecla;
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
            scanf(" %c", &tecla);
        }
        while((tecla!='1')&&(tecla!='2')&&(tecla!='3')&&(tecla!='0'));

        switch(tecla)
        {
        case '1':
            laberinto1();
            break;
        case '2':
            laberinto2();
            break;
        case '3':
            laberinto3();
            break;
        case '0':
            printf("\n\n\nHasta luego!!\n");
            break;
        }
    }
    while(tecla!='0');
    return 0;
}
void laberinto1(void)
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 1~~~~~~~~~~~~~~~\n\n\n");
}
void laberinto2(void)
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 2~~~~~~~~~~~~~~~\n\n\n");
}
void laberinto3(void)
{
    printf("\t\t              ~~~~~~~~~~~~~~~~Has entrado en el laberinto 3~~~~~~~~~~~~~~~\n\n\n");
}
