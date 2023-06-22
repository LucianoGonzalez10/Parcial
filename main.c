#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int nroHabitacion;
    int piso; // los pisos son 4
    int capacidad; // 1 si es single, 2 si es doble, etc
    int precio;
    char tipoHab [20]; // se genera automáticamente: estándar o premium
} stHabitacion;

stHabitacion cargarHabitaciones();
void cargarArchivo(char nombre[]);
int contarArchivo(char nombre[]);
int pasarArreglo(char nombre[], stHabitacion arreglo[]);
void mostrarArreglo(stHabitacion arreglo[], int dimension);
int mostrarArchivo(char nombre[]);
int pasarTodoArreglo(char nombre[], stHabitacion arregloGeneral[]);
int cargarMatriz(char nombre[], int dimF, int dimC, int matriz[dimF][dimC], int validos);
void mostrarMatriz(int dimF, int dimC, int matriz[dimF][dimC]);


int main()
{
    char nombre[20] = "habitaciones.bin";
    stHabitacion arreglo[150];
    stHabitacion arregloGeneral[150];
    int matriz[150][4];
    cargarArchivo(nombre);
    int cantidad = contarArchivo(nombre);
    printf("La cantidad de habitaciones en ese rango de precio es de: %i \n", cantidad);
    int dimension = pasarArreglo(nombre, arreglo);
    printf("\n \n ARREGLO \n");
    mostrarArreglo(arreglo, dimension);
    printf("ARCHIVO \n");
    mostrarArchivo(nombre);
    int validos = pasarTodoArreglo(nombre, arregloGeneral);
    int dimF = cargarMatriz(nombre, dimF, 4, matriz,  validos);
    mostrarMatriz(dimF, 4, matriz);

    return 0;
}

stHabitacion cargarHabitaciones()
{
    stHabitacion aux;
    printf("Ingrese el numero de la habitacion: \n");
    scanf("%i", &aux.nroHabitacion);

    printf("Ingrese el piso de la habitacion: \n");
    scanf("%i", &aux.piso);
    while(aux.piso > 4 || aux.piso < 1)
    {
        printf("Ingrese un piso valido: \n");
        scanf("%i", &aux.piso);
    }
    printf("Ingrese la capacidad de la habitacion: \n");
    scanf("%i", &aux.capacidad);

    printf("Ingrese el precio de la habitacion: \n");
    scanf("%i", &aux.precio);

    if(aux.piso >= 3)
    {
        strcpy(aux.tipoHab, "premium");
    }
    else
    {
        strcpy(aux.tipoHab, "estandar");
    }

    return aux;
}

void cargarArchivo(char nombre[])
{
    FILE * buffer = fopen(nombre, "ab");
    stHabitacion h;
    char control = 's';

    printf("Desea cargar datos? (s/n) \n");
    fflush(stdin);
    scanf("%c", &control);

    if(buffer)
    {
        while(control == 's')
        {
            h = cargarHabitaciones();
            fwrite(&h, sizeof(stHabitacion), 1, buffer);

            printf("Desea seguir cargando datos? (s/n) \n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(buffer);
    }
}

int contarArchivo(char nombre[])
{
    FILE * buffer = fopen(nombre, "rb");
    stHabitacion aux;

    int precioMin = 0, precioMax = 0, i = 0;
    printf("Ingrese el precio minimo de la habitacion: \n");
    scanf("%i", &precioMin);

    printf("Ingrese el precio maximo de la habitacion: \n");
    scanf("%i", &precioMax);

    if(buffer)
    {
        while(fread(&aux, sizeof(stHabitacion),1, buffer) > 0)
        {
            if(aux.precio >= precioMin && aux.precio <= precioMax)
            {
                i++;
            }
        }
        fclose(buffer);
    }
    return i;
}

int pasarArreglo(char nombre[], stHabitacion arreglo[])
{
    FILE * buffer = fopen(nombre, "rb");
    stHabitacion aux;
    int i = 0;
    char eleccion[20];
    printf("Ingrese el tipo de habitacion a pasar al arreglo: \n");
    fflush(stdin);
    gets(eleccion);

    if(buffer)
    {
        while(fread(&aux, sizeof(stHabitacion), 1, buffer)> 0)
        {
            if(strcmp(aux.tipoHab, eleccion) == 0)
            {
                arreglo[i] = aux;
                i++;
            }
        }
        fclose(buffer);
    }
    return i;
}

int mostrarArchivo(char nombre[])
{
    stHabitacion aux;
    FILE * buffer = fopen(nombre, "rb");
    int i = 0;
    if(buffer)
    {
        while(fread(&aux, sizeof(stHabitacion),1, buffer) > 0)
        {
            printf("Numero de habitacion:  %i \n", aux.nroHabitacion);
            printf("Piso de la habitacion:  %i \n", aux.piso);
            printf("Capacidad de la habitacion:  %i \n", aux.capacidad);
            printf("Precio de la habitacion:  %i \n", aux.precio);
            printf("Tipo de habitacion:  %s \n", aux.tipoHab);
            printf("___________________________ \n");
            i++;
        }
        fclose(buffer);
    }
    return i;
}

void mostrarArreglo(stHabitacion arreglo[], int dimension)
{
    int i = 0;
    while(i<dimension)
    {
        printf("Numero de Habitacion: %i \n", arreglo[i].nroHabitacion);
        printf("Piso de la Habitacion: %i \n", arreglo[i].piso);
        printf("Capacidad de la Habitacion: %i \n", arreglo[i].capacidad);
        printf("Precio de la Habitacion: %i \n", arreglo[i].precio);
        printf("Tipo de Habitacion: %s \n", arreglo[i].tipoHab);
        printf("___________________________ \n");
        i++;
    }
}


int pasarTodoArreglo(char nombre[], stHabitacion arregloGeneral[])
{
    FILE * buffer = fopen(nombre, "rb");
    stHabitacion aux;
    int i = 0;

    if(buffer)
    {
        while(fread(&aux, sizeof(stHabitacion), 1, buffer)> 0)
        {
                arregloGeneral[i] = aux;
                i++;
        }
        fclose(buffer);
    }
    return i;
}

int cargarMatriz(char nombre[], int dimF, int dimC, int matriz[dimF][dimC], int validos){
    stHabitacion aux;
    FILE * buffer = fopen(nombre, "rb");
    int f = 0, c = 0;
    if(buffer){
        for(f=0; f<dimF && f < validos; f++){
            if(fread(&aux, sizeof(stHabitacion),1 , buffer) > 0){
                matriz[f][c++] = aux.nroHabitacion;
                matriz[f][c++] = aux.piso;
                matriz[f][c++] = aux.capacidad;
                matriz[f][c++] = aux.precio;
            }
            c = 0;
        }
        fclose(buffer);
    }
    return f;
}

void mostrarMatriz(int dimF, int dimC, int matriz[dimF][dimC]){
    int f = 0, c = 0;
    for(f = 0; f<dimF; f++){
        for(c = 0; c<dimC; c++){
            printf("|    %i     |", matriz[f][c]);
        }
        printf("\n");
    }
}

