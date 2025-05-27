#include "pilas.h"

Pila* pila_crear(){
    Pila* coba;
    coba = malloc(sizeof(Pila));
    coba -> ultimo = 0;
    return coba;
}
int pila_es_vacia(Pila* koba){
     if(koba->ultimo == 0)
        return 1;
     return 0;
 }
 int pila_tope(Pila* koba){
    if(koba->ultimo == 0)
        return -1;
    int ultimo_aux = koba->ultimo;
    ultimo_aux  --;
    int nro = koba->datos[ultimo_aux];
    return nro;
 }
 void pila_apilar(Pila* koba, int numero){
      koba->datos[koba->ultimo] = numero;
      koba->ultimo += 1;
}
 void pila_desapilar(Pila* koba){
      koba-> ultimo -= 1; 
}
 void pila_imprimir(Pila* koba){
    for(int i = 0; i < koba->ultimo; i++)
        printf("%d\n", koba->datos[i]);
}       
void pila_destruir(Pila* koba){
    free(koba);
}
