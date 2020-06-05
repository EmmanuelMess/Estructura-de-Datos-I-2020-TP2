#ifndef ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H
#define ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H

#include <stdbool.h>

struct Rango {
  double a, b;
};

struct ArbolAvl {
  struct Rango rango;
  double maxB;

  struct ArbolAvl* derecha;
  struct ArbolAvl* izquierda;
};

typedef void Impresion(struct Rango);

struct ArbolAvl* itree_crear();

void itree_destruir(struct ArbolAvl* tree);

void itree_insertar(struct ArbolAvl *tree, struct Rango rango);

void itree_eliminar(struct ArbolAvl* tree, struct Rango rango);

bool itree_intersectar(struct ArbolAvl* tree, struct Rango rango);

void itree_recorrer_dfs(struct ArbolAvl *arbol, Impresion impresion);

void itree_recorrer_bfs(struct ArbolAvl *arbol, Impresion impresion);

#endif //ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H
