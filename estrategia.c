#include "estrategia.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static int posiciones_validas(Coordenada *validas, TipoCasilla **casillas, int alto, int ancho) {
    int cant_posiciones_validas = 0;
    
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (casillas[i][j] == VACIO) {
                validas[cant_posiciones_validas].x = i;
                validas[cant_posiciones_validas++].y = j;
            }
        }
    }

    return cant_posiciones_validas;
}

static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = TORRE;
}

static int determinar_posicion_torre(int *casilla_elegida, int cant_validas) {
    int nueva_posicion = rand() % cant_validas;
    while(casilla_elegida[nueva_posicion])
        nueva_posicion = rand() % cant_validas;

    return nueva_posicion;
}


void disponer(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int casilla_elegida[cantidad_casillas];
    for(int i = 0; i < cantidad_casillas; casilla_elegida[i++] = 0);

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre = determinar_posicion_torre(casilla_elegida, cant_validas);
        casilla_elegida[nueva_torre] = 1;
        int nueva_torre_x = posiciones_validas_torre[nueva_torre].x;
        int nueva_torre_y = posiciones_validas_torre[nueva_torre].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
}

void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int cant_torres = mapa -> cant_torres;
    int colocadas = 0;
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);
    for(int j = 0 ; j < cant_validas && !cant_torres ; j++){
        if(contarVecinosCamino(posiciones_validas_torre[j].x, posiciones_validas_torre[j].y,mapa) > 3){
            int nueva_torre_x = posiciones_validas_torre[j].x;
            int nueva_torre_y = posiciones_validas_torre[j].y;
            colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
            cant_torres--;
            colocadas++;
        } 
    }
    return;
}

int contarVecinosCamino(int posicion_torre_x, int posicion_torre_y , Mapa* mapa) {
    int vecinos = 0;
    int desplazamientos[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Arriba izquierda, arriba, arriba derecha
        {0, -1},         {0, 1},   // Izquierda, derecha
        {1, -1}, {1, 0}, {1, 1}    // Abajo izquierda, abajo, abajo derecha
    };

    for (int i = 0; i < 8; i++) {
        int nuevaFila = posicion_torre_y + desplazamientos[i][0];
        int nuevaColumna = posicion_torre_x + desplazamientos[i][1];

        // Verificar que esté dentro de los límites del tablero
        if (nuevaFila >= 0 && nuevaFila < mapa->ancho && nuevaColumna >= 0 && nuevaColumna < mapa->alto) {
            if (mapa->casillas[nuevaFila][nuevaColumna] = CAMINO) {
                vecinos++;
            }
        }
    }

    return vecinos;
}

