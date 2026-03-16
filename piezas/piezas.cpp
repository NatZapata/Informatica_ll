#include "piezas.h"

void crear_pieza_aleatoria(unsigned short &ancho_matriz,unsigned char *primera_mascara,
                           unsigned char *segunda_mascara, unsigned char *tercera_mascara,
                           unsigned char *cuarta_mascara){

    unsigned char numero_pieza= (rand()%5)+1;
    unsigned short mitad_fila=(ancho_matriz)>>1;

    for(unsigned short i = 0; i < ancho_matriz; i++){
        primera_mascara[i] = 0;
        segunda_mascara[i] = 0;
        tercera_mascara[i] = 0;
        cuarta_mascara[i] = 0;
    }


    switch (numero_pieza) {
        //Forma de linea
    case 1:{
        for(unsigned short i=0;i< ancho_matriz;i++){
            if(i==mitad_fila){
                *(primera_mascara+i)=1;
                *(segunda_mascara+i)=1;
                *(tercera_mascara+i)=1;
                *(cuarta_mascara+i)=1;

            }

        }

        break;
    }
    //Forma de cuadradro macizo
    case 2:{
        for(unsigned short i=0;i< ancho_matriz;i++){
            if(i==mitad_fila ||  i==mitad_fila+1){
                *(primera_mascara+i)=1;
                *(segunda_mascara+i)=1;
                // *(tercera_mascara+i)=0;
                // *(cuarta_mascara+i)=0;

            }
        }
        break;
    }
    case 3:{
        //Forma de T
        for(unsigned short i=0;i< ancho_matriz;i++){
            if(i==mitad_fila || i==mitad_fila-1 || i==mitad_fila+1){
                *(primera_mascara+i)=1;
                //*(tercera_mascara+i)=0;
                //*(cuarta_mascara+i)=0;
                if(i==mitad_fila){
                    *(segunda_mascara+i)=1;
                }

            }
        }


        break;
    }
    case 4:{
        //Forma de L
        for(unsigned short i=0;i< ancho_matriz;i++){
            if(i==mitad_fila){
                *(primera_mascara+i)=1;
                *(segunda_mascara+i)=1;
                *(tercera_mascara+i)=1;
                // *(cuarta_mascara+i)=0;

            } else if(i==mitad_fila-1){
                *(tercera_mascara+i)=1;

            }
        }
        break;

    }
    default:{
        for(unsigned short i=0;i< ancho_matriz;i++){
            if(i==mitad_fila){
                *(primera_mascara+i)=1;
                *(segunda_mascara+i)=1;
                *(tercera_mascara+i)=1;
                //  *(cuarta_mascara+i)=0;

            } else if(i==mitad_fila+1){
                *(tercera_mascara+i)=1;

            }
        }
        break;
    }


    }


}


void poner_pieza(unsigned char **tablero,short posicion_pieza){
    if(posicion_pieza==0){

    }

}



