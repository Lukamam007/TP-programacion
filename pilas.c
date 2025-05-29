#include "pilas.h"
#include "mapa.h"
int MAX_PILA = mapa->cant_torres;
Pila* pila_crear() {
    Pila* p = malloc(sizeof(Pila));
    p->datos = malloc(sizeof(Estado) * MAX_PILA);
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
    if (p->ultimo == MAX_PILA) {
        MAX_PILA += 10;
        p->datos = realloc(p->datos, sizeof(Estado) * MAX_PILA);
    }
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
