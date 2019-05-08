
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "contactos.h"
#include "tree.h"

#define FALSE 0
#define TRUE 1

#define MAX_NOME 1024
#define MAX_EMAIL 512
#define MAX_TEL 64

static list_link head;
static link tree_head;

void adiciona() {
    char *nome = NULL, *local = NULL, *dominio = NULL, *tel = NULL; 
    Email email = NULL;
    Contacto contacto = NULL;
    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    local = (char*) malloc(sizeof(char)*MAX_EMAIL);
    dominio = (char*) malloc(sizeof(char)*MAX_EMAIL);
    tel = (char*) malloc(sizeof(char)*MAX_TEL);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-] %[0-9-]", nome, local, dominio, tel);
    if (STsearch(tree_head, nome) != NULL) {
        printf("Nome existente.\n");
        return;
    }
    email = criaEmail(local, dominio);
    contacto = criaContacto(nome, tel, email);
    head = insertEnd(head, contacto);
    tree_head = insertR(tree_head, contacto);
    return;
}

void procura() {
    char *nome = NULL;
    Contacto c = NULL;
    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    c = (Contacto) malloc(sizeof(struct stru_Contacto));
    scanf(" %[0-9a-zA-Z_-]", nome);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");
        return;
    }
    printContacto(c);
    return;
}

void apaga() {
    char *nome = NULL;
    Contacto c = NULL;
    nome = (char*) malloc(sizeof(char)*MAX_NOME);
    scanf(" %[0-9a-zA-Z_-]", nome);
    c = STsearch(tree_head, nome);
    if (c == NULL) {
        printf("Nome inexistente.\n");
        return;
    }
    head = delete(head, nome);
    tree_head = deleteR(tree_head, nome);
    apagaContacto(c);
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
        return;
    }
    email = criaEmail(local, dominio);
    c->email = email;
    return;
}

void contaDominio() {
    
}


int main() {
    int x = TRUE;
    int c;
    head = NULL;
    tree_head = NULL;
    c = getchar();
    while (x == TRUE) {
        switch(c) {
            case 'a':
                adiciona();
                break;
            case 'l':
                print(head);
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
                x = FALSE;
        }
        c = getchar();
    }
    return 0;
}

