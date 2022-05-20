#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "treemap.h"


typedef struct{
    char palabra[100];
    int contador;
}Palabra;


typedef struct{
    char nombre[100];
    char id[100];//con atoi pasar el string a int
    //int cantPalabras;
    //List ListaPalabras;//almacena nodo de estrcut Palabra,(palabras que tiene el libro)
}Libro;



void* crearLibro(char* auxTitulo, char* auxArchivo){

    Libro* auxLibro=(Libro*) malloc (sizeof(Libro));
    strcpy(auxLibro->nombre,auxTitulo);
    strcpy(auxLibro->id,auxArchivo);
    return auxLibro;
}

void cargarDocumentos(TreeMap* mapaPalabras, TreeMap* mapaLibros){

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

            printf("Nombre del archivo/Indetificador del libro: %s\n", auxArchivo);

            FILE *archivoAbierto=fopen(auxArchivo,"r");

            if(archivoAbierto==NULL){

                auxArchivo=strtok(identificadores,separador);
                printf("El archivo no se encontro o no existe\n");
                break;
            }
            else{
                printf("archivo encontrado\n");
                char auxTitulo[100];
                //sacar el nombre del libro desde el archivo
                fseek(archivoAbierto,33,SEEK_SET);//se mueve el puntero a la posicion 32 del archivo de texto
                
                if(strcmp(fgets(auxTitulo,100,archivoAbierto), ",")!=0){
                    printf("TITULO: %s\n", auxTitulo);

                }

                if(searchTreeMap(mapaLibros,auxTitulo)==NULL){//el libro no existe en el mapa

                    Libro *auxLibro=crearLibro(auxTitulo,auxArchivo);
                    insertTreeMap(mapaLibros,auxTitulo,auxLibro);//se agrega el libro al mapa, key=titulo, valor=Libro

                    contarPalabras(mapaPalabras,auxArchivo);//funcion para contar las palabras del libro
                }
                else{
                    continue;
                }
                
                //si no existe agregarlo ->luego de agregarlo se comienzan a contar las palabras
                //si existe pasar al siguiente archivo

            }

            fclose(archivoAbierto);
            auxArchivo=strtok(NULL, separador);

            printf("siguiente archivo\n");

        }
    }

}

char* next_palabra(FILE *archivo){
    char aux[1024];
    if(fscanf(archivo,"%1023s",aux)==1){

        //pasar palabra a minuscula
        for (int k = 0; aux[k]; k++){
            aux[k] = tolower(aux[k]);
        }

        return strdup(aux);
    }
    else{
        return NULL;
    }
}


void* crearPalabra(auxPalabra){
    Palabra* auxP=(Palabra*) malloc (sizeof(Palabra));
    strcpy(auxP->palabra,auxPalabra);
    auxP->contador=1;
    return auxP;

}

void contarPalabras(TreeMap *mapaPalabras,char *auxArchivo){
    //abrir archivo
    FILE *archivoAbierto=fopen(auxArchivo,"r");
    //ingresa a cada palabra
    char *auxPalabra=next_palabra(archivoAbierto);
    while(auxPalabra){

        Pair* auxPair=searchTreeMap(mapaPalabras,auxPalabra);
        if(auxPair==NULL){

            Palabra *palabraCreada=crearPalabra(auxPalabra);
            insertTreeMap(mapaPalabras,auxPalabra,palabraCreada);
            //crear el nodo para la palabra y agregarlo al mapa y la lista
        }
        else{
            auxPair->value->contador++;
            
        }
        //ver si la palabra existe en el mapa
        //si existe aumentar contador
        //si no eixste crearla y agregarla al mapa y la lista del libro

        auxPalabra=next_palabra(archivoAbierto);
    }

}