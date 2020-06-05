#ifndef ESTRUCTURA_DE_DATOS_I_2020_TP2_DEQUE_H
#define ESTRUCTURA_DE_DATOS_I_2020_TP2_DEQUE_H

#include <malloc.h>
#include "arbol_avl.h"

//INICIO <-> <-> <-> FINAL
struct ArbolAvlNodeDequeNode {
  struct ArbolAvlNode* arbolAvl;
  struct ArbolAvlNodeDequeNode* siguente;
  struct ArbolAvlNodeDequeNode* anterior;
};

struct ArbolAvlNodeDeque {
  struct ArbolAvlNodeDequeNode* primerNodo;
  struct ArbolAvlNodeDequeNode* ultimoNodo;
};

struct ArbolAvlNodeDeque* deque_crear();

void deque_destruir(struct ArbolAvlNodeDeque* deque);

bool deque_vacio(struct ArbolAvlNodeDeque *deque);

void deque_push_front(struct ArbolAvlNodeDeque* deque, struct ArbolAvlNode* arbolAvl);

struct ArbolAvlNode* deque_pop_front(struct ArbolAvlNodeDeque* deque);

struct ArbolAvlNode* deque_pop_back(struct ArbolAvlNodeDeque* deque);

#endif //ESTRUCTURA_DE_DATOS_I_2020_TP2_DEQUE_H
