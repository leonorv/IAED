#include "dominio.h"

Dominio criaDominio(char *nome) {
    Dominio new = (Dominio) malloc(sizeof(struct stru_Dominio));
    new->nome_dominio = strdup(nome);
    new->counter = 1;
    return new;
}

void apagaDominio(Dominio d) {
    free(d->nome_dominio);
    free(d);
}