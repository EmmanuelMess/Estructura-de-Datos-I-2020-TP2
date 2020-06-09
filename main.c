#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tests.h"
#include "main.h"
#define DEBUG true

const char PARSE_ERROR[] = "Error: Formato invalido\n";
const char ERROR_RANGO[] = "Error: Rango invalido\n";
const char ERROR_INSERCION[] = "Error: Insercion invalida\n";
const char ERROR_ELIMINACION[] = "Error: Eliminacion invalida\n";

void impresion(struct ArbolAvlNode* nodo) {
  printf(" [%lf, %lf]", nodo->rango.a, nodo->rango.b);
}

bool escanearRango(struct Rango* rango, char* entrada) {
  char aRaw[512] = {0}, bRaw[512] = {0};

  if(*entrada == '[') {
    entrada++;
  } else {
    return true;
  }

  for (int i = 0; *entrada != ','; entrada++) {
    aRaw[i++] = *entrada;
  }

  if(*entrada == ',') {
    entrada++;
  } else {
    return true;
  }

  for (int i = 0; *entrada != ']'; entrada++) {
    bRaw[i++] = *entrada;
  }

  rango->a = strtod(aRaw, NULL);
  rango->b = strtod(bRaw, NULL);

  return false;
}

bool procesar(char *entrada, struct ArbolAvl *arbol) {
  char c;
  if(sscanf(entrada, "%c", &c) == 1) {
    entrada++;
  } else {
    printf(PARSE_ERROR);
    exit(1);
  }

  switch (c) {
    case 'i': {
      if(*entrada == ' ') {
        entrada++;
      } else {
        printf(PARSE_ERROR);
        return false;
      }

      struct Rango rango = {0};
      if(escanearRango(&rango, entrada)) {
        printf(PARSE_ERROR);
        return false;
      }

      if(rango.b < rango.a) {
        printf(ERROR_RANGO);
        return false;
      }

      bool fallo = !itree_insertar(arbol, rango);

      if(fallo) {
        printf(ERROR_INSERCION);
        return false;
      }
    }
      break;
    case 'e':{
      if(*entrada == ' ') {
        entrada++;
      } else {
        printf(PARSE_ERROR);
        return false;
      }

      struct Rango rango = {0};
      if(escanearRango(&rango, entrada)) {
        printf(PARSE_ERROR);
        return false;
      }

      bool fallo = !itree_eliminar(arbol, rango);
      if(fallo) {
        printf(ERROR_ELIMINACION);
      }
    }
      break;
    case '?':{
      if(*entrada == ' ') {
        entrada++;
      } else {
        printf(PARSE_ERROR);
        return false;
      }

      struct Rango rango = {0};
      if(escanearRango(&rango, entrada)) {
        printf(PARSE_ERROR);
        return false;
      }

      struct Rango intersecta = itree_intersectar(arbol, rango);
      if(intersecta.a != intersecta.a) {
        printf("No\n");
      } else {
        printf("Si [%lf, %lf]\n", intersecta.a, intersecta.b);
      }
    }
      break;
    case 'b':
      if (*entrada != 'f' || *(entrada + 1) != 's') {
        printf(PARSE_ERROR);
        return false;
      }

      itree_recorrer_bfs(arbol, impresion);

      printf("\n");
      break;
    case 'd':
      if (*entrada != 'f' || *(entrada + 1) != 's') {
        printf(PARSE_ERROR);
        return false;
      }

      itree_recorrer_dfs(arbol, impresion);

      printf("\n");
      break;
    case 's':
      return true;
    default:
      printf(PARSE_ERROR);
      return false;
  }
  return false;
}

int main(int argc, char *argv[]) {
#if DEBUG
  if(argc == 2) {
    main_tests();

    return 0;
  }
#endif

  struct ArbolAvl* arbol = itree_crear();
  bool sigue = true;

  while (sigue) {
    printf("> ");
    char *entrada = malloc(1024 * sizeof(char));
    entrada = fgets(entrada, 1024, stdin);
    if (entrada != NULL) {
      sigue = !procesar(entrada, arbol);

#if DEBUG
      itree_imprimir_arbol(arbol);
#endif

      free(entrada);
    }
  }

  itree_destruir(arbol);
}
