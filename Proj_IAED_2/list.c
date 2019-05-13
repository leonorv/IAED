/**** Operacoes para lista duplamente ligada ****/
#include <string.h>
#include "list.h"

list NEW() {
    list x = (list) malloc(sizeof(struct struct_list));
    x->head = NULL;
    x->tail = NULL;
    return x;
}

list insertEnd(list l, Contact c) {
    list_link new_last = (list_link) malloc(sizeof(struct list_node));
    new_last->contact = c;
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
        printContact(t->contact);
    }
}

list delete(list l, char* text) {
    list_link t;
    for (t = l->head; t != NULL; t = t->next) {
        if (strcmp(t->contact->name, text) == 0) {
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