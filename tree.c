#include "tree.h"

link NEW_NODE_TREE(Contacto c, link l, link r) {
    link x = (link) malloc(sizeof(struct node));
    x->contacto = c;
    x->l = l;
    x->r = r;
    x->height = 1;
    return x;
}

int height(link h) {
    if (h == NULL) return 0;
    return h->height;
}

link rotL(link h) {
    int height_left, height_right;
    link x = h->r;
    h->r = x->l;
    x->l = h;
    height_left = height(h->l);
    height_right = height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = height(x->l);
    height_right = height(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

link rotR(link h) {
    int height_left, height_right;
    link x = h->l;
    h->l = x->r;
    x->r = h;
    height_left = height(h->l);
    height_right = height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = height(x->l);
    height_right = height(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

link rotLR(link h) { /*rotação dupla esquerda direita*/
    if (h == NULL) return h;
    h->l = rotL(h->l);
    return rotR(h);
}

link rotRL(link h) { /*rotação dupla direita esquerda*/
    if (h == NULL) return h;
    h->r = rotR(h->r);
    return rotL(h);
}

int Balance(link h) { /*Balance factor*/
    if (h == NULL) return 0;
    return height(h->l) - height(h->r);
}

link AVLbalance(link h) {
    int balanceFactor;
    if (h == NULL) return h;
    balanceFactor = Balance(h);
    if (balanceFactor > 1) {
        if (Balance(h->l) > 0) h = rotR(h);
        else h = rotLR(h);
    }
    else if (balanceFactor < -1) {
        if (Balance(h->r) < 0) h = rotL(h);
        else h = rotRL(h);
        }
    else {
        int height_left = height(h->l);
        int height_right = height(h->r);
        h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    }
    return h;
}

link insertR(link h, Contacto contacto) {
    if (h == NULL) return NEW_NODE_TREE(contacto, NULL, NULL);
    if (less(key(contacto), key(h->contacto))) h->l = insertR(h->l, contacto);
    else h->r = insertR(h->r, contacto);
    h = AVLbalance(h);
    return h;
}

link deleteR(link h, Key nome) {
    if (h == NULL) return h;
    else if (less(nome, key(h->contacto))) h->l = deleteR(h->l, nome);
    else if (less(key(h->contacto), nome)) h->r = deleteR(h->r, nome) ;
    else {
        if (h->l != NULL && h->r != NULL){
            link aux = max(h->l);
            {Contacto x; x = h->contacto; h->contacto = aux->contacto; aux->contacto = x;}
            h->l = deleteR(h->l, key(aux->contacto));
        }
        else {
            link aux = h;
            if (h->l == NULL && h->r == NULL) h = NULL;
            else if (h->l == NULL) h = h->r;
            else h = h->l;
            free(aux);
        }
    }
    h = AVLbalance(h);
    return h;
}

Contacto searchR(link h, Key v) {
    if (h == NULL) return NULL;
    if (equal(v, key(h->contacto))) return h->contacto;
    if (less(v, key(h->contacto))) return searchR(h->l, v);
    else return searchR(h->r, v);
}

Contacto STsearch(link head, Key v) {
    return searchR(head, v);
}

link max(link h) {
    if (h == NULL || h -> r == NULL) return h;
    else return max(h -> r);
}