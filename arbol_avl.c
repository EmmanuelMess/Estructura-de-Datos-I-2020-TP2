#include <malloc.h>
#include "arbol_avl.h"
#include "deque.h"

struct ArbolAvl *itree_crear() {
  struct ArbolAvl* avl = calloc(1, sizeof(struct ArbolAvl));

  return avl;
}

void itree_destruir(struct ArbolAvl *tree) {
  free(tree);
}

void itree_eliminar(struct ArbolAvl *tree, struct Rango rango) {

}

void itree_insertar(struct ArbolAvl *tree, struct Rango rango) {

}

bool itree_intersectar(struct ArbolAvl *tree, struct Rango rango) {
 return true;
}

void itree_imprimir_arbol(struct ArbolAvl *arbol) {
  unsigned int assumedPos = 1;
  unsigned int nodosEnDeque = 0;

  struct ArbolAvlNodeDeque* deque = deque_crear();

  deque_push_front(deque, arbol->arbolAvlNode);
  nodosEnDeque++;

  int i = 0;
  for (; nodosEnDeque > 0; i++) {
    struct ArbolAvlNode* nodo = deque_pop_back(deque);

    if(!nodo) {
      printf(" NULL");
      deque_push_front(deque, NULL);
      deque_push_front(deque, NULL);
    } else {
      printf(
        " {m: %lf, r: [%lf, %lf], f: %d}",
        nodo->maxB,
        nodo->rango.a,
        nodo->rango.b,
        nodo->factorDeEquilibrio
        );
      nodosEnDeque--;

      deque_push_front(deque, nodo->izquierda);
      nodosEnDeque += (nodo->izquierda != NULL ? 1 : 0);
      deque_push_front(deque, nodo->derecha);
      nodosEnDeque += (nodo->derecha != NULL ? 1 : 0);
    }

    if(assumedPos == i+1 && nodosEnDeque > 0) {
      printf("\n");
      assumedPos <<= 1;
      assumedPos += 1;
    }
  }

  for(;i+1 <= assumedPos; i++) {
    printf(" NULL");
  }

  printf("\n");
}

typedef struct ArbolAvlNode* (Popper(struct ArbolAvlNodeDeque*)) ;

void itree_recorrer_fs(
  struct ArbolAvl *arbol,
  Impresion impresion,
  Popper pop
) {
  struct ArbolAvlNodeDeque* deque = deque_crear();

  deque_push_front(deque, arbol->arbolAvlNode);

  while (!deque_vacio(deque)) {
    struct ArbolAvlNode* nodo = pop(deque);

    impresion(nodo->rango);

    if(nodo->izquierda) {
      deque_push_front(deque, nodo->izquierda);
    }
    if(nodo->derecha) {
      deque_push_front(deque, nodo->derecha);
    }
  }

  deque_destruir(deque);
}

void itree_recorrer_dfs(struct ArbolAvl *arbol, Impresion impresion) {
  itree_recorrer_fs(arbol, impresion, deque_pop_front);
}

void itree_recorrer_bfs(struct ArbolAvl *arbol, Impresion impresion) {
  itree_recorrer_fs(arbol, impresion, deque_pop_back);
}