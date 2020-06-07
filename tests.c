#include <assert.h>
#include "tests.h"
#include "main.h"
#include "arbol_avl.h"
#include "deque.h"

void test_deque_pila() {
  struct ArbolAvlNodeDeque* deque = deque_crear();

  deque_push_front(deque, (struct ArbolAvlNode*) 1);
  deque_push_front(deque, (struct ArbolAvlNode*) 2);
  deque_push_front(deque, (struct ArbolAvlNode*) 3);
  deque_push_front(deque, (struct ArbolAvlNode*) 4);

  assert(deque_pop_front(deque) == (struct ArbolAvlNode*) 4);
  assert(deque_pop_front(deque) == (struct ArbolAvlNode*) 3);
  assert(deque_pop_front(deque) == (struct ArbolAvlNode*) 2);
  deque_push_front(deque, (struct ArbolAvlNode*) 4);
  assert(deque_pop_front(deque) == (struct ArbolAvlNode*) 4);
  assert(deque_pop_front(deque) == (struct ArbolAvlNode*) 1);

  assert(deque_vacio(deque));

  deque_destruir(deque);
}

void test_deque_cola() {
  struct ArbolAvlNodeDeque* deque = deque_crear();

  deque_push_front(deque, (struct ArbolAvlNode*) 1);
  deque_push_front(deque, (struct ArbolAvlNode*) 2);
  deque_push_front(deque, (struct ArbolAvlNode*) 3);
  deque_push_front(deque, (struct ArbolAvlNode*) 4);

  assert(deque_pop_back(deque) == (struct ArbolAvlNode*) 1);
  assert(deque_pop_back(deque) == (struct ArbolAvlNode*) 2);
  assert(deque_pop_back(deque) == (struct ArbolAvlNode*) 3);
  deque_push_front(deque, (struct ArbolAvlNode*) 1);
  assert(deque_pop_back(deque) == (struct ArbolAvlNode*) 4);
  assert(deque_pop_back(deque) == (struct ArbolAvlNode*) 1);

  assert(deque_vacio(deque));

  deque_destruir(deque);
}

void test_procesador() {
  FILE* file = fopen("tests/simple.txt", "r");
  char buffer[256];
  struct ArbolAvl* arbol = itree_crear();

  while(fgets(buffer, 256, file)) {
    procesar(buffer, arbol);
  }

  itree_destruir(arbol);
}

void main_tests() {
  test_deque_pila();
  test_deque_cola();
  test_procesador();
}
