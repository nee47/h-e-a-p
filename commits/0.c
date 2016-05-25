#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include <stdio.h>
#define TAM_INI 190

struct heap{
  void** datos;
  size_t tam;
  size_t largo;
  cmp_func_t cmp;
};

heap_t *heap_crear(cmp_func_t cmp){
  heap_t* heap = malloc(sizeof(heap_t));
  if(!heap) return NULL;
  heap->datos = malloc(sizeof(void*) * TAM_INI);
  if(!heap->datos){
    free(heap);
    return NULL;
  }
  heap->largo = TAM_INI;
  heap->tam = 0 ;
  heap->cmp = cmp;
  return heap;
}


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);

void heap_destruir(heap_t *heap, void destruir_elemento(void *e));


size_t heap_cantidad(const heap_t *heap){
  return heap->tam;
}


bool heap_esta_vacio(const heap_t *heap){
  return heap->tam == 0 ? true : false;
}


void swap (void** x, void** y) {
  void* temp = *x;
  *x = *y;
  *y = temp;
}


void upheap(void** a, size_t nodo, cmp_func_t cmp){
  size_t padre;
  if (nodo != 0)  padre = (nodo - 1)/2;
  else padre = 0 ;
  //while(padre > 0)
  if(cmp(a[nodo], a[padre]) > 0){ // nodo < padre 
    //swap(a[nodo], a[padre]);   
    void* aux = a[nodo];
    a[nodo] = a[padre];
    a[padre] = aux;
    upheap(a, padre, cmp);
  }
}
//      printf(" HICE SWAP nodo es : %zu padre es :%zu \n\n", *(size_t*)heap->datos[nodo], *(size_t*)heap->datos[padre]);

bool heap_encolar(heap_t *heap, void *elem){
  //if(heap->tam > heap->largo + 1) redimensionar(heap);
  heap->datos[heap->tam] = elem ;
  upheap(heap->datos, heap->tam, heap->cmp);
  heap->tam++;
  for(size_t a = 0; a < heap->tam; a++){
    printf("heap->datos[%zu] es : %zu\n\n", a, *(size_t*)heap->datos[a]);
  }
  return true;
}


void *heap_ver_max(const heap_t *heap){
  return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
  if(heap_esta_vacio(heap)) return NULL;
  
  void* dato_salida = heap->datos[0];
  return dato_salida;
}
