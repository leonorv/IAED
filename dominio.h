#ifndef _DOMINIO_
#define _DOMINIO_

#include <stdio.h>
#include <stdlib.h>

typedef char *Key;

typedef struct stru_Dominio {
    Key dominio;
    int counter;
} *Dominio;


Item criaDominio(Key, char*);
void apagaDominio(Item d);

#endif