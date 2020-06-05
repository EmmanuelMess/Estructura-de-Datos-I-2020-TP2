#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arbol_avl.h"
#include "tests.h"

const char PARSE_ERROR[] = "Error: Formato invalido\n";

void impresion(struct Rango rango) {
  printf(" [%lf, %lf]", rango.a, rango.b);
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

bool procesar(char* entrada, struct ArbolAvl* arbol) {
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

      itree_insertar(arbol, rango);
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

      itree_eliminar(arbol, rango);
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

      bool intersecta = itree_intersectar(arbol, rango);
      printf(intersecta? "Si":"No");
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
  if(argc == 2) {
    main_tests();

    return 0;
  }

  struct ArbolAvl* arbol = itree_crear();
  bool sigue = true;

  while (sigue) {
    printf("> ");
    char *entrada = malloc(1024 * sizeof(char));
    entrada = fgets(entrada, 1024, stdin);
    if (entrada != NULL) {
      sigue = !procesar(entrada, arbol);
      free(entrada);
    }
  }
}
