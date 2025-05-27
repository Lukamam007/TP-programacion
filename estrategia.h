#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include "mapa.h"
#include "nivel.h"
#include "pilas.c"
typedef void (*DisposicionTorres)(Nivel*, Mapa*);

void disponer(Nivel* nivel, Mapa* mapa);

void disponer_con_backtracking(Nivel* nivel, Mapa* mapa);

void disponer_custom(Nivel* nivel, Mapa* mapa);

int contarVecinosCamino(int posicion_torre_x, int posicion_torre_y , Mapa* mapa);

#endif
