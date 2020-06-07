#ifndef ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H
#define ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H

#include <stdbool.h>

struct Rango {
  double a, b;
};

struct ArbolAvlNode {
  struct Rango rango;
  double maxB;
  short factorDeEquilibrio;

  struct ArbolAvlNode* derecha;
  struct ArbolAvlNode* izquierda;
};

struct ArbolAvl {
  struct ArbolAvlNode* arbolAvlNode;
};

typedef void Accion(struct ArbolAvlNode*);

typedef void Impresion(struct ArbolAvlNode*);

struct ArbolAvl* itree_crear();

void itree_destruir(struct ArbolAvl* tree);

bool itree_insertar(struct ArbolAvl *arbol, struct Rango rango);

void itree_eliminar(struct ArbolAvl* tree, struct Rango rango);

bool itree_intersectar(struct ArbolAvl* tree, struct Rango rango);

void itree_recorrer_dfs(struct ArbolAvl *arbol, Impresion impresion);

void itree_recorrer_bfs(struct ArbolAvl *arbol, Impresion impresion);

void itree_imprimir_arbol(struct ArbolAvl *arbol);

#endif //ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H
