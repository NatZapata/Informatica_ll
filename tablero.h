#ifndef TABLERO_H
#define TABLERO_H
#include <iostream>
using namespace std;


unsigned char ** crear_tablero(unsigned short &ancho_bits,
                              unsigned short &altura);
void dibujar_matriz(unsigned char** matriz,
                    unsigned short &ancho,
                    unsigned short &altura);
void dibujar_pieza_temporal(unsigned char **tablero,
                            short &posicion_pieza,
                            unsigned short &ancho,
                            unsigned short &altura,
                            unsigned char *mascara1,
                            unsigned char *mascara2,
                            unsigned char *mascara3,
                            unsigned char *mascara4);

void poner_pieza(unsigned char **tablero,
                 short &posicion_pieza,
                 unsigned short &ancho,
                 unsigned short &altura,
                 unsigned char *mascara1,
                 unsigned char *mascara2,
                 unsigned char *mascara3,
                 unsigned char *mascara4);


void eliminar_fila(unsigned char **tablero,
                   unsigned short &ancho,
                   unsigned short &altura);
#endif
