#include <stdio.h>
#include <string.h>
#include "funciones.h"
#include "treemap.h"


typedef struct{
    char* palabra;
    int contador;
}Palabra;


typedef struct{
    char nombre[100];
    int id;//con atoi pasar el string a int
    int cantPalabras;
    //List ListaPalabras
}Libro;


void cargarDocumentos(TreeMap *mapaPalabras, TreeMap *mapaLibros){

    char identificadores[150];
    char separador[2]=" ";

    printf("Ingrese el identificador de los libros a indexar separados por espacios\n");
    fgets(identificadores,150,stdin);
    fgets(identificadores,150,stdin);

    char *auxArchivo=strtok(identificadores, separador);
         //printf("1Nombre del archivo: %s\n", auxArchivo);

    if(auxArchivo!=NULL){

        //printf("ENTRO AL IF\n");

        while(auxArchivo!=NULL){

            //printf("ENTRO AL WHILE\n");

            printf("Nombre del archivo: %s\n", auxArchivo);

            FILE *archivoAbierto=fopen(auxArchivo,"r");

            if(archivoAbierto==NULL){

                auxArchivo=strtok(identificadores,separador);
                printf("El archivo no se encontro o no existe\n");
                break;
            }
            else{
                printf("archivo encontrado\n");

                //sacar el nombre del libro desde el archivo
                //guardar el nombre en una variable 
                //ver si el libro ya existe previamente en el mapa
                //si no existe agregarlo ->luego de agregarlo se comienzan a contar las palabras
                //si existe pasar al siguiente archivo

            }

            fclose(archivoAbierto);
            auxArchivo=strtok(NULL, separador);

            printf("siguiente archivo\n");

        }
    }

}