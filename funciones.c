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
    char id[100];
    List *ListaPalabras;//almacena nodo de estrcut Palabra,(palabras que tiene el libro)
};



void* crearLibro(char* auxTitulo, char* auxArchivo){

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

                printf("El archivo no se encontro o no existe\n");
                auxArchivo=strtok(identificadores,separador);
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

                    insertTreeMap(mapaLibros,auxLibro->nombre,auxLibro);//se agrega el libro al mapa, key=titulo, valor=Libro
                    contarPalabras(mapaPalabras,auxArchivo,auxLibro);//funcion para contar las palabras del libro
                }
                /*else{
                    continue;
                }*/

            }

            fclose(archivoAbierto);
            auxArchivo=strtok(NULL, separador);

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

    Palabra* auxP=(Palabra*) malloc (sizeof(Palabra));
    strcpy(auxP->palabra,auxPalabra);
    auxP->contador=1;
    return auxP;

}

void contarPalabras(TreeMap *mapaPalabras,char *auxArchivo,Libro* auxLibro){

    //abrir archivo
    FILE *archivoAbierto=fopen(auxArchivo,"r");
    //ingresa a cada palabra
    char *auxPalabra=next_palabra(archivoAbierto);
    while(auxPalabra){

        Pair *auxPair=searchTreeMap(mapaPalabras,auxPalabra);

        if(auxPair==NULL){//la palabra no existe

            Palabra *palabraCreada=crearPalabra(auxPalabra);
            //se inserta la palabras en el mapa
            insertTreeMap(mapaPalabras,auxPalabra,palabraCreada);
            //se inserta la palabra en la lista del libro
            pushBack(auxLibro->ListaPalabras,palabraCreada);
        }
        else{//la palabras existe

            Palabra *auxPalabra2;
            //aumentar contador
            auxPalabra2=auxPair->value;
            auxPalabra2->contador++;
            
        }
        auxPalabra=next_palabra(archivoAbierto);
    }

}

void mostrarDocumentos(TreeMap* mapaLibros){

    Pair* aux=firstTreeMap(mapaLibros);
    Libro* auxLibro;

    if(aux==NULL){
        printf("Aun no hay libros\n");
    }
    else{
       while(aux!=NULL){

           auxLibro=aux->value;
           printf("Titulo:%s  - Identificador:%s \n", auxLibro->nombre, auxLibro->id);
           aux=nextTreeMap(mapaLibros);
        }
    }
}


void buscarLibroTitulo(TreeMap* mapaLibros){
    //USUARIO INGRESA PALABRAS SEPARADAS POR ESPACIOS
    //BUSCAR LIBROS QUE CONTIENEN TODAS LAS PALABRAS
    //MOSTRAR TITULOS
    char palabras[150];
    char separador[2]=" ";
    int cantidad;
    int encontradas=0;
    List* librosConPalabras=createList();

    printf("ingrese la cantidad de palabras que utilizara\n");
    scanf("%d", &cantidad);
    printf("Ingrese las palabras para buscar el libro separada por un espacio\n");
    fgets(palabras,150,stdin);
    fgets(palabras,150,stdin);

    Pair* auxPair=firstTreeMap(mapaLibros);
    Libro* auxLibro;
    Palabra* auxLista;
    
    while(auxPair!=NULL){

        char *auxPalabras=strtok(palabras, separador);

        if(auxPalabras!=NULL){

            while (auxPalabras!=NULL){

                auxLibro=auxPair->value;
                auxLista=firstList(auxLibro->ListaPalabras);

                while (auxLista!=NULL){

                    if(strcmp(auxLista->palabra,auxPalabras)!=0){
                        encontradas++;
                    }

                    auxLista=nextList(auxLibro->ListaPalabras);
                    
                }
                auxPalabras=strtok(NULL, separador);
                
            }
            
        }

        if(encontradas==cantidad){

            //se agrega el libro a la lista con los libros que tienen todas las palabras
            pushBack(librosConPalabras,auxLibro);
        }
        encontradas=0;
        auxPair=nextTreeMap(mapaLibros);
    }
    
    auxLibro=firstList(librosConPalabras);

    printf("Libros con todas las palabras\n");
    while(auxLibro!=NULL){
        printf("%s\n",auxLibro->nombre);

        auxLibro=nextList(librosConPalabras);
    }

}