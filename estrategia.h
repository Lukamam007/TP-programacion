#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include "mapa.h"
#include "nivel.h"
#include "pilas.c"

typedef void (*DisposicionTorres)(Nivel*, Mapa*);

typedef struct _area_ataque_de_casillas{
	      int x,y;
        int ataque;
}area_ataque_de_casillas;

void disponer(Nivel* nivel, Mapa* mapa);

void disponer_con_backtracking(Nivel* nivel, Mapa* mapa);

void disponer_custom(Nivel* nivel, Mapa* mapa);

int contarVecinosCamino(int posicion_torre_x, int posicion_torre_y , Mapa* mapa,int distancia_ataque);

int comparar(const void *a, const void *b);


#endif
