#include "domain_list.h"

domain_link d_NEW_NODE_TREE(Dominio d, domain_link l, domain_link r) {
    domain_link x = (domain_link) malloc(sizeof(struct domain_node));
    x->dominio = d;
    x->l = l;
    x->r = r;
    x->height = 1;
    return x;
}

int d_height(domain_link h) {
    if (h == NULL) return 0;
    return h->height;
}

domain_link d_rotL(domain_link h) {
    int height_left, height_right;
    domain_link x = h->r;
    h->r = x->l;
    x->l = h;
    height_left = d_height(h->l);
    height_right = d_height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = d_height(x->l);
    height_right = d_height(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

domain_link d_rotR(domain_link h) {
    int height_left, height_right;
    domain_link x = h->l;
    h->l = x->r;
    x->r = h;
    height_left = d_height(h->l);
    height_right = d_height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = d_height(x->l);
    height_right = d_height(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

domain_link d_rotLR(domain_link h) { /*rotação dupla esquerda direita*/
    if (h == NULL) return h;
    h->l = d_rotL(h->l);
    return d_rotR(h);
}

domain_link d_rotRL(domain_link h) { /*rotação dupla direita esquerda*/
    if (h == NULL) return h;
    h->r = d_rotR(h->r);
    return d_rotL(h);
}

int d_Balance(domain_link h) { /*Balance factor*/
    if (h == NULL) return 0;
    return d_height(h->l) - d_height(h->r);
}

domain_link d_AVLbalance(domain_link h) {
    int balanceFactor;
    if (h == NULL) return h;
    balanceFactor = d_Balance(h);
    if (balanceFactor > 1) {
        if (d_Balance(h->l) > 0) h = d_rotR(h);
        else h = d_rotLR(h);
    }
    else if (balanceFactor < -1) {
        if (d_Balance(h->r) < 0) h = d_rotL(h);
        else h = d_rotRL(h);
        }
    else {
        int height_left = d_height(h->l);
        int height_right = d_height(h->r);
        h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    }
    return h;
}

domain_link d_insertR(domain_link h, Dominio d) {
    if (h == NULL) return d_NEW_NODE_TREE(d, NULL, NULL);
    if (d_less(d_key(d), d_key(h->dominio))) h->l = d_insertR(h->l, d);
    else h->r = d_insertR(h->r, d);
    h = d_AVLbalance(h);
    return h;
}

domain_link d_deleteR(domain_link h, d_Key nome) {
    if (h == NULL) return h;
    else if (d_less(nome, d_key(h->dominio))) h->l = d_deleteR(h->l, nome);
    else if (d_less(d_key(h->dominio), nome)) h->r = d_deleteR(h->r, nome) ;
    else {
        if (h->l != NULL && h->r != NULL){
            domain_link aux = d_max(h->l);
            {Dominio x; x = h->dominio; h->dominio = aux->dominio; aux->dominio = x;}
            h->l = d_deleteR(h->l, d_key(aux->dominio));
        }
        else {
            domain_link aux = h;
            if (h->l == NULL && h->r == NULL) h = NULL;
            else if (h->l == NULL) h = h->r;
            else h = h->l;
            apagaDominio(aux->dominio);
            free(aux);
        }
    }
    h = d_AVLbalance(h);
    return h;
}

Dominio d_searchR(domain_link h, char* v) {
    if (h == NULL) return NULL;
    if (d_equal(v, d_key(h->dominio))) return h->dominio;
    if (d_less(v, d_key(h->dominio))) return d_searchR(h->l, v);
    else return d_searchR(h->r, v);
}

Dominio d_STsearch(domain_link head, char* v) {
    return d_searchR(head, v);
}

domain_link d_max(domain_link h) {
    if (h == NULL || h -> r == NULL) return h;
    else return d_max(h -> r);
}
