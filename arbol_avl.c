#include <malloc.h>
#include <stdlib.h>
#include "arbol_avl.h"
#include "deque.h"

typedef struct ArbolAvlNode* (Popper(struct Deque*)) ;

int max(int a, int b) {
  return a > b? a:b;
}

void itree_recorrer_fs(
  struct ArbolAvl *arbol,
  Accion actuar,
  Popper pop
) {
  struct Deque* deque = deque_crear();

  deque_push_front(deque, arbol->arbolAvlNode);

  while (!deque_vacio(deque)) {
    struct ArbolAvlNode* nodo = pop(deque);

    if(nodo->izquierda) {
      deque_push_front(deque, nodo->izquierda);
    }
    if(nodo->derecha) {
      deque_push_front(deque, nodo->derecha);
    }

    actuar(nodo);
  }

  deque_destruir(deque);
}

struct ArbolAvl *itree_crear() {
  struct ArbolAvl* avl = calloc(1, sizeof(struct ArbolAvl));

  return avl;
}

void itree_destruir(struct ArbolAvl *tree) {
  itree_recorrer_fs(tree, free, deque_pop_back);
  free(tree);
}

bool itree_eliminar(struct ArbolAvl *tree, struct Rango rango) {

}

int IZQUIERDA = 0;
int DERECHA = 1;

void actualizar_max_nodo(struct ArbolAvlNode* nodo) {
  if(nodo->izquierda == NULL && nodo->derecha == NULL) {
    nodo->maxB = nodo->rango.b;
  } else if(nodo->izquierda == NULL) {
    nodo->maxB = nodo->derecha->maxB;
  } else if (nodo->derecha == NULL) {
    nodo->maxB = nodo->izquierda->maxB;
  } else {
    nodo->maxB = nodo->izquierda->maxB > nodo->derecha->maxB ?
                 nodo->izquierda->maxB : nodo->derecha->maxB;
  }
}

void rotacion_simple_izquierda(
  struct ArbolAvlNode** posicionDelNodo,
  struct ArbolAvlNode* nodo
) {
  struct ArbolAvlNode* nuevoHijo = nodo->izquierda;
  struct ArbolAvlNode* nuevoNietoDerecha = nodo;
  struct ArbolAvlNode* nuevoIzquierdaNietoDerecha = nodo->izquierda->derecha;

  *posicionDelNodo = nuevoHijo;
  nuevoHijo->derecha = nuevoNietoDerecha;
  nuevoNietoDerecha->izquierda = nuevoIzquierdaNietoDerecha;

  nuevoNietoDerecha->alto -= 2;

  actualizar_max_nodo(nuevoNietoDerecha);
  actualizar_max_nodo(nuevoHijo);
}

void rotacion_simple_derecha(
  struct ArbolAvlNode** posicionDelNodo,
  struct ArbolAvlNode* nodo
) {
  struct ArbolAvlNode* nuevoHijo = nodo->derecha;
  struct ArbolAvlNode* nuevoNietoIzquierda = nodo;
  struct ArbolAvlNode* nuevaDerechaNietoIzquierda = nodo->derecha->izquierda;

  *posicionDelNodo = nuevoHijo;
  nuevoHijo->izquierda = nuevoNietoIzquierda;
  nuevoNietoIzquierda->derecha = nuevaDerechaNietoIzquierda;

  nuevoNietoIzquierda->alto -= 2;

  actualizar_max_nodo(nuevoNietoIzquierda);
  actualizar_max_nodo(nuevoHijo);
}

