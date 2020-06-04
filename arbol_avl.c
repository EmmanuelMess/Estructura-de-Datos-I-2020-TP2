#include <malloc.h>
#include <stdio.h>
#include "arbol_avl.h"
#include "deque.h"

struct ArbolAvl *itree_crear(struct Rango rango) {
  struct ArbolAvl* avl = malloc(sizeof(struct ArbolAvl));

    avl->rango   = rango;
    avl->maxB = rango.b;
    avl->izquierda  = NULL;
    avl->derecha  = NULL;
    avl->factor_balance = 1;
  return avl;
}

void itree_destruir(struct ArbolAvl *tree) {
  free(tree);
}

int balance (struct ArbolAvl* N)
{
    if (N == NULL)
        return 0;
    return N->factor_balance;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}

struct ArbolAvl* rotacion_derecha(struct ArbolAvl* y)
{
    struct ArbolAvl* x = y->izquierda;
    struct ArbolAvl* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->factor_balance = max(balance(y->izquierda), balance(y->derecha))+1;
    x->factor_balance = max(balance(x->izquierda), balance(x->derecha))+1;

    return x;
}

struct ArbolAvl *rotacion_izquierda(struct ArbolAvl *x)
{
    struct ArbolAvl *y = x->derecha;
    struct ArbolAvl *T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->factor_balance = max(balance(x->izquierda), balance(x->derecha))+1;
    y->factor_balance = max(balance(y->izquierda), balance(y->derecha))+1;

    return y;
}

int getBalance(struct ArbolAvl *N)
{
    if (N == NULL)
        return 0;
    return balance(N->izquierda) - balance(N->derecha);
}

struct ArbolAvl* itree_eliminar(struct ArbolAvl *root, struct Rango rango) {
//struct Node* deleteNode(struct Node* root, int key)

    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( rango.a < root->rango.a )
        root->izquierda = itree_eliminar(root->izquierda, rango);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( rango.a  > root->rango.a )
        root->derecha = itree_eliminar(root->derecha, rango);

    // if key is same as root's key, then This is
    // the node to be deleted
    else if(root->rango.b==rango.b)
    {
        // node with only one child or no child
        if( (root->izquierda == NULL) || (root->derecha == NULL) )
        {
            struct ArbolAvl *temp = root->izquierda ? root->izquierda :
                                             root->derecha;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct ArbolAvl* temp = minValueNode(root->derecha);

            // Copy the inorder successor's data to this node
            root->rango = temp->rango;

            // Delete the inorder successor
            root->derecha = itree_eliminar(root->derecha, temp->rango);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->factor_balance = 1 + max(balance(root->izquierda),
                           balance(root->derecha));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->izquierda) >= 0)
        return rotacion_derecha(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->izquierda) < 0)
    {
        root->izquierda =  rotacion_izquierda(root->izquierda);
        return rotacion_derecha(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->derecha) <= 0)
        return rotacion_izquierda(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->derecha) > 0)
    {
        root->derecha = rotacion_derecha(root->derecha);
        return rotacion_izquierda(root);
    }

    recalcularMax(root);
    return root;

}

void recalcularMax(struct ArbolAvl* node){ //no anda bien esta funcion para recalcular el max
double max;
if(node==NULL)return;
if(node->izquierda==node->derecha && node->izquierda==NULL){
    node->maxB = node->rango.b;
    return;
}else if(node->izquierda==NULL){
max=node->derecha->maxB;
}else if(node->derecha==NULL){
max=node->izquierda->maxB;
}else{
  max=(node->izquierda->maxB > node->derecha->maxB)? node->izquierda->maxB:node->derecha->maxB;
}
node->maxB= (node->maxB >max)? node->maxB:max;
}

struct ArbolAvl * minValueNode(struct ArbolAvl* node)
{
    struct ArbolAvl* current = node;

    /* loop down to find the leftmost leaf */
    while (current->izquierda != NULL)
        current = current->izquierda;

    return current;
}

struct ArbolAvl* itree_insertar(struct ArbolAvl *node, struct Rango rango) {

/* 1.  Perform the normal BST insertion */
    if (node == NULL){

        return(itree_crear(rango));
    }
    double l = node->rango.a;

    if (rango.a < l)
        node->izquierda  = itree_insertar(node->izquierda, rango);
    else if (rango.a > l){


        node->derecha = itree_insertar(node->derecha, rango);

    }
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->factor_balance = 1 + max(balance(node->izquierda),
                           balance(node->derecha));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && rango.a < node->izquierda->rango.a)
        return rotacion_derecha(node);

    // Right Right Case
    if (balance < -1 && rango.a > node->derecha->rango.a)
        return rotacion_izquierda(node);

    // Left Right Case
    if (balance > 1 && rango.a > node->izquierda->rango.a)
    {
        node->izquierda =  rotacion_izquierda(node->izquierda);
        return rotacion_derecha(node);
    }

    // Right Left Case
    if (balance < -1 && rango.a < node->derecha->rango.a)
    {
        node->derecha = rotacion_derecha(node->derecha);
        return rotacion_izquierda(node);
    }

    /* return the (unchanged) node pointer */
        if (node->maxB < rango.b){
        node->maxB = rango.b;
        }

    return node;
}



bool itree_intersectar(struct ArbolAvl *tree, struct Rango rango) {
 return true;
}

typedef struct ArbolAvl* (Popper(struct ArbolAvlDeque*)) ;

void itree_recorrer_fs(
  struct ArbolAvl *arbol,
  Impresion impresion,
  Popper pop
) {
  struct ArbolAvlDeque* deque = deque_crear();

  deque_push_front(deque, arbol);

  while (!deque_vacio(deque)) {
    struct ArbolAvl* nodo = pop(deque);

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
void inOrder(struct ArbolAvl *root)
{
    if(root != NULL)
    {

        inOrder(root->izquierda);
        printf("[%f,%f Max: %f]", root->rango.a,root->rango.b,root->maxB);
        inOrder(root->derecha);
    }
}
