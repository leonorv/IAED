#ifndef _DOMAIN_LIST_
#define _DOMAIN_LIST_

#include <stdlib.h>
#include <stdio.h>

typedef struct domain_list_node {
    char *dominio;
	int counter;
    struct domain_list_node *next, *prev;
} *domain_list_link;

typedef struct struct_domain_list {
    domain_list_link head, tail;
} *domain_list;

domain_list d_NEW();
domain_list d_insertEnd(domain_list l, char* d);
domain_list_link d_lookup(domain_list_link head, char* text);
domain_list d_delete(domain_list l, char* text);
void d_list_init(domain_list_link head);

#endif