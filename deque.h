#ifndef ESTRUCTURA_DE_DATOS_I_2020_TP2_DEQUE_H
#define ESTRUCTURA_DE_DATOS_I_2020_TP2_DEQUE_H

#include <malloc.h>
#include "arbol_avl.h"

//INICIO <-> <-> <-> FINAL
struct DequeNode {
  void* arbolAvl;
  struct DequeNode* siguente;
  struct DequeNode* anterior;
};

struct Deque {
  struct DequeNode* primerNodo;
  struct DequeNode* ultimoNodo;
};

struct Deque* deque_crear();

void deque_destruir(struct Deque* deque);

bool deque_vacio(struct Deque *deque);

void deque_push_front(struct Deque* deque, void *elemento);

void * deque_pop_front(struct Deque* deque);

void * deque_pop_back(struct Deque* deque);

#endif //ESTRUCTURA_DE_DATOS_I_2020_TP2_DEQUE_H
