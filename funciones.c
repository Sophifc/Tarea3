#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"
#include "treemap.h"
#include "list.h"


typedef struct{
    char palabra[100];
    int contador;
}Palabra;


struct Libro{
    char nombre[100];
    char id[100];//con atoi pasar el string a int
    //int cantPalabras;
    List *ListaPalabras;//almacena nodo de estrcut Palabra,(palabras que tiene el libro)
};



void* crearLibro(char* auxTitulo, char* auxArchivo){

    //printf("Creando libro\n");
    Libro* auxLibro=(Libro*) malloc (sizeof(Libro));
    List* listaLibro=createList();
    auxLibro->ListaPalabras=listaLibro;
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


    if(auxArchivo!=NULL){



        while(auxArchivo!=NULL){


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
                   
                    printf("El libro no existe,hay que crearlo\n");
                    Libro *auxLibro=crearLibro(auxTitulo,auxArchivo);
                    //printf("Libro creado\n");

                    insertTreeMap(mapaLibros,auxTitulo,auxLibro);//se agrega el libro al mapa, key=titulo, valor=Libro
                    //printf("Libro guardado en el mapa\n");
                    contarPalabras(mapaPalabras,auxArchivo,auxLibro);//funcion para contar las palabras del libro
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


void* crearPalabra(char *auxPalabra){
    //printf("creando palabra\n");
    Palabra* auxP=(Palabra*) malloc (sizeof(Palabra));
    strcpy(auxP->palabra,auxPalabra);
    auxP->contador=1;
    return auxP;

}

void contarPalabras(TreeMap *mapaPalabras,char *auxArchivo,Libro* auxLibro){
    //printf("Contando palabras del libro\n");
    //abrir archivo
    FILE *archivoAbierto=fopen(auxArchivo,"r");
    //ingresa a cada palabra
    char *auxPalabra=next_palabra(archivoAbierto);
    while(auxPalabra){

        Pair *auxPair=searchTreeMap(mapaPalabras,auxPalabra);
        

        if(auxPair==NULL){//la palabra no existe
            
           // printf("Palabra no existe,a crearla\n");

            Palabra *palabraCreada=crearPalabra(auxPalabra);
            //se inserta la palabras en el mapa
            
            insertTreeMap(mapaPalabras,auxPalabra,palabraCreada);
            //printf("palabra guardado en el mapa\n");
            //se inserta la palabra en la lista del libro
            //ERROR
            pushBack(auxLibro->ListaPalabras,palabraCreada);
            //printf("palabra guardado en la lista del libro\n");

            //crear el nodo para la palabra y agregarlo al mapa y la lista
        }
        else{//la palabras existe

            Palabra *auxPalabra2;
            //printf("palabra existe, aumentando contador\n");
            //aumentar contador
            auxPalabra2=auxPair->value;
            auxPalabra2->contador++;
            
        }
        //printf("pasando a la sgte palabra\n");
        auxPalabra=next_palabra(archivoAbierto);
    }

}

void mostrarDocumentos(TreeMap* mapaLibros){

    Pair* aux=firstTreeMap(mapaLibros);
    Libro* auxLibro;

    while(aux!=NULL){

        auxLibro=aux->value;
        printf("Titulo:%s  - Identificador:%s \n", auxLibro->nombre, auxLibro->id);

        aux=nextTreeMap(mapaLibros);
    }
}