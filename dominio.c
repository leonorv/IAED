#include "dominio.h"

Item criaDominio(char *dominio) {
    Item new = (Item) malloc(sizeof(struct stru_Dominio));
    new->dominio = dominio;
    new->counter = 0;
    return new;
}

void apagaDominio(Item d) {
    free(d);
}