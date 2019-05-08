#include <string.h>
#include "lista.h"

list_link NEW(Contacto c) {
    list_link x = (list_link) malloc(sizeof(struct list_node));
    x->contacto = c;
    x->next = NULL;
    return x;
}

list_link insertEnd(list_link head, Contacto c) {
    list_link x;
    if (head == NULL) {
        return NEW(c);
    }
    for (x = head; x->next != NULL; x = x->next);
    x->next = NEW(c);
    return head;
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

list_link delete(list_link head, char* text) {
    list_link t, prev;
    for (t = head, prev = NULL; t != NULL;
    prev = t, t = t->next) {
        if(strcmp(t->contacto->nome, text) == 0) {
            if (t == head) head = t->next;
            else prev->next = t->next;

            free(t);
        }
    }
    return head;
}
