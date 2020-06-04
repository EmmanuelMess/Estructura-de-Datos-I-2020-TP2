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
  int factor_balance;
};

typedef void Impresion(struct Rango);

struct ArbolAvl* itree_crear(struct Rango rango);

void itree_destruir(struct ArbolAvl* tree);

struct ArbolAvl*  itree_insertar(struct ArbolAvl *tree, struct Rango rango);

struct ArbolAvl*  itree_eliminar(struct ArbolAvl* tree, struct Rango rango);

bool itree_intersectar(struct ArbolAvl* tree, struct Rango rango);

void itree_recorrer_dfs(struct ArbolAvl *arbol, Impresion impresion);

void itree_recorrer_bfs(struct ArbolAvl *arbol, Impresion impresion);

struct ArbolAvl * minValueNode(struct ArbolAvl* node);

void inOrder(struct ArbolAvl *root);

void recalcularMax(struct ArbolAvl* node);

int getBalance(struct ArbolAvl *N);

struct ArbolAvl *rotacion_izquierda(struct ArbolAvl *x);

struct ArbolAvl* rotacion_derecha(struct ArbolAvl* y);

int max(int a, int b);

int balance (struct ArbolAvl* N);

#endif //ESTRUCTURA_DE_DATOS_I_2020_TP2_ARBOL_AVL_H

