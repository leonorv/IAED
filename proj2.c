
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "contactos.h"
#include "tree.h"

#include "domain_list.h"


#define FALSE 0
#define TRUE 1

#define MAX_NOME 1024
#define MAX_EMAIL 512
#define MAX_TEL 64

/*static list_link head;*/
static list lista;
static link tree_head;
static domain_list lista_dominios;

void adiciona() {
    char nome_buffer[MAX_NOME], local_buffer[MAX_EMAIL], dominio_buffer[MAX_EMAIL], tel_buffer[MAX_TEL];
    char *nome = NULL, *local = NULL, *dominio = NULL, *tel = NULL; 
    Email email = NULL;
    Contacto contacto = NULL;
    domain_list_link node_dominio = NULL;
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-] %[0-9-]", nome_buffer, local_buffer, dominio_buffer, tel_buffer);
    nome = strdup(nome_buffer);
    local = strdup(local_buffer);
    dominio = strdup(dominio_buffer);
    tel = strdup(tel_buffer);
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

    lista = insertEnd(lista, contacto);
    tree_head = insertR(tree_head, contacto);

    node_dominio = d_lookup(lista_dominios->head, dominio);
    if (node_dominio == NULL) lista_dominios = d_insertEnd(lista_dominios, dominio);
    else {
        node_dominio->counter++;
        free(dominio);
    }


    free(nome);
    free(local);
    /*free(dominio);*/
    free(tel);


    return;
}

void procura() {
    char nome_buffer[MAX_NOME];
    char *nome = NULL;
    Contacto c = NULL;
    /*nome = (char*) malloc(sizeof(char)*MAX_NOME);*/
    scanf(" %[0-9a-zA-Z_-]", nome_buffer);
    nome = strdup(nome_buffer);
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
    char nome_buffer[MAX_NOME];
    char *nome = NULL;
    Contacto c = NULL;

    domain_list_link node_dominio = NULL;

    /*nome = (char*) malloc(sizeof(char)*MAX_NOME);*/
    scanf(" %[0-9a-zA-Z_-]", nome_buffer);
    nome = strdup(nome_buffer);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");

        free(nome);

        return;
    }

    node_dominio = d_lookup(lista_dominios->head, c->email->dominio);
    if (node_dominio->counter == 1) {
        lista_dominios = d_delete(lista_dominios, node_dominio->dominio);
    }
    else {
        node_dominio->counter--;
    }

    lista = delete(lista, nome);
    tree_head = deleteR(tree_head, nome);


    free(nome);



    return;
}

void mudaEmail() {
    char nome_buffer[MAX_NOME], local_buffer[MAX_EMAIL], dominio_buffer[MAX_EMAIL];
    char *nome = NULL, *local = NULL, *dominio = NULL;
    Email email = NULL;
    Contacto c = NULL;

    domain_list_link node_dominio = NULL;


    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-]", nome_buffer, local_buffer, dominio_buffer);
    nome = strdup(nome_buffer);
    local = strdup(local_buffer);
    dominio = strdup(dominio_buffer);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");

        free(nome);
        free(local);
        free(dominio);


        return;
    }
    email = criaEmail(local, dominio);


    node_dominio = d_lookup(lista_dominios->head, c->email->dominio);
    if (node_dominio->counter == 1) {
        lista_dominios = d_delete(lista_dominios, node_dominio->dominio);
    }
    else {
        node_dominio->counter--;
    }

    free(c->email->local);
    free(c->email->dominio);
    free(c->email);
    c->email = email;

    node_dominio = d_lookup(lista_dominios->head, c->email->dominio);
    if (node_dominio == NULL) lista_dominios = d_insertEnd(lista_dominios, dominio);
    else node_dominio->counter++;


    free(nome);
    free(local);
    /*free(dominio);*/


    return;
}

void contaDominio() {
    char dominio_buffer[MAX_EMAIL];
    char *dominio = NULL;
    domain_list_link node_dominio = NULL;
    scanf(" %[0-9a-zA-Z-_.-]", dominio_buffer);
    dominio = strdup(dominio_buffer);
    node_dominio = d_lookup(lista_dominios->head, dominio);
    if (node_dominio == NULL) {
        printf("%s:%d\n", dominio, 0);
        free(dominio);
        return;
    }
    else {
        printf("%s:%d\n", dominio, node_dominio->counter);
        free(dominio);
        return;
    }

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

void d_freeList(domain_list_link head) {
    domain_list_link t, aux;
    for (t = head; t != NULL; t = aux) {
        aux = t->next;
        free(t->dominio);
        free(t);
    }
}

int main() {
    int x = TRUE;
    int c;
    lista = NEW();
    tree_head = NULL;
    lista_dominios = d_NEW();
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
                d_freeList(lista_dominios->head);
                x = FALSE;
        }
        c = getchar();
    }
    return 0;
}

