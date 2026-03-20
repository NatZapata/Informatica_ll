#include "Tablero.h"


unsigned char ** crear_tablero(unsigned short &ancho, unsigned short &altura){

    // verificación de entrada de datos

    //Cuerpo principal de la función

    //Uso de memoria dinámica, Esta será la base de los arreglos.
    unsigned char **tablero= new unsigned char *[altura];

    for(unsigned short i=0;i<altura;i++){
        *(tablero+i)= new unsigned char[ancho];
    }
    for(unsigned short i=0;i<altura;i++){
        for(unsigned short j=0;j<(ancho);j++){
            *(*(tablero+i)+j)=0;
        }
    }

    return tablero;


}





void dibujar_matriz(unsigned char** matriz,
                    unsigned short &ancho,
                    unsigned short &altura){
    bool bit=0;
    for(unsigned short i=0;i<altura;i++){
        cout<<"             ";
        for(int j=0;j<((ancho));j++){
            //ciclo que recorre los bits del número
            for( short k=7;k>=0;k--){
                bit=((*(*(matriz+i)+j))>>k)&1;
                if(bit){
                    cout<<"  "<<">";
                } else{
                    cout<<"  "<<".";
                }
            }
        }
        cout<<endl;
    }
}
//Esta función no almacena nada, solo muestra por terminal una
//superposición del tablero y la pieza.
void dibujar_pieza_temporal(unsigned char **tablero,
                            short &posicion_pieza,
                            unsigned short &ancho,
                            unsigned short &altura,
                            unsigned char *mascara1,
                            unsigned char *mascara2,
                            unsigned char *mascara3,
                            unsigned char *mascara4){

    unsigned char segmento;
    short bit=0;

    for(unsigned short i=0;i<altura;i++){

        cout<<"             ";

        for(unsigned short k=0;k<ancho;k++){

            segmento = tablero[i][k];

            if(i == posicion_pieza-3)
                segmento |= mascara1[k];

            else if(i == posicion_pieza-2)
                segmento |= mascara2[k];

            else if(i == posicion_pieza-1)
                segmento |= mascara3[k];

            else if(i == posicion_pieza)
                segmento |= mascara4[k];


            for(short j=7;j>=0;j--){

                bit = (segmento >> j) & 1;

                if(bit)
                    cout<<" >";
                else
                    cout<<" .";
            }
        }

        cout<<endl;
    }
}
/*Pone la pieza definitivamente en el tablero
 * solo se pone la pieza en el tablero si colisiona.
 */
void poner_pieza(unsigned char **tablero,
                 short &posicion_pieza,
                 unsigned short &ancho,
                 unsigned short &altura,
                 unsigned char *mascara1,
                 unsigned char *mascara2,
                 unsigned char *mascara3,
                 unsigned char *mascara4){

    unsigned char *mascaras[4] = {mascara1, mascara2, mascara3, mascara4};

    for(short f = 0; f < 4; f++){

        short fila_tablero = posicion_pieza - 3 + f;

        if(fila_tablero >= 0 && fila_tablero < altura){

            for(unsigned short i = 0; i < ancho; i++){

                tablero[fila_tablero][i] |= mascaras[f][i];

            }
        }
    }
}

/*Función encargada de eliminar,
 * detecta con una máscara si una linea esta llena.
 * Luego, con la manipulación de los punteros se bajan las filas.

*/
void eliminar_fila(unsigned char **tablero,
                   unsigned short &ancho,
                   unsigned short &altura){

    bool eliminar;

    for(unsigned short i=0;i<altura;i++){

        eliminar=true;

        for(unsigned short m=0;m<ancho;m++){

            if((tablero[i][m]^255)!=0){
                eliminar=false;
            }

        }

        if(eliminar){

            for(short k=i;k>0;k--){

                for(unsigned short m=0;m<ancho;m++){
                    //*(*(tablero + k) + m) = *(*(tablero + (k - 1)) + m);
                    tablero[k][m]=tablero[k-1][m];
                }

            }

            for(unsigned short m=0;m<ancho;m++){
                tablero[0][m]=0;
            }

            i--;
        }
    }
}


