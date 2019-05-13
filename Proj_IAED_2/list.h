/*** LISTA DUPLAMENTE LIGADA ****/
#ifndef _LIST_
#define _LIST_

#include <stdlib.h>
#include <stdio.h>
#include "contacts.h"

typedef struct list_node {
    Contact contact;
    struct list_node *next, *prev;
} *list_link;

typedef struct struct_list {
    list_link head, tail;
} *list;

list NEW();
list insertEnd(list l, Contact c);
void print(list_link head);
list delete(list l, char* text);

#endif