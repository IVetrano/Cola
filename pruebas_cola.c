#include "cola.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>


static void prueba_cola_vacia(void){
    cola_t* cola = cola_crear();
    print_test("Se pudo crear la cola", cola != NULL);
    print_test("Prueba cola vacia al ser creada", cola_esta_vacia(cola));
    print_test("Al ver primero vacia recibo NULL", cola_ver_primero(cola) == NULL);
    print_test("Al desencolar vacia recibo NULL", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
}

static void prueba_unico_elem(void){
	cola_t* cola = cola_crear();
	int a;

	print_test("Prueba encolar un elemento", cola_encolar(cola, &a));
	print_test("Prueba ver primero", cola_ver_primero(cola) == &a);
	print_test("Prueba desencolar unico elemento", cola_desencolar(cola) == &a);
	cola_destruir(cola, NULL);
}


static void prueba_invariante(void){
	int arreglo[] = {1, 2, 3};
	cola_t* cola = cola_crear();

	print_test("Se pudo crear la cola", cola != NULL);
	print_test("Se pudo encolar el elemento A", cola_encolar(cola, &arreglo[0]));
	print_test("Ahora al ver primero recibo a A", cola_ver_primero(cola) == &arreglo[0]);
	print_test("Se pudo encolar el elemento B", cola_encolar(cola, &arreglo[1]));
	print_test("Al ver primero sigo recibiendo A", cola_ver_primero(cola) == &arreglo[0]);
	print_test("La cola no esta vacia", !cola_esta_vacia(cola));
	print_test("Al desencolar recibo A", cola_desencolar(cola) == &arreglo[0]);
	print_test("Ahora al ver primero recibo B", cola_ver_primero(cola) == &arreglo[1]);
	print_test("Se pudo encolar C", cola_encolar(cola, &arreglo[2]));
	print_test("El primer elemento sigue siendo B", cola_ver_primero(cola) == &arreglo[1]);
	print_test("Al desencolar recibo B", cola_desencolar(cola) == &arreglo[1]);
	print_test("Ahora el primero es C", cola_ver_primero(cola) == &arreglo[2]);
	print_test("La cola no esta vacia", !cola_esta_vacia(cola));
	print_test("Al desencolar recibo C", cola_desencolar(cola) == &arreglo[2]);
	print_test("Ahora la cola esta vacia", cola_esta_vacia(cola));
	print_test("Al intentar desencolar recibo NULL", cola_desencolar(cola) == NULL);
	print_test("Al intentar ver primero recibo NULL", cola_ver_primero(cola) == NULL);
	print_test("Se pudo encolar A", cola_encolar(cola, &arreglo[0]));
	print_test("Se pudo encolar B", cola_encolar(cola, &arreglo[1]));
	print_test("Se pudo encolar C", cola_encolar(cola, &arreglo[2]));
	print_test("Ahora la cola no esta vacia", !cola_esta_vacia(cola));
	print_test("Al ver primero recibo A", cola_ver_primero(cola) == &arreglo[0]);
	print_test("Al desencolar recibo A", cola_desencolar(cola) == &arreglo[0]);
	print_test("Al desencolar recibo B", cola_desencolar(cola) == &arreglo[1]);
	print_test("Al desencolar recibo C", cola_desencolar(cola) == &arreglo[2]);
	print_test("Ahora la cola esta vacia", cola_esta_vacia(cola));



	cola_destruir(cola, NULL);
}

static void prueba_volumen(void){
	bool encolar = true;
	bool desencolar = true;
	bool ver_primero = true;
	int arreglo[1000];
	cola_t* cola = cola_crear();

	for (int i = 0; i < 1000; i++){
		encolar &= cola_encolar(cola, &arreglo[i]);
		ver_primero &= cola_ver_primero(cola) == &arreglo[0];
	}

	print_test("Se pudieron encolar 1000 elementos", encolar);
	print_test("Al ver primero las 1000 veces recibi el primer elemento encolado", ver_primero);
	print_test("La cola no esta vacia", !cola_esta_vacia(cola));

	ver_primero = true;

	for (int i = 0; i < 1000; i++){
		ver_primero &= cola_ver_primero(cola) == &arreglo[i];
		desencolar &= cola_desencolar(cola) == &arreglo[i];
	}

	print_test("Al desencolar se recibio el elemento correcto siempre", desencolar);
	print_test("Al ver primero las 1000 veces se recibio el elemento esperado", ver_primero);
	print_test("Ahora la cola esta vacia", cola_esta_vacia(cola));

	
	cola_destruir(cola, NULL);

}

static void prueba_encolar_NULL(void){
	void* a = NULL;

	cola_t* cola = cola_crear();

	print_test("Se pudo encolar NULL", cola_encolar(cola, &a));
	print_test("La cola no esta vacia al encolar NULL", !cola_esta_vacia(cola));
	print_test("Al ver primero recibo el puntero a NULL que encole", cola_ver_primero(cola) == &a);
	print_test("Al desencolar recibo el puntero a NULL que encole", cola_desencolar(cola) == &a);
	print_test("Ahora la cola si esta vacia", cola_esta_vacia(cola));

	cola_destruir(cola, NULL);
}

static void prueba_vaciado(){
	cola_t* cola = cola_crear();
	int a;
	print_test("Se pudo encolar 1 elemento", cola_encolar(cola, &a));
	print_test("Al desencolar el elemento recibi el encolado", cola_desencolar(cola) == &a);

	//Ahora esta vacia => pruebo si funciona como una nueva

	print_test("Ahora la cola esta vacia", cola_esta_vacia(cola));
	print_test("Se puede encolar elementos despues de vaciar la cola", cola_encolar(cola, &a));
	print_test("Al ver primero recibo el elemento encolado", cola_ver_primero(cola) == &a);
	print_test("Ahora la cola no esta vacia", !cola_esta_vacia(cola));
	print_test("Al desencolar recibo el elemento que encole", cola_desencolar(cola) == &a);

	cola_destruir(cola, NULL);
}

static void prueba_destruir_vacia_sin_funcion(){
	cola_t* cola = cola_crear();
	cola_destruir(cola, NULL);
	print_test("Se destruyo una cola sin elementos ni funcion para destruirlos", true);
}

static void prueba_destruir_no_vacia_sin_funcion(){
	bool encolar = true;
	int arreglo[3];
	cola_t* cola = cola_crear();

	for (int i = 0; i < 3; i++){
		encolar &= cola_encolar(cola, &arreglo[i]);
	}
	print_test("Se pudieron encolar 3 elementos", encolar);

	cola_destruir(cola, NULL);
	print_test("Se destruyo una cola con elementos pero sin funcion para destruir elementos", true);
}

static void prueba_destruir_vacia_con_funcion(){
	cola_t* cola = cola_crear();
	cola_destruir(cola, free);
	print_test("Se destruyo una cola sin elementos pero con funcion para destruir los elementos", true);
}

static void prueba_destruir_no_vacia_con_funcion(){
	//Uso memoria dinamica => le paso a cola_destruir "free()" como funcion
	//de destruccion de datos.

	int* arreglo[10];
	bool encolar = true;

	for (int i = 0; i < 10; i++){
		arreglo[i] = malloc(sizeof(int));
	}

	cola_t* cola = cola_crear();
	for(int i = 0; i < 10; i++){
		encolar &= cola_encolar(cola, arreglo[i]);
	}

	print_test("Se pudieron encolar 10 elementos", encolar);

	cola_destruir(cola, free);
	print_test("Se destruyo una cola con elementos y con funcion para destruirlos", true);

}

void pruebas_cola_estudiante(void){
	prueba_cola_vacia();
	prueba_invariante();
	prueba_volumen();
	prueba_unico_elem();
	prueba_encolar_NULL();
	prueba_vaciado();
	prueba_destruir_vacia_sin_funcion();
	prueba_destruir_vacia_con_funcion();
	prueba_destruir_no_vacia_sin_funcion();
	prueba_destruir_no_vacia_con_funcion();
}


#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
