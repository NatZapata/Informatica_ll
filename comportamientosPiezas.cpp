#include "comportamientosPiezas.h"




void mover_izquierda(unsigned char **tablero,
                     short &posicion_pieza,
                     unsigned short &ancho,
                     unsigned char *mascara1,
                     unsigned char *mascara2,
                     unsigned char *mascara3,
                     unsigned char *mascara4){

    unsigned char *mascaras[4] = {mascara1, mascara2, mascara3, mascara4};
    short fila_tablero=0;
    unsigned char futura;

    // verificar borde izquierdo
    for(unsigned short f=0; f<4; f++){
        if(mascaras[f][0] & 128)
            return;
    }

    // verificar colisión lateral
    for(short f=0; f<4; f++){

        fila_tablero = posicion_pieza - 3 + f;

        if(fila_tablero < 0)
            continue;

        //Se recorren los bytes de la máscara.
        for(unsigned short i=0;i<ancho;i++){

            //unsigned char futura;
// Solución del problema de un byte se pierde. Se traslada al sigueinte byte
            if((i < ancho-1) && (mascaras[f][i+1] & 128))
                futura = (mascaras[f][i] << 1) | 1;
            else
                futura = mascaras[f][i] << 1;

            if(tablero[fila_tablero][i] & futura)
                return;
        }
    }

    // Aplicar el movimiento
    for(unsigned short m=0; m<4; m++){

        for(unsigned short i=0; i<ancho; i++){

            if(i < ancho-1 && (mascaras[m][i+1] & 128))
                mascaras[m][i] = (mascaras[m][i] << 1) | 1;
            else
                mascaras[m][i] <<= 1;

        }
    }
}

void mover_derecha(unsigned char **tablero,
                   short &posicion_pieza,
                   unsigned short &ancho,
                   unsigned char *mascara1,
                   unsigned char *mascara2,
                   unsigned char *mascara3,
                   unsigned char *mascara4){

    const short FILAS_PIEZA = 4;

    unsigned char *mascaras[4] =
        {mascara1, mascara2, mascara3, mascara4};

    // verificar borde derecho
    for(short f=0; f<4; f++){
        if(mascaras[f][ancho-1] & 1)
            return;
    }

    // verificar colisión lateral
    for(short f=0; f<FILAS_PIEZA; f++){

        short fila_tablero = posicion_pieza - (FILAS_PIEZA-1) + f;

        if(fila_tablero < 0)
            continue;

        for(unsigned short i=0;i<ancho;i++){

            unsigned char futura;

            if(i>0 && (mascaras[f][i-1] & 1))
                futura = (mascaras[f][i] >> 1) | 128;
            else
                futura = mascaras[f][i] >> 1;

            if(tablero[fila_tablero][i] & futura)
                return;
        }
    }

    // aplicar movimiento
    for(short f=0; f<FILAS_PIEZA; f++){

        for(int i = ancho-1; i >= 0; i--){

            if(i > 0 && (mascaras[f][i-1] & 1))
                mascaras[f][i] = (mascaras[f][i] >> 1) | 128;
            else
                mascaras[f][i] >>= 1;

        }
    }
}


bool bajar_pieza(unsigned char **tablero,
                 short &posicion_pieza,
                 unsigned short &ancho,
                 unsigned short &altura,
                 unsigned char *mascara1,
                 unsigned char *mascara2,
                 unsigned char *mascara3,
                 unsigned char *mascara4)
{
    const unsigned short FILAS = 4;
    bool colision = false;
    unsigned char bloque;
    short fila_tablero;

    unsigned char *mascaras[FILAS] =
        {
            mascara1,
            mascara2,
            mascara3,
            mascara4
        };



    // Revisar si la pieza puede bajar
    for(short f = FILAS-1; f >= 0 && !colision; f--)
    {
        short fila_tablero = posicion_pieza - (FILAS-1) + f;

        if(fila_tablero < 0)
            continue;

        for(unsigned short m = 0; m < ancho && !colision; m++)
        {
            bloque = mascaras[f][m];


            if(bloque == 0)
                continue;

            // choque con el suelo
            if(fila_tablero + 1 >= altura)
            {
                colision = true;
                break;
            }

            // choque con otra pieza
            if(tablero[fila_tablero + 1][m] & bloque)
            {
                colision = true;
                break;
            }
        }
    }

    // Si no hay colisión, se procede a bajar la pieza

    if(!colision)
    {
        posicion_pieza++;
        return false;
    }

    // Si hay colisión se procede a fijar la pieza
    for(short f = 0; f < FILAS; f++)
    {
        fila_tablero = posicion_pieza - (FILAS-1) + f;

        if(fila_tablero < 0)
            continue;

        for(unsigned short b = 0; b < ancho; b++)
        {
            tablero[fila_tablero][b] |= mascaras[f][b];
        }
    }

    return true;
}




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
                 unsigned char *nueva4){

    unsigned char *mascaras[4] = {mascara1, mascara2, mascara3, mascara4};
    unsigned char *nuevas[4]   = {nueva1, nueva2, nueva3, nueva4};
    unsigned char pieza[4][4]={};
    unsigned char rotada[4][4]={};
    unsigned char *mascara;

    short centro=0;
    short ancho_pieza=0;
    short byte=0;
    short bit=0;

    for(short f=0; f<4; f++)
        for(unsigned short i=0;i<ancho;i++)
            nuevas[f][i] = 0;

    short col_min = ancho<<3;
    short col_max = -1;

    for(unsigned short byte=0; byte<ancho; byte++){

        unsigned char combinado =
            mascaras[0][byte] |
            mascaras[1][byte] |
            mascaras[2][byte] |
            mascaras[3][byte];

        if(combinado){

            for(short bit=7; bit>=0; bit--){

                if((combinado>>bit)&1){

                    short col = (byte<<3) + (7-bit);

                    if(col < col_min) col_min = col;
                    if(col > col_max) col_max = col;
                }
            }
        }
    }

    if(col_max==-1){
        return;
    }

     centro = (col_min + col_max) / 2;
     ancho_pieza = col_max-col_min+1;



    for(unsigned short fila=0;fila<4;fila++){

         mascara = mascaras[fila];

        for(short col=0;col<ancho_pieza;col++){

            short bit_global = col_min+col;

            short byte = bit_global>>3;
            short bit = 7-(bit_global%8);

            pieza[fila][col] = (mascara[byte]>>bit)&1;
        }
    }


// Generación de la rotación de la matriz.
    for(unsigned short i=0;i<4;i++)
        for(unsigned short j=0;j<4;j++)
            rotada[j][3-i] = pieza[i][j];

    //se pone cada bit, de la matriz 4*4 en su posición global en las máscaras.

    for(short fila=0;fila<4;fila++){
        for(short col=0;col<4;col++){

            if(rotada[fila][col]){

                short bit_global = centro -1 + col;

                if((bit_global < 0) || (bit_global) >= (ancho<<3)){
                    return;
                }

                 byte = bit_global>>3;
                 bit = 7-(bit_global%8);

                nuevas[fila][byte] |= (1<<bit);
            }
        }
    }

    if(posicion_pieza>=3){

        for(unsigned short i=0;i<ancho;i++){

            if((tablero[posicion_pieza-3][i] & nuevas[0][i]) ||
                (tablero[posicion_pieza-2][i] & nuevas[1][i]) ||
                (tablero[posicion_pieza-1][i] & nuevas[2][i]) ||
                (tablero[posicion_pieza][i]   & nuevas[3][i])){

                return;
            }
        }
    }

    for(short f=0; f<4; f++)
        for(unsigned short i=0;i<ancho;i++)
            mascaras[f][i] = nuevas[f][i];
}


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
                 unsigned char *rotada4){
    switch (boton) {
    case 'a':{
        mover_izquierda(tablero,posicion,ancho, mascara1,mascara2,mascara3,mascara4);
        break;
    }

    case 'd':{
        mover_derecha(tablero,posicion,ancho, mascara1,mascara2,mascara3,mascara4);
        break;
    }
    case 's':{
        colision=bajar_pieza(tablero
                    ,posicion,
                    ancho,
                    altura,
                    mascara1,
                    mascara2,mascara3,mascara4);
    }
        break;
    case 'w':{
        rotar_pieza(tablero,
                    ancho,posicion,
                    mascara1,mascara2
                    ,mascara3,
                    mascara4,
                    rotada1,
                    rotada2,
                    rotada3,
                    rotada4);

        break;
    }
    }
}
