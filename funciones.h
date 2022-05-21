#include "treemap.h"

typedef struct Libro Libro;


void* crearLibro(char auxTitulo[], char *auxArchivo);
void cargarDocumentos(TreeMap *mapaPalabras, TreeMap *mapaLibros);
void contarPalabras(TreeMap* mapaPalabras,char *auxArchivo,Libro* auxLibro);
void mostrarDocumentos(TreeMap* mapaLibros);