#include "deque.h"

struct Deque *deque_crear() {
  return calloc(1, sizeof(struct Deque));
}

void deque_destruir(struct Deque *deque) {
  while (deque->primerNodo != NULL) {
    struct DequeNode* siguente = deque->primerNodo->siguente;
    free(deque->primerNodo);
    deque->primerNodo = siguente;
  }

  free(deque);
}

bool deque_vacio(struct Deque *deque) {
  return deque->ultimoNodo == NULL;
}

void * deque_pop_back(struct Deque *deque) {
  struct DequeNode* tmp = deque->ultimoNodo;

  struct ArbolAvlNode* elemento = deque->ultimoNodo->arbolAvl;
  deque->ultimoNodo = deque->ultimoNodo->anterior;

  if(deque->ultimoNodo != NULL) {
    deque->ultimoNodo->siguente = NULL;
  } else {
    deque->primerNodo = NULL;
  }

  free(tmp);
  return elemento;
}

void * deque_pop_front(struct Deque *deque) {
  struct DequeNode* tmp = deque->primerNodo;

  struct ArbolAvlNode* elemento = deque->primerNodo->arbolAvl;
  deque->primerNodo = deque->primerNodo->siguente;

  if(deque->primerNodo != NULL) {
    deque->primerNodo->anterior = NULL;
  } else {
    deque->ultimoNodo = NULL;
  }

  free(tmp);
  return elemento;
}

void * deque_peek_front(struct Deque *deque) {
  return deque->primerNodo->arbolAvl;
}

void deque_push_front(struct Deque *deque, void *elemento) {
  struct DequeNode* node = calloc(1, sizeof(struct DequeNode));
  node->arbolAvl = elemento;
  node->siguente = deque->primerNodo;
  node->anterior = NULL;

  if(deque->primerNodo == NULL) {
    deque->primerNodo = node;
    deque->ultimoNodo = node;
  } else {
    deque->primerNodo->anterior = node;

    deque->primerNodo = node;
  }
}