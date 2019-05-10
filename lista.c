#include <string.h>
#include "lista.h"

list NEW() {
    list x = (list) malloc(sizeof(struct struct_list));
    x->head = NULL;
    x->tail = NULL;
    return x;
}

list insertEnd(list l, Contacto c) {
    list_link new_last = (list_link) malloc(sizeof(struct list_node));
    new_last->contacto = c;
    if (l->tail == NULL) l->head = new_last;
    else l->tail->next = new_last;
    new_last->prev = l->tail;
    new_last->next = NULL;
    l->tail = new_last;
    return l;
}


void print(list_link head) {
    list_link t;
    for (t = head; t != NULL; t = t->next) {
        printContacto(t->contacto);
    }
}

list_link lookup(list_link head, char* text) {
    list_link t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->contacto->nome, text) == 0) return t;
    return NULL;
}

list delete(list l, char* text) {
    list_link t;
    for (t = l->head; t != NULL; t = t->next) {
        if (strcmp(t->contacto->nome, text) == 0) {
            if (t == l->head) l->head = l->head->next;
            if (t == l->tail) l->tail = l->tail->prev;
            if (t->next != NULL) t->next->prev = t->prev;
            if (t->prev != NULL) t->prev->next = t->next;

            free(t);
            return l;
        }
    }
    return l;
}