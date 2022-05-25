int moverse(char matriz[][100], int *fila, int *columna);
void laberinto1(int salida[]);
void laberinto2(int salida[]);
void laberinto3(int salida[]);
int registrarse_iniciarsesion(char contra[]);

typedef struct //estructura jugador que almacena su nombre, contrasenha y
{              //movimientos en cada laberinto
    char nombre[20], contrasenna[20];
    int movimientos_laberinto1;
    int movimientos_laberinto2;
    int movimientos_laberinto3;
}jugador;

