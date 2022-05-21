#include <stdio.h>
#include <string.h>
#include "treemap.h"
#include "funciones.h"


int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}


void initMenu(){

  TreeMap *mapaPalabras=createTreeMap(lower_than_string);
  TreeMap *mapaLibros=createTreeMap(lower_than_string);

    int eleccion;

    while(eleccion!=0){

        printf("Opciones del menu: \n");
        printf("0-. Salir del menu\n");
        printf("1-. Cargar documentos\n");
        printf("2-. Mostrar documentos ordenaods\n");
        printf("3-. Buscar libro por titulo\n");
        printf("4-. Palabras con mayor fecuencia\n");
        printf("5-. Palabras mas relevants\n");
        printf("6-. Buscar por palabra\n");
        printf("7-. Mostrar palabra en un contexto\n");

        scanf("%d",&eleccion);
        

        switch (eleccion){

        case 1:
        cargarDocumentos(mapaPalabras, mapaLibros);
        break;

        case 2:
        mostrarDocumentos(mapaLibros);
        break;


        case 3:

          break;

        case 4:

           break;

        case 5:

          break;

        case 6:

           break;

        case 7:

          break;

        }
    }


}