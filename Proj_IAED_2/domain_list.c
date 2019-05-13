#include <string.h>
#include "domain_list.h"

domain_list d_NEW() {
    domain_list x = (domain_list) malloc(sizeof(struct struct_domain_list));
    x->head = NULL;
    x->tail = NULL;
    return x;
}

domain_list d_insertEnd(domain_list l, char* d) {
    domain_list_link new_last = (domain_list_link) malloc(sizeof(struct domain_list_node));
    new_last->domain = d;
    new_last->counter = 1;
    if (l->tail == NULL) l->head = new_last;
    else l->tail->next = new_last;
    new_last->prev = l->tail;
    new_last->next = NULL;
    l->tail = new_last;
    return l;
}

domain_list_link d_search(domain_list_link head, char* text) {
    domain_list_link t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->domain, text) == 0) return t;
    return NULL;
}

domain_list d_delete(domain_list l, char* text) {
    domain_list_link t;
    for (t = l->head; t != NULL; t = t->next) {
        if (strcmp(t->domain, text) == 0) {
            if (t == l->head) l->head = l->head->next;
            if (t == l->tail) l->tail = l->tail->prev;
            if (t->next != NULL) t->next->prev = t->prev;
            if (t->prev != NULL) t->prev->next = t->next;
            free(t->domain);
            free(t);
            return l;
        }
    }
    return l;
}