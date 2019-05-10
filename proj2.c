
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "contactos.h"
#include "tree.h"

/*#include "domain_list.h"
#include "dominio.h"*/

#define FALSE 0
#define TRUE 1

#define MAX_NOME 1024
#define MAX_EMAIL 512
#define MAX_TEL 64

/*static list_link head;*/
static list lista;
static link tree_head;
/*static domain_link domain_head;*/

void adiciona() {
    char *nome = NULL, *local = NULL, *dominio = NULL, *tel = NULL; 
    Email email = NULL;
    Contacto contacto = NULL;

    /*Dominio struct_dominio = NULL;*/

    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    local = (char*) malloc(sizeof(char)*MAX_EMAIL);
    dominio = (char*) malloc(sizeof(char)*MAX_EMAIL);
    tel = (char*) malloc(sizeof(char)*MAX_TEL);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-] %[0-9-]", nome, local, dominio, tel);
    if (STsearch(tree_head, nome) != NULL) {
        printf("Nome existente.\n");
        free(nome);
        free(local);
        free(dominio);
        free(tel);
        return;
    }
    email = criaEmail(local, dominio);
    contacto = criaContacto(nome, tel, email);


    /*head*/lista = insertEnd(lista, contacto);
    tree_head = insertR(tree_head, contacto);


    /*struct_dominio = d_STsearch(domain_head, contacto->email->dominio);
    if (struct_dominio == NULL) domain_head = d_insertR(domain_head, criaDominio(dominio));
    else {
        struct_dominio->counter++;
    }*/

    free(nome);
    free(local);
    free(dominio);
    free(tel);
    return;
}

void procura() {
    char *nome = NULL;
    Contacto c = NULL;
    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    scanf(" %[0-9a-zA-Z_-]", nome);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");

        free(nome);

        return;
    }
    printContacto(c);

    free(nome);

    return;
}

void apaga() {
    char *nome = NULL;
    Contacto c = NULL;

    /*Dominio struct_dominio = NULL;*/

    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    scanf(" %[0-9a-zA-Z_-]", nome);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");

        free(nome);

        return;
    }

    /*struct_dominio = d_STsearch(domain_head, c->email->dominio);
    if (struct_dominio->counter == 1) {
        domain_head = d_deleteR(domain_head, struct_dominio->nome_dominio);
    }
    else {
        struct_dominio->counter--;
    }*/

    lista = delete(lista, nome);
    tree_head = deleteR(tree_head, nome);


    free(nome);



    return;
}

void mudaEmail() {
    char *nome = NULL, *local = NULL, *dominio = NULL;
    Email email = NULL;
    Contacto c = NULL;
    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    local = (char*) malloc(sizeof(char)*MAX_EMAIL);
    dominio = (char*) malloc(sizeof(char)*MAX_EMAIL);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-]", nome, local, dominio);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");

        free(nome);
        free(local);
        free(dominio);


        return;
    }
    email = criaEmail(local, dominio);
    free(c->email->local);
    free(c->email->dominio);
    free(c->email);
    c->email = email;

    free(nome);
    free(local);
    free(dominio);


    return;
}

void contaDominio() {
    /*char *dominio = (char*) malloc(sizeof(char)*MAX_EMAIL);
    Dominio struct_dominio;
    scanf(" %[0-9a-zA-Z-_.-]", dominio);
    struct_dominio = d_STsearch(domain_head, dominio);
    if (struct_dominio != NULL) {
        printf("%s:%d\n", dominio, struct_dominio->counter);
        free(dominio);
        return;
    }
    else {
        printf("%s:%d\n", dominio, 0);
        free(dominio);
        return;
    }*/
    char *dominio = (char*) malloc(sizeof(char)*MAX_EMAIL);
    list_link t, aux;
    int counter = 0;
    scanf(" %[0-9a-zA-Z-_.-]", dominio);
    for (t = lista->head; t != NULL; t = aux) {
        if (strcmp(t->contacto->email->dominio, dominio) == 0) counter++;
        aux = t->next;
    }
    printf("%s:%d\n", dominio, counter);
    free(dominio);
}

void freeList(list_link head) {
    list_link t, aux;
    for (t = head; t != NULL; t = aux) {
        aux = t->next;
        free(t);
    }
}

void traverse(link h) {
    if (h == NULL) return;
    traverse(h->l);
    traverse(h->r);
    apagaContacto(h->contacto);
    free(h);
}

/*void d_traverse(domain_link h) {
    if (h == NULL) return;
    d_traverse(h->l);
    d_traverse(h->r);
    apagaDominio(h->dominio);
    free(h);
}*/

int main() {
    int x = TRUE;
    int c;
    /*head = NULL;*/
    lista = NEW();
    tree_head = NULL;
    /*domain_head = NULL;*/
    c = getchar();
    while (x == TRUE) {
        switch(c) {
            case 'a':
                adiciona();
                break;
            case 'l':
                print(lista->head);
                break;
            case 'p':
                procura();
                break;
            case 'r':
                apaga();
                break;
            case 'e':
                mudaEmail();
                break;
            case 'c':
                contaDominio();
                break;
            case 'x':
                freeList(lista->head);
                traverse(tree_head);
                /*d_traverse(domain_head);*/
                x = FALSE;
        }
        c = getchar();
    }
    return 0;
}

