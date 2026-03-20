#ifndef PIEZAS_H
#define PIEZAS_H
//#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
void crear_pieza_aleatoria(unsigned short &ancho_matriz,unsigned short &numero_pieza,unsigned char *primera_mascara,
                           unsigned char *segunda_mascara, unsigned char *tercera_mascara,
                           unsigned char *cuarta_mascara);


bool game_over(unsigned char **tablero,
               unsigned short ancho_matriz,
               unsigned char numero_pieza,
               unsigned char *m1,
               unsigned char *m2,
               unsigned char *m3,
               unsigned char *m4);
#endif // PIEZAS_H
