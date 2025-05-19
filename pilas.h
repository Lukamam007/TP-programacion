typedef struct _Pila {
    int datos[MAX_PILA];
    int ultimo;
} Pila;

Pila* pila_crear();
int pila_es_vacia(Pila*); 
int pila_tope(Pila*); 
void pila_apilar(Pila*,int); 
void pila_desapilar(Pila*); 
void pila_imprimir(Pila*); 
void pila_destruir(Pila*); 
