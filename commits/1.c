#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include <stdio.h>
#define TAM_INI 190

// Faltan las funciones heapify y crear_vector_ARr
struct heap{
  void** datos;
  size_t tam;
  size_t largo;
  cmp_func_t cmp;
};

heap_t* creador(size_t largo){
  heap_t* heap = malloc(sizeof(heap_t));
  
  if(!heap) return NULL;
  heap->datos = malloc(sizeof(void*) * largo);
  
  if(!heap->datos){
    free(heap);
    return NULL;
  }
  return heap;
}

heap_t *heap_crear(cmp_func_t cmp){
  heap_t* heap = creador(TAM_INI);
  if(!heap) return NULL;
  heap->largo = TAM_INI;
  heap->tam = 0 ;
  heap->cmp = cmp;
  return heap;
}

void copiar_array(void* arreglo1[], void* arreglo2[],  size_t n){
  for(size_t i = 0; i < n; i++){
    arreglo1[i] = arreglo2[i];
  }
}

void heapify(heap_t* heap);

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
  heap_t* heap = creador(n);
  heap->largo = n;
  heap->tam = 0;
  heap->cmp = cmp;
  //copiar_array(heap->datos, arreglo, n);
  for (size_t i = 0; i < n; i++){
    
    heapify(heap); 
  }
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
  heap_t* = heap_crear_arr(elementos, cant, cmp);
  for(size_t i = 0; i < cant; i++){
    elementos[cant-i-1] = heap_desencolar(heap);   
  }
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
  while(!heap_esta_vacio(heap)){
    if (destruir_elemento) {
      destruir_elemento(heap_desencolar(heap));
    }
    else heap_desencolar(heap);
  }
  free(heap->datos);
  free(heap);
}


size_t heap_cantidad(const heap_t *heap){
  return heap->tam;
}


bool heap_esta_vacio(const heap_t *heap){
  return heap->tam == 0 ? true : false;
}


void swap (void** array, size_t nodo, size_t padre) {
  void* aux = array[nodo];
  array[nodo] = array[padre];
  array[padre] = aux;
}


void upheap(void** a, size_t nodo, cmp_func_t cmp){
  size_t padre, actual = nodo;
  if (nodo != 0)  padre = (actual - 1)/2;
  else padre = 0 ;
  while( actual != 0 && cmp(a[actual], a[padre]) > 0 ){ // nodo < padre 
    swap(a, actual, padre);
    actual = padre;    
    padre = (actual - 1)/2;
  }
}

bool heap_encolar(heap_t *heap, void *elem){
  //if(heap->tam > heap->largo + 1) redimensionar(heap);
  heap->datos[heap->tam] = elem ;
  upheap(heap->datos, heap->tam, heap->cmp);
  heap->tam++;
  return true;
}


void *heap_ver_max(const heap_t *heap){
  return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}

void down_heap(heap_t* heap, size_t tam, size_t actual ) {//game estato
  void** array = heap->datos;
  size_t hijo_derecho = (2 * actual) + 2  , hijo_izquierdo = (2 * actual) +1, pos_max ;
  if(hijo_derecho < tam){
    if(heap->cmp(array[hijo_izquierdo], array[hijo_derecho]) < 0){
      pos_max = hijo_derecho;
    }
    else pos_max = hijo_izquierdo;
    
    if (heap->cmp(array[actual], array[pos_max]) < 0){
      swap(array, actual, pos_max);
    } 
    down_heap(heap, tam-1, pos_max);
  }
  
  
}

void *heap_desencolar(heap_t *heap){
  if(heap_esta_vacio(heap)) return NULL;
  void* dato_salida = heap->datos[0];
  heap->datos[0] = heap->datos[heap->tam-1];
  down_heap(heap, heap->tam, 0);
  heap->tam--;
  /*  for(size_t a = 0; a < heap->tam; a++){
    printf("heap->datos[%zu] es : %zu\n\n", a, *(size_t*)heap->datos[a]);
    }*/
  return dato_salida;
}
