#include<stdio.h>

void laberinto1(void);
void laberinto2(void);
void laberinto3(void);

int main()
{
    char tecla;
    do
    {
        printf("\t\t                                 Bienvenido\n\n\n\n");
        printf("\t\tLaberinto 1 (1)                Laberinto 2 (2)              Laberinto 3(3)\n\n\n\n");
        printf("\t\t                                                                    Salir(0)\n\n\n");
        do
        {
            scanf(" %c", &tecla);
        }
        while((tecla!='1')&&(tecla!='2')&&(tecla!='3')&&(tecla!='0'));

        switch(tecla)
        {
        case '1':
            //laberinto1();
            break;
        case '2':
            //laberinto2();
            break;
        case '3':
            //laberinto3();
            break;
        case '0':
            printf("\n\n\nHasta luego!!\n");
            break;
        }
    }
    while(tecla!='0');
    return 0;
}