bool itree_insertar(struct ArbolAvl *arbol, struct Rango rango) {
  struct ArbolAvlNode* nodo = calloc(1, sizeof(struct ArbolAvlNode));
  nodo->rango = rango;
  nodo->maxB = rango.b;
  nodo->alto = 1;

  struct Deque* dequeCamino = deque_crear();
  struct Deque* dequeDireccion = deque_crear();

  {
    struct ArbolAvlNode **pos = &(arbol->arbolAvlNode);
    while (*pos != NULL) {
      struct ArbolAvlNode *chequear = *pos;

      if (rango.a < chequear->rango.a
          || (chequear->rango.a == rango.a && rango.b < chequear->rango.b)) {
        pos = &((*pos)->izquierda);
        deque_push_front(dequeDireccion, &IZQUIERDA);
      } else if (chequear->rango.a < rango.a
                 || (chequear->rango.a == rango.a &&
                     chequear->rango.b < rango.b)) {
        pos = &((*pos)->derecha);
        deque_push_front(dequeDireccion, &DERECHA);
      } else {
        return false;
      }

      deque_push_front(dequeCamino, chequear);
    }

    *pos = nodo;
  }

  while (!deque_vacio(dequeCamino)) {
    struct ArbolAvlNode* chequear = deque_pop_front(dequeCamino);
    int pos = *((int*) deque_pop_front(dequeDireccion));

    actualizar_max_nodo(chequear);

    if(chequear->izquierda && chequear->derecha) {
      chequear->alto = max(chequear->izquierda->alto, chequear->derecha->alto) + 1;
    } else if(chequear->izquierda) {
      chequear->alto = chequear->izquierda->alto + 1;
    } else if(chequear->derecha) {
      chequear->alto = chequear->derecha->alto + 1;
    } else {
      chequear->alto = 1;
    }

    if(-1 <= itree_factor_de_equilibrio(chequear)
        && itree_factor_de_equilibrio(chequear) <= 1) {
      continue;
    }

    struct ArbolAvlNode **posicionDelNodo;

    if (!deque_vacio(dequeDireccion)) {
      struct ArbolAvlNode *padre = deque_pop_front(dequeCamino);
      deque_push_front(dequeCamino, padre);

      if (pos == IZQUIERDA) {
        posicionDelNodo = &(padre->izquierda);
      } else {
        posicionDelNodo = &(padre->derecha);
      }
    } else {
      posicionDelNodo = &(arbol->arbolAvlNode);
    }

    if (itree_factor_de_equilibrio(chequear->izquierda) < 0) {
      rotacion_simple_izquierda(posicionDelNodo, chequear);
      break;
    } else if (itree_factor_de_equilibrio(chequear->derecha) > 0) {
      rotacion_simple_derecha(posicionDelNodo, chequear);
      break;
    } else if(itree_factor_de_equilibrio(chequear->izquierda) > 0) {
      rotacion_simple_derecha(&(chequear->izquierda), chequear->izquierda);
      rotacion_simple_izquierda(posicionDelNodo, chequear);
      break;
    } else if(itree_factor_de_equilibrio(chequear->derecha) < 0) {
      rotacion_simple_izquierda(&(chequear->derecha), chequear->derecha);
      rotacion_simple_derecha(posicionDelNodo, chequear);
      break;
    }
  }

  while (!deque_vacio(dequeCamino)) {
    struct ArbolAvlNode *chequear = deque_pop_front(dequeCamino);
    actualizar_max_nodo(chequear);
  }

  deque_destruir(dequeCamino);
  deque_destruir(dequeDireccion);

  return true;
}

bool itree_intersectar(struct ArbolAvl *tree, struct Rango rango) {
 return true;
}

void itree_imprimir_arbol(struct ArbolAvl *arbol) {
  unsigned int assumedPos = 1;
  unsigned int nodosEnDeque = 0;

  struct Deque* deque = deque_crear();

  deque_push_front(deque, arbol->arbolAvlNode);
  nodosEnDeque++;

  int i = 0;
  for (; nodosEnDeque > 0; i++) {
    struct ArbolAvlNode* nodo = deque_pop_back(deque);

    if(!nodo) {
      printf(" {    NULL    }");
      deque_push_front(deque, NULL);
      deque_push_front(deque, NULL);
    } else {
      printf(
        " {m: %.1lf, r: [%.2lf, %.2lf], a: %d}",
        nodo->maxB,
        nodo->rango.a,
        nodo->rango.b,
        nodo->alto
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
    printf(" {    NULL    }");
  }

  printf("\n");
}

void itree_recorrer_fs_imprimir(
  struct ArbolAvl *arbol,
  Impresion impresion,
  Popper pop
) {
  itree_recorrer_fs(arbol, impresion, pop);
}

void itree_recorrer_dfs(struct ArbolAvl *arbol, Impresion impresion) {
  itree_recorrer_fs_imprimir(arbol, impresion, deque_pop_front);
}

void itree_recorrer_bfs(struct ArbolAvl *arbol, Impresion impresion) {
  itree_recorrer_fs_imprimir(arbol, impresion, deque_pop_back);
}

int itree_factor_de_equilibrio(struct ArbolAvlNode *nodo) {
  if(nodo->derecha && nodo->izquierda) {
    return nodo->derecha->alto - nodo->izquierda->alto;
  } else if(nodo->derecha) {
    return nodo->derecha->alto;
  } else if(nodo->izquierda) {
    return -nodo->izquierda->alto;
  } else {
    return 0;
  }
}