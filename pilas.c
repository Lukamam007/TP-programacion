#include "pilas.h"
#include "mapa.h"

Pila* pila_crear(Mapa* mapa) {
    Pila* p = malloc(sizeof(Pila));
    p->datos = malloc(sizeof(Estado) * mapa -> cant_torres);
    p->ultimo = 0;
    return p;
}

int pila_es_vacia(Pila* p) {
    return p->ultimo == 0;
}

Estado pila_tope(Pila* p) {
    if (pila_es_vacia(p)) {
        Estado vacio = {{-1, -1}, -1};
        return vacio;
    }
    return p->datos[p->ultimo - 1];
}

void pila_apilar(Pila* p, Estado e) {
    p->datos[p->ultimo++] = e;
}

void pila_desapilar(Pila* p) {
    if (!pila_es_vacia(p))
        p->ultimo--;
}

void pila_imprimir(Pila* p) {
    for (int i = 0; i < p->ultimo; i++)
        printf("(%d, %d) idx: %d\n", p->datos[i].posicion.x, p->datos[i].posicion.y, p->datos[i].num_torre);
}

void pila_destruir(Pila* p) {
    free(p->datos);
    free(p);
}
