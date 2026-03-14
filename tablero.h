#ifndef TABLERO_H
#define TABLERO_H
#include <iostream>
using namespace std;


unsigned char ** crear_tablero(unsigned short &ancho, unsigned short &altura);
void dibujar_matriz(unsigned char** matriz,unsigned short &ancho, unsigned short &altura);
#endif
