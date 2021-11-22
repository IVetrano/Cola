#include "cola.h"

#include <stdlib.h>
#include <stdio.h>

//Nodos
typedef struct nodo{
	void* dato;
	struct nodo* prox;
} nodo_t;

nodo_t* nodo_crear(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

void nodo_destruir(nodo_t* nodo){
	free(nodo);
}



//Cola
struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};


cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));

	if(!cola) return NULL;

	cola->primero = NULL;
	cola->ultimo = NULL;

	return cola;
}

bool cola_esta_vacia(const cola_t* cola){
	return cola->primero == NULL && cola->ultimo == NULL;
}

void* cola_ver_primero(const cola_t* cola){
	if(cola_esta_vacia(cola)) return NULL;
	return cola->primero->dato;
}

void cola_destruir(cola_t* cola, void (*destruir_dato)(void*)){
	while (!cola_esta_vacia(cola)){
		void* dato = cola_desencolar(cola);
		if (destruir_dato) destruir_dato(dato);
	}
	
	free(cola);
}

bool cola_encolar(cola_t* cola, void* valor){
	nodo_t* nuevo = nodo_crear(valor);
	if (!nuevo) return false;

	if (cola_esta_vacia(cola)) cola->primero = nuevo;

	else cola->ultimo->prox = nuevo;

	cola->ultimo = nuevo;
	return true;
}

void* cola_desencolar(cola_t* cola){
	if (cola_esta_vacia(cola)) return NULL;

	void* dato = cola->primero->dato;
	nodo_t* nodo = cola->primero;
	cola->primero = cola->primero->prox;
	nodo_destruir(nodo);

	if (!cola->primero) cola->ultimo = NULL;

	return dato;
}