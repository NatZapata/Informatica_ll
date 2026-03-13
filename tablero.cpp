#include "Tablero.h"

unsigned char ** crear_tablero(unsigned short ancho, unsigned short altura){

    // verificación de entrada de datos
    while(ancho<8){
        cout<<"el ancho debe ser mayor o igual a 8 "<< endl;
        cout<<"Ingrese un nuevo valor: ";
        cin >> ancho;
    }
    while(ancho%8 !=0){
        cout<<"El ancho debe ser un multiplo de 8"<<endl;
        cout<<"Ingrese un nuevo valor de ancho: ";
        cin >> ancho;
    }
    while(altura<8){
        cout<<"La altura debe ser mayor o igual a 8 "<< endl;
        cout<<"Ingrese un nuevo valor de altura: ";
        cin >> altura;
    }

    //Cuerpo principal de la función

    //Uso de memoria dinámica, Esta será la base de los arreglos.
    unsigned char **tablero= new unsigned char *[altura];

    for(unsigned short i=0;i<altura;i++){
        *(tablero+i)= new unsigned char[ancho];
    }
    for(unsigned short i=0;i<altura;i++){
        for(unsigned short j=0;j<ancho;j++){
            *(*(tablero+i)+j)=0;
        }
    }

    return tablero;


}
