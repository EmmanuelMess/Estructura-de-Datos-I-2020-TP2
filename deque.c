#include "deque.h"

struct ArbolAvlNodeDeque *deque_crear() {
  return calloc(1, sizeof(struct ArbolAvlNodeDeque));
}

void deque_destruir(struct ArbolAvlNodeDeque *deque) {
  while (deque->primerNodo != NULL) {
    struct ArbolAvlNodeDequeNode* siguente = deque->primerNodo->siguente;
    free(deque->primerNodo);
    deque->primerNodo = siguente;
  }

  free(deque);
}

bool deque_vacio(struct ArbolAvlNodeDeque *deque) {
  return deque->ultimoNodo == NULL;
}

struct ArbolAvlNode* deque_pop_back(struct ArbolAvlNodeDeque *deque) {
  struct ArbolAvlNodeDequeNode* tmp = deque->ultimoNodo;

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

struct ArbolAvlNode* deque_pop_front(struct ArbolAvlNodeDeque *deque) {
  struct ArbolAvlNodeDequeNode* tmp = deque->primerNodo;

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

void deque_push_front(struct ArbolAvlNodeDeque *deque, struct ArbolAvlNode* arbolAvl) {
  struct ArbolAvlNodeDequeNode* node = calloc(1, sizeof(struct ArbolAvlNodeDequeNode));
  node->arbolAvl = arbolAvl;
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