#ifndef _CONTACTOS_
#define _CONTACTOS_

#define key(A) (A != NULL ? A->nome : "")
#define less(A, B) strcmp(A, B) < 0
#define equal(A, B) strcmp(A, B) == 0

#include <stdio.h>
#include <stdlib.h>

typedef struct stru_Email {
    char *local, *dominio;
} *Email;

typedef char *Key;
typedef struct stru_Contacto {
    Email email;
    Key nome;
    char *telemovel;
} *Contacto;

Email criaEmail(char*, char*);
Contacto criaContacto(Key, char*, Email);
void apagaContacto(Contacto c);
void printContacto(Contacto c);

#endif
