#ifndef _LISTA_
#define _LISTA_

#include <stdlib.h>
#include <stdio.h>
#include "contactos.h"

typedef struct list_node {
    Contacto contacto;
    struct list_node *next;
} *list_link;

list_link NEW(Contacto c);
list_link insertEnd(list_link head, Contacto c);
void print(list_link head);
list_link lookup(list_link head, char* text);
list_link delete(list_link head, char* text);
void list_init(list_link head);

#endif