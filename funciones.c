#include <stdio.h>
#include <string.h>
#include "funciones.h"
#include "treemap.h"


typedef struct{
    char* Palabra;
    int contador;
}EstructPalabra;

void cargarDocumentos(){

    char identificadores[150];
    char separador[2]=" ";

    printf("Ingrese el identificador de los libros a indexar separados por espacios\n");
    fgets(identificadores,150,stdin);
    fgets(identificadores,150,stdin);

    char *auxArchivo=strtok(identificadores, separador);

    if(auxArchivo!=NULL){

        while(auxArchivo!=NULL){

            printf("Nombre del archivo: %s\n", auxArchivo);

            FILE *archivoAbierto=fopen(auxArchivo,"r");

            if(archivoAbierto==NULL){

                auxArchivo=strtok(identificadores,separador);
                printf("El archivo no se encontro o no existe\n");
                continue;
            }
            else{
                printf("archivo encontrado\n");
            }




        }
    }

}