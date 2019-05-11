#include "contactos.h"

Email criaEmail(char *local, char *dominio) {
    Email new = (Email) malloc(sizeof(struct stru_Email));
    new->local = strdup(local);
    new->dominio = strdup(dominio);


    return new; 
}

Contacto criaContacto(char *nome, char *tel, Email email) {
    Contacto new = (Contacto) malloc(sizeof(struct stru_Contacto));
    new->nome = strdup(nome);
    new->telemovel = strdup(tel);
    new->email = email;

    return new;
}

void apagaContacto(Contacto c) {
    free(c->email->local);
    free(c->email->dominio);
    free(c->email);
    free(c->nome);
    free(c->telemovel);
    free(c);
}

void printContacto(Contacto c) {
    printf("%s %s@%s %s\n", c->nome, c->email->local, c->email->dominio, c->telemovel);
    return;
}