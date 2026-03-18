#ifndef COMPORTAMIENTOSPIEZAS_H
#define COMPORTAMIENTOSPIEZAS_H
void mover_izquierda(unsigned char **tablero,
                     short &posicion_pieza,
                     unsigned short &ancho,
                     unsigned char *mascara1,
                     unsigned char *mascara2,
                     unsigned char *mascara3,
                     unsigned char *mascara4);

void mover_derecha(unsigned char **tablero,
                   short &posicion_pieza,
                   unsigned short &ancho,
                   unsigned char *mascara1,
                   unsigned char *mascara2,
                   unsigned char *mascara3,
                   unsigned char *mascara4);



bool bajar_pieza(unsigned char **tablero,
                 short &posicion_pieza,
                 unsigned short &ancho,
                 unsigned short &altura,
                 unsigned char *mascara1,
                 unsigned char *mascara2,
                 unsigned char *mascara3,
                 unsigned char *mascara4);



void movimientos(unsigned char **tablero,
                 short &posicion,
                 char &boton,
                 bool &colision,
                 unsigned short &ancho,
                 unsigned short &altura,
                 unsigned char *mascara1,
                 unsigned char *mascara2,
                 unsigned char *mascara3,
                 unsigned char *mascara4,
                 unsigned char *rotada1,
                 unsigned char *rotada2,
                 unsigned char *rotada3,
                 unsigned char *rotada4);



void rotar_pieza(unsigned char **tablero,
                 unsigned short &ancho,
                 short &posicion_pieza,
                 unsigned char *mascara1,
                 unsigned char *mascara2,
                 unsigned char *mascara3,
                 unsigned char *mascara4,
                 unsigned char *nueva1,
                 unsigned char *nueva2,
                 unsigned char *nueva3,
                 unsigned char *nueva4);

#endif // COMPORTAMIENTOSPIEZAS_H
