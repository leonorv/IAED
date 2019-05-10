#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dominio.h"

typedef struct domain_node {
	Dominio dominio;
	struct domain_node *l;
	struct domain_node *r;
	int height;
} *domain_link;

domain_link d_NEW_NODE_TREE(Dominio d, domain_link l, domain_link r);
int d_height(domain_link h);
domain_link d_rotL(domain_link h);
domain_link d_rotR(domain_link h);
domain_link d_rotLR(domain_link h);
domain_link d_rotRL(domain_link h);
int d_Balance(domain_link h);
domain_link d_AVLbalance(domain_link h);
domain_link d_insertR(domain_link h, Dominio dominio);
domain_link d_deleteR(domain_link h, d_Key k);
Dominio d_searchR(domain_link h, char* v);
Dominio d_STsearch(domain_link head, char* v);
domain_link d_max(domain_link h);