#ifndef PILA_H
#define PILA_H

#include <stdlib.h>
#include <stdio.h>
#include "nivel.h" 
#include "mapa.h"

typedef struct {
    Coordenada posicion;
    int num_torre;
} Estado;

extern int MAX_PILA;

typedef struct _Pila {
    Estado *datos;
    int ultimo;
} Pila;

Pila* pila_crear(Mapa*);
int pila_es_vacia(Pila*);
Estado pila_tope(Pila*);
void pila_apilar(Pila*, Estado);
void pila_desapilar(Pila*);
void pila_imprimir(Pila*);
void pila_destruir(Pila*);

#endif
