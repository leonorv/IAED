#ifndef _LISTA_
#define _LISTA_

#include <stdlib.h>
#include <stdio.h>
#include "contactos.h"

typedef struct list_node {
    Contacto contacto;
    struct list_node *next, *prev;
} *list_link;

typedef struct struct_list {
    list_link head, tail;
} *list;

list NEW();
list insertEnd(list l, Contacto c);
void print(list_link head);
list_link lookup(list_link head, char* text);
list delete(list l, char* text);
void list_init(list_link head);

#endif