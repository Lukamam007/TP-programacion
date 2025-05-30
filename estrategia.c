#include "estrategia.h"
#include "simulador.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "turno.h"

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
    Pila* pila = pila_crear();
    int num_torre = 0;
    int exito = 0;  // 0 si no hay solución, 1 si sí
    for (int x = 0; x < mapa->alto; x++)
        for (int y = 0; y < mapa->ancho; y++)
            if (mapa->casillas[x][y] == TORRE)
                mapa->casillas[x][y] = VACIO;
    while (num_torre >= 0) {
        int encontrada = 0;
        for (int x = 0; x < mapa->alto && !encontrada; x++) {
            for (int y = 0; y < mapa->ancho && !encontrada; y++) {
                if (mapa->casillas[x][y] != VACIO)
                    continue;
                Coordenada pos = {x, y};
                Estado est = {pos, num_torre};
                mapa->casillas[x][y] = TORRE;
                pila_apilar(pila, est);
                num_torre++;
                encontrada = 1;
                if (num_torre == mapa->cant_torres) {
                    Nivel* copia = inicializar_nivel(nivel->camino->largo_camino, nivel->enemigos->cantidad, nivel->enemigos->vida_inicial);
                    for (int i = 0; i < copia->camino->largo_camino; i++)
                        copia->camino->posiciones[i] = nivel->camino->posiciones[i];

                    int vivos = simular_turno(mapa, copia, copia->camino->posiciones, copia->camino->largo_camino);

                    if (vivos == 0) {
                        liberar_nivel(copia);
                        exito = 1;
                        break;
                    }

                    liberar_nivel(copia);
                }
            }
        }

        if (!encontrada) {
            if (pila_es_vacia(pila))
                break;

            Estado est = pila_tope(pila);
            mapa->casillas[est.posicion.x][est.posicion.y] = VACIO;
            num_torre = est.idx_torre;
            pila_desapilar(pila);
        }
        if (exito == 1)
            break;
    }
    if (exito == 0) {
        while (!pila_es_vacia(pila)) {
            Estado est = pila_tope(pila);
            mapa->casillas[est.posicion.x][est.posicion.y] = VACIO;
            pila_desapilar(pila);
        }
    } else {
        for (int i = 0; i < mapa->cant_torres; i++)
            mapa->torres[i] = pila->datos[i].posicion;
    }
    pila_destruir(pila);
}
int comparar(const void *a, const void *b) {
    return ((area_ataque_de_casillas*)b)->ataque - ((area_ataque_de_casillas*)a)->ataque;
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada *posiciones_validas_torre = malloc(sizeof(Coordenada) * cantidad_casillas);
    int cant_torres = mapa -> cant_torres;
    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);
    area_ataque_de_casillas casillas_ataque[cant_validas];
    posiciones_validas_torre = realloc(posiciones_validas_torre,sizeof(Coordenada) * cant_validas);
    for(int j = 0 ; j < cant_validas ; j++){
           casillas_ataque[j].x = posiciones_validas_torre[j].x;
           casillas_ataque[j].y = posiciones_validas_torre[j].y;
           casillas_ataque[j].ataque =  contarVecinosCamino(posiciones_validas_torre[j].x, posiciones_validas_torre[j].y , mapa, mapa -> distancia_ataque);
    }

qsort(casillas_ataque, cant_validas, sizeof(area_ataque_de_casillas), comparar);

 for(int nroTorre = 0 ;nroTorre < cant_torres; nroTorre++){
	colocar_torre(mapa, casillas_ataque[nroTorre].x, casillas_ataque[nroTorre].y, nroTorre);
}

    free(posiciones_validas_torre);

    return;
}


int contarVecinosCamino(int posicion_torre_x, int posicion_torre_y , Mapa* mapa,int distancia_ataque) {

 int vecinos = 0;
 for (int dx = -distancia_ataque; dx <= distancia_ataque; dx++) {
        for (int dy = -distancia_ataque; dy <= distancia_ataque; dy++) {
            int nuevo_x = posicion_torre_x + dx;
            int nuevo_y = posicion_torre_y + dy;

            if (dx == 0 && dy == 0) continue;
            if (nuevo_x < 0 || nuevo_y < 0) continue;
            if (nuevo_x >= mapa->alto || nuevo_y >= mapa->ancho) continue;

	if (mapa->casillas[nuevo_x][nuevo_y] == CAMINO) 
                vecinos++;
           
        }
    }

    return vecinos;
}

