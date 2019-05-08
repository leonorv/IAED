#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "contactos.h"

typedef struct node {
	Contacto contacto;
	struct node *l;
	struct node *r;
	int height;
} *link;

link NEW_NODE_TREE(Contacto c, link l, link r);
int height(link h);
link rotL(link h);
link rotR(link h);
link rotLR(link h);
link rotRL(link h);
int Balance(link h);
link AVLbalance(link h);
link insertR(link h, Contacto contacto);
link deleteR(link h, Key k);
Contacto searchR(link h, Key v);
Contacto STsearch(link head, Key v);
link max(link h);