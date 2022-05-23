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
    List *ListaPalabras;//almacena nodo de estrcut Palabra,palabras que tiene el libro
    List *CantidadVecesPalabra;//almacena la palabra y cantidad de veces que aparece en el libro
    int cantidad;//cantidad de palabras que tiene en total
};



void* crearLibro(char* auxTitulo, char* auxArchivo){

    Libro* auxLibro=(Libro*) malloc (sizeof(Libro));
    List* listaLibro=createList();
    auxLibro->ListaPalabras=listaLibro;


    List* listaLibro2=createList();
    auxLibro->CantidadVecesPalabra=listaLibro2;

    strcpy(auxLibro->nombre,auxTitulo);
    strcpy(auxLibro->id,auxArchivo);
    auxLibro->cantidad=0;
    return auxLibro;
}


// 1) FUNCION QUE CARGA LOS LIBROS INGRESADOS POR EL USUARIO
void cargarDocumentos(TreeMap* mapaPalabras, TreeMap* mapaLibros/*,FILE *carpeta*/){

    char identificadores[150];
    char separador[2]=" ";

    printf("Ingrese el identificador de los libros a indexar separados por espacios\n");
    fgets(identificadores,150,stdin);
    fgets(identificadores,150,stdin);

    
    char *auxArchivo=strtok(identificadores, separador);

    if(auxArchivo!=NULL){

        while(auxArchivo!=NULL){

            FILE *archivoAbierto=fopen(auxArchivo,"r");

            if(archivoAbierto==NULL){

                printf("El archivo no se encontro o no existe\n");
                auxArchivo=strtok(identificadores,separador);
                break;
            }
            else{
                printf("Nombre del archivo/Indetificador del libro: %s\n", auxArchivo);
                printf("archivo encontrado\n");
                char auxTitulo[100];
                //sacar el nombre del libro desde el archivo
                fseek(archivoAbierto,33,SEEK_SET);//se mueve el puntero a la posicion 32 del archivo de texto
                
                fgets(auxTitulo,100,archivoAbierto);
                //strtok(auxTitulo, ",");

                if(strcmp(auxTitulo, ",")!=0){
                    printf("TITULO: %s\n", auxTitulo);

                }

                if(searchTreeMap(mapaLibros,auxArchivo)==NULL){//el libro no existe en el mapa
                   
                    Libro *auxLibro=crearLibro(auxTitulo,auxArchivo);

                    insertTreeMap(mapaLibros,auxArchivo,auxLibro);//se agrega el libro al mapa, key=id, valor=Libro
                    contarPalabras(mapaPalabras,auxArchivo,auxLibro);//funcion para contar las palabras del libro
                    
                }

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

void* crearPalabra2(char *auxPalabra){

    Palabra* auxP=(Palabra*) malloc (sizeof(Palabra));
    strcpy(auxP->palabra,auxPalabra);
    auxP->contador=1;
    return auxP;

}


// FUNCION QUE CUENTA LAS PALABRAS DEL LIBRO
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

            Palabra *palabraCreada2=crearPalabra2(auxPalabra);
            pushBack(auxLibro->CantidadVecesPalabra,palabraCreada2);

            auxLibro->cantidad++;
        }
        else{//la palabras existe

            //aumentar contador
            Palabra *auxPalabra2;
            auxPalabra2=auxPair->value;
            auxPalabra2->contador++;

            //aumentar cantidad en la lista del libro 
            Palabra* auxPalabra3=firstList(auxLibro->CantidadVecesPalabra);
            while(auxPalabra3!=NULL){
                if(strcmp(auxPalabra3->palabra,auxPalabra2->palabra)==0){
                    auxPalabra3->contador++;
                }
                auxPalabra3=nextList(auxLibro->CantidadVecesPalabra);
            }

            
        }
        auxPalabra=next_palabra(archivoAbierto);
    }

}


// 2) FUNCION MUESTRA TODOS LOS LIBROS CARGADOS ORDENADOS POR ORDEN ALFABETICO
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

// 3)FUNCION QUE BUSCA  Y MJESTRA LOS LIBROS QUE CONTENGAN TODAS LAS PALABRAS INGRESADAS POR EL USUARIO
void buscarLibroTitulo(TreeMap* mapaLibros){

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
        printf("palabra a buscar : %s\n", auxPalabras);

        if(auxPalabras!=NULL){

            while (auxPalabras!=NULL){

                auxLibro=auxPair->value;
                auxLista=firstList(auxLibro->ListaPalabras);

                while (auxLista!=NULL){

                    if(strcmp(auxLista->palabra,auxPalabras)==0){
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


// 4) FUNCION QUE BUSCA Y MUESTRA LAS PALABRAS CON MAYOR FRECUENCIA DE UN LIBRO INGRRESADO POR LE USUARIO

void mayorFrecuencia(TreeMap* mapaLibros){

    char identificador[150];
    printf("Ingrese el identificador del libro\n");
    fgets(identificador,150,stdin);
    fgets(identificador,150,stdin);
    strtok(identificador," ");

    Pair* auxPair=searchTreeMap(mapaLibros,identificador);

    if(auxPair!=NULL){
        Libro* auxLibro=auxPair->value;

        double frecuencia;
        double frecuenciaInicial=0;
        List* auxLista=createList();
        Palabra* auxPalabra=firstList(auxLibro->CantidadVecesPalabra);

        while(auxPalabra!=NULL){
        
            frecuencia=(auxPalabra->contador/auxLibro->cantidad);
            printf("frecuencia: %lf\n", frecuencia);

            if(frecuencia>frecuenciaInicial){
               pushBack(auxLista,auxPalabra);
               frecuenciaInicial=frecuencia;
               frecuencia=0;
            }
            auxPalabra=nextList(auxLibro->CantidadVecesPalabra);
        }

        printf("Palabras con mayor frecuencia:\n");
        auxPalabra=firstList(auxLista);
        int cont=0;
        while(auxPalabra!=NULL){

           if(cont==10){
               break;
            }
            else{
                printf("%d-. %s", cont, auxPalabra->palabra);
                cont++;
                auxPalabra=nextList(auxLista);
           }

        }
    }
    else{
        printf("El libro perteneciente al id no se ha encontrado\n");

    }

}
