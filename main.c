#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arbol_avl.h"
#include "tests.h"

const char PARSE_ERROR[] = "Error: Formato invalido";

void impresion(struct Rango rango) {
  printf(" [%lf, %lf]", rango.a, rango.b);
}

struct Rango escanearRango(char* entrada) {
  char aRaw[512] = {0}, bRaw[512] = {0};

  if(*entrada == '[') {
    entrada++;
  } else {
    printf(PARSE_ERROR);
    exit(1);
  }

  for (int i = 0; *entrada != ','; entrada++) {
    aRaw[i++] = *entrada;
  }

  if(*entrada == ',') {
    entrada++;
  } else {
    printf(PARSE_ERROR);
    exit(1);
  }

  for (int i = 0; *entrada != ']'; entrada++) {
    bRaw[i++] = *entrada;
  }

  double a = strtod(aRaw, NULL);
  double b = strtod(bRaw, NULL);

  return (struct Rango) {.a =  a, .b =  b};
}

bool procesar(char* entrada, struct ArbolAvl* arbol) {
  char c;
  if(sscanf(entrada, "%c", &c) == 1) {
    entrada++;
  } else {
    printf(PARSE_ERROR);
    exit(1);
  }

  if(*entrada == ' ') {
    entrada++;
  } else {
    printf(PARSE_ERROR);
    exit(1);
  }

  switch (c) {
    case 'i': {
      struct Rango rango = escanearRango(entrada);
      arbol=itree_insertar(arbol, rango);
    }
      break;
    case 'e':{
      struct Rango rango = escanearRango(entrada);
      arbol=itree_eliminar(arbol, rango);
    }
      break;
    case '?':{
      struct Rango rango = escanearRango(entrada);
      bool intersecta = itree_intersectar(arbol, rango);
      printf(intersecta? "Si":"No");
    }
      break;
    case 'b':
      itree_recorrer_bfs(arbol, impresion);
      break;
    case 'd':
      inOrder(arbol);
      //itree_recorrer_dfs(arbol, impresion);
      break;
    case 's':
      return true;
    default:
      printf(PARSE_ERROR);
      exit(1);
  }
  return false;
}

int main(int argc, char *argv[]) {
  if(argc == 2) {
    main_tests();

   return 0;
  }

  struct Rango rango;
  rango.a = 10;
  rango.b =11;

  struct ArbolAvl* arbol = itree_crear(rango);
  bool sigue = true;
  //inOrder(arbol);
  //printf("%f",arbol->rango.a);
  struct Rango rango2;
  rango2.a=13;
  rango2.b=15;
  //arbol=itree_insertar(arbol,rango2);
  //nOrder(arbol);
  while (sigue) {
    char *entrada = malloc(1024 * sizeof(char));
    entrada = fgets(entrada, 1024, stdin);
    if (entrada != NULL) {
      sigue = !procesar(entrada, arbol);
      free(entrada);
    }
  }
}

