#include <iostream>
#include <ctime>

#include "Tablero.h"
#include "Piezas.h"
#include "comportamientosPiezas.h"

using namespace std;

int main(){

    srand(time(0));




    unsigned short ancho = 34;
    unsigned short altura = 11;

    short posicion_pieza_actual = 0;

    bool terminar_juego = false;
    bool colision = false;

    char letra;

    cout << "Ingrese el ancho del tablero (multiplo de 8): ";
    while (!(cin >> ancho) || (ancho % 8 != 0) || (ancho < 8)) {
        cout << "Entrada invalida (debe ser numero y multiplo de 8). Intente de nuevo: ";
        cin.clear();
        cin.ignore(10, '\n');
    }

    cout << "Ingrese la altura del tablero: ";
    while (!(cin >> altura) || (altura <8)) {
        cout << "Entrada invalida. Intente de nuevo: ";
        cin.clear();
        cin.ignore(10, '\n');
    }




    // Crear tablero
    ancho>>=3;
    unsigned char **tablero = crear_tablero(ancho,altura);

    // Máscaras de la pieza
    unsigned char *primera_mascara = new unsigned char[ancho];
    unsigned char *segunda_mascara = new unsigned char[ancho];
    unsigned char *tercera_mascara = new unsigned char[ancho];
    unsigned char *cuarta_mascara  = new unsigned char[ancho];

    // Máscaras para rotación
    unsigned char *rotada1 = new unsigned char[ancho];
    unsigned char *rotada2 = new unsigned char[ancho];
    unsigned char *rotada3 = new unsigned char[ancho];
    unsigned char *rotada4 = new unsigned char[ancho];
    bool game_over_j=false;
    unsigned short numero_pieza= (rand()%5)+1;





    // Crear primera pieza
    crear_pieza_aleatoria(ancho,numero_pieza,
                          primera_mascara,
                          segunda_mascara,
                          tercera_mascara,
                          cuarta_mascara);

    while(!terminar_juego){
        numero_pieza=(rand()%5)+1;



        cout << endl;

        dibujar_pieza_temporal(tablero,
                               posicion_pieza_actual,
                               ancho,
                               altura,
                               primera_mascara,
                               segunda_mascara,
                               tercera_mascara,
                               cuarta_mascara);

        cout << endl;

        cout<<"Ingrese un boton: [a] izquierda [d] derecha [s] abajo [w] rotar [q] salir: ";
        cin>>letra;

        if(letra=='q'){
            break;
        }
        cout << "posicion_pieza_actual: " << posicion_pieza_actual << endl;
        if(posicion_pieza_actual>altura){
            posicion_pieza_actual=altura;
        }

        movimientos(tablero,
                    posicion_pieza_actual,
                    letra,
                    colision,
                    ancho,
                    altura,
                    primera_mascara,
                    segunda_mascara,
                    tercera_mascara,
                    cuarta_mascara,
                    rotada1,
                    rotada2,
                    rotada3,
                    rotada4);

        if(colision || posicion_pieza_actual==altura){


            poner_pieza(tablero,
                        posicion_pieza_actual,
                        ancho,
                        altura,
                        primera_mascara,
                        segunda_mascara,
                        tercera_mascara,
                        cuarta_mascara);

            eliminar_fila(tablero,ancho,altura);

            // nueva pieza
            crear_pieza_aleatoria(ancho,numero_pieza,
                                  primera_mascara,
                                  segunda_mascara,
                                  tercera_mascara,
                                  cuarta_mascara);

            game_over_j= game_over(tablero,
                                    ancho,numero_pieza,
                                    primera_mascara,
                                    segunda_mascara,
                                    tercera_mascara,
                                    cuarta_mascara);
            if(game_over_j){

                cout<<"Game Over "<<"";
                break;
            }

            posicion_pieza_actual = 3;

            colision = false;
        }

    }

    // liberar memoria
    for(unsigned short i=0;i<altura;i++){
        delete[] tablero[i];
    }

    delete[] tablero;

    delete[] primera_mascara;
    delete[] segunda_mascara;
    delete[] tercera_mascara;
    delete[] cuarta_mascara;

    delete[] rotada1;
    delete[] rotada2;
    delete[] rotada3;
    delete[] rotada4;

    return 0;
}

