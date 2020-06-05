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
}

void itree_recorrer_dfs(struct ArbolAvl *arbol, Impresion impresion) {
  itree_recorrer_fs(arbol, impresion, deque_pop_front);
}

void itree_recorrer_bfs(struct ArbolAvl *arbol, Impresion impresion) {
  itree_recorrer_fs(arbol, impresion, deque_pop_back);
}