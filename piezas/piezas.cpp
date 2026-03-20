
#include "piezas.h"
#include <iostream>


// acá ya entra el ancho en bytes, es decir lo que el usuario ingresa dividido entre 8

void crear_pieza_aleatoria(unsigned short &ancho_matriz,unsigned short &numero_pieza,unsigned char *primera_mascara,
                           unsigned char *segunda_mascara, unsigned char *tercera_mascara,
                           unsigned char *cuarta_mascara){


    // unsigned char numero_pieza= 2;
    unsigned short columna_central= (ancho_matriz<<2);
    unsigned short byte_centro = (columna_central>>3);


    unsigned short bit_centro  = columna_central% 8;




    for(unsigned short i = 0; i < ancho_matriz; i++){
        primera_mascara[i] = 0;
        segunda_mascara[i] = 0;
        tercera_mascara[i] = 0;
        cuarta_mascara[i] = 0;
    }


    switch (numero_pieza) {
        //Forma de linea
    case 1:{
        //creación de la pieza
        primera_mascara[byte_centro]|=(1<<(7-bit_centro));
        segunda_mascara[byte_centro]|=(1<<(7-bit_centro));
        tercera_mascara[byte_centro]|=(1<<(7-bit_centro));
        cuarta_mascara[byte_centro]|=(1<<(7-bit_centro));


        break;
    }
    //Forma de cuadradro macizo
    case 2:{
        if((byte_centro!=0&&byte_centro!=1)||((ancho_matriz)*8==16))byte_centro -= 1;
        bit_centro  = columna_central% 8;
        if(bit_centro <= 6){
            tercera_mascara[byte_centro] |= (3 << (bit_centro));
            cuarta_mascara[byte_centro]  |= (3 << (bit_centro));
        }
        else{ // bit_centro == 7
            tercera_mascara[byte_centro]     |= (1 << 7);
            tercera_mascara[byte_centro + 1] |= 1;

            cuarta_mascara[byte_centro]      |= (1 << 7);
            cuarta_mascara[byte_centro + 1]  |= 1;
        }

        break;
    }
    case 3:{ // pieza T
        if((byte_centro!=0&&byte_centro!=1)||((ancho_matriz)*8==16)){
            byte_centro -= 1;

        }

        bit_centro  = (columna_central% 8);

        // fila inferior: XXX
        if(bit_centro >= 1 && bit_centro <= 6){
            tercera_mascara[byte_centro] |= (7 << (bit_centro - 1));
        }
        else if(bit_centro == 0){
            tercera_mascara[byte_centro] |= 3;
            tercera_mascara[byte_centro+1] |= (1<<7);
        }
        else{ // bit_centro == 7
            tercera_mascara[byte_centro] |= (3 << 6);
            tercera_mascara[byte_centro + 1] |= 1;
        }

        // fila superior: .X.
        segunda_mascara[byte_centro] |= (1 << bit_centro);

        break;
    }
    case 4:{ // L
        if((byte_centro!=0&&byte_centro!=1)||((ancho_matriz)*8==16)){
            byte_centro -= 1;

        }
        bit_centro  = (columna_central% 8);


        // fila inferior: XXX
        if(bit_centro >= 1 && bit_centro <= 6){
            tercera_mascara[byte_centro] |= (7 << (bit_centro-1 ));
        }
        else if(bit_centro == 0){
            tercera_mascara[byte_centro] |= 3;
            tercera_mascara[byte_centro + 1] |= 128;
        }
        else{ // bit 7
            tercera_mascara[byte_centro] |= (3 << 6);
            tercera_mascara[byte_centro  +1] |= (1<<7);
        }

        // bloque superior derecho
        unsigned short col = bit_centro + 1;
        unsigned short byte = byte_centro;
        if(col >= 8){
            col = 0;
            byte++;
        }

        segunda_mascara[byte] |= (1 << col);

        break;
    }
    default: { // L
        if((byte_centro!=0&&byte_centro!=1)||((ancho_matriz)*8==16)){
            byte_centro -= 1;

        }
        bit_centro  = (columna_central% 8);


        // fila inferior: XXX
        if(bit_centro >= 1 && bit_centro <= 6){
            segunda_mascara[byte_centro] |= (7 << (bit_centro-1 ));
        }
        else if(bit_centro == 0){
            segunda_mascara[byte_centro] |= 3;
            segunda_mascara[byte_centro + 1] |= 128;
        }
        else{ // bit 7
            segunda_mascara[byte_centro] |= (3 << 6);
            segunda_mascara[byte_centro  +1] |= (1<<7);
        }

        // bloque superior derecho
        unsigned short col = bit_centro + 1;
        unsigned short byte = byte_centro;
        if(col >= 8){
            col = 0;
            byte++;
        }

        tercera_mascara[byte] |= (1 << col);

        break;
    }



    }


}

bool game_over(unsigned char **tablero,
               unsigned short ancho_matriz,
               unsigned char numero_pieza,
               unsigned char *m1,
               unsigned char *m2,
               unsigned char *m3,
               unsigned char *m4)
{
    unsigned char *pieza[4] = {m1,m2,m3,m4};

    unsigned short filas_a_revisar = 4;

    // según la pieza solo revisamos las filas que realmente usa
    switch(numero_pieza)
    {
    case 1: filas_a_revisar = 4; break; // línea vertical
    case 2: filas_a_revisar = 2; break; // cuadrado
    case 3: filas_a_revisar = 2; break; // T
    case 4: filas_a_revisar = 2; break; // L
    default: filas_a_revisar = 2; break;
    }

    for(unsigned short f = 0; f < filas_a_revisar; f++)
    {
        for(unsigned short b = 0; b < ancho_matriz; b++)
        {
            if(tablero[f][b] & pieza[f][b])
                return true;
        }
    }

    return false;


