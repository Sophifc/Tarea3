#include "treemap.h"

typedef struct Libro Libro;


void* crearLibro(char auxTitulo[], char *auxArchivo);
void cargarDocumentos(TreeMap *mapaPalabras, TreeMap *mapaLibros/*, FILE *carpeta*/);
void contarPalabras(TreeMap* mapaPalabras,char *auxArchivo,Libro* auxLibro);
void mostrarDocumentos(TreeMap* mapaLibros);
void buscarLibroTitulo(TreeMap* mapaLibros);
void mayorFrecuencia(TreeMep* mapaLibros);