#ifndef _DOMINIOS_
#define _DOMINIOS_

#define d_key(A) (A != NULL ? A->nome_dominio : "")
#define d_less(A, B) strcmp(A, B) < 0
#define d_equal(A, B) strcmp(A, B) == 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *strdup(const char *s);

typedef char *d_Key;
typedef struct stru_Dominio {
    d_Key nome_dominio;
    int counter;
} *Dominio;

Dominio criaDominio(d_Key k);
void apagaDominio(Dominio d);

#endif