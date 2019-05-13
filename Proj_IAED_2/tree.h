/**** ARVORE BINARIA ****/
/* Source code: slides de IAED 2014/2015 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "contacts.h"

typedef struct node {
	Contact contact;
	struct node *l;
	struct node *r;
	int height;
} *link;

link NEW_NODE_TREE(Contact c, link l, link r);
int height(link h);
link rotL(link h);
link rotR(link h);
link rotLR(link h);
link rotRL(link h);
int Balance(link h);
link AVLbalance(link h);
link insertR(link h, Contact contact);
link deleteR(link h, Key k);
Contact searchR(link h, Key v);
Contact STsearch(link head, Key v);
link max(link h);