/**** BEM-VINDX AO SEGUNDO PROJETO DE IAED ****/
/**** GESTOR DE CONTACTOS ****/
/* Aluna: Leonor Veloso 92509 */
#include "list.h"
#include "contacts.h"
#include "tree.h"
#include "domain_list.h"

/**** CONSTANTES ****/
#define FALSE 0
#define TRUE 1

#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64

/**** VARIAVEIS ESTATICAS ****/
static list list_simple; /* Lista que guarda os contactos por ordem de insercao */
static link tree_head; /* Arvore binaria que guarda os contactos por ordem alfabetica de nome */
static domain_list list_domains; /* Lista que guarda os dominios por ordem de insercao */

/**** COMANDO A ****/
void add() {
    char name_buffer[MAX_NAME], local_buffer[MAX_EMAIL], domain_buffer[MAX_EMAIL], phone_buffer[MAX_PHONE];
    char *name = NULL, *local = NULL, *domain = NULL, *phone = NULL; 
    Email email = NULL;
    Contact contact = NULL;
    domain_list_link node_domain = NULL;
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-] %[0-9-]", name_buffer, local_buffer, domain_buffer, phone_buffer);
    name = strdup(name_buffer);
    local = strdup(local_buffer);
    domain = strdup(domain_buffer);
    phone = strdup(phone_buffer);
    if (STsearch(tree_head, name) != NULL) {
        printf("Nome existente.\n");
        free(name);
        free(local);
        free(domain);
        free(phone);
        return;
    }
    email = createEmail(local, domain);
    contact = createContact(name, phone, email);
    list_simple = insertEnd(list_simple, contact);
    tree_head = insertR(tree_head, contact);
    node_domain = d_search(list_domains->head, domain);
    if (node_domain == NULL) list_domains = d_insertEnd(list_domains, domain);
    else {
        node_domain->counter++;
        free(domain);
    }
    free(name);
    free(local);
    free(phone);
    return;
}

/**** COMANDO P ****/
void search_for_contact() {
    char name_buffer[MAX_NAME];
    char *name = NULL;
    Contact c = NULL;
    scanf(" %[0-9a-zA-Z_-]", name_buffer);
    name = strdup(name_buffer);
    c = STsearch(tree_head, name);
    if (c == NULL) {
        printf("Nome inexistente.\n");
        free(name);
        return;
    }
    printContact(c);
    free(name);
    return;
}

/**** COMANDO R ****/
void delete_contact() {
    char name_buffer[MAX_NAME];
    char *name = NULL;
    Contact c = NULL;
    domain_list_link node_domain = NULL;
    scanf(" %[0-9a-zA-Z_-]", name_buffer);
    name = strdup(name_buffer);
    c = STsearch(tree_head, name);
    if (c == NULL) {
        printf("Nome inexistente.\n");
        free(name);
        return;
    }
    node_domain = d_search(list_domains->head, c->email->domain);
    if (node_domain->counter == 1) {
        list_domains = d_delete(list_domains, node_domain->domain);
    }
    else {
        node_domain->counter--;
    }
    list_simple = delete(list_simple, name);
    tree_head = deleteR(tree_head, name);
    free(name);
    return;
}

/**** COMANDO E ****/
void change_email() {
    char name_buffer[MAX_NAME], local_buffer[MAX_EMAIL], domain_buffer[MAX_EMAIL];
    char *name = NULL, *local = NULL, *domain = NULL;
    Email email = NULL;
    Contact c = NULL;
    domain_list_link node_domain = NULL;
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z-_.-]", name_buffer, local_buffer, domain_buffer);
    name = strdup(name_buffer);
    local = strdup(local_buffer);
    domain = strdup(domain_buffer);
    c = STsearch(tree_head, name);
    if (c == NULL) {
        printf("Nome inexistente.\n");
        free(name);
        free(local);
        free(domain);
        return;
    }
    email = createEmail(local, domain);
    node_domain = d_search(list_domains->head, c->email->domain);
    if (node_domain->counter == 1) {
        list_domains = d_delete(list_domains, node_domain->domain);
    }
    else {
        node_domain->counter--;
    }
    free(c->email->local);
    free(c->email->domain);
    free(c->email);
    c->email = email;
    node_domain = d_search(list_domains->head, c->email->domain);
    if (node_domain == NULL) list_domains = d_insertEnd(list_domains, domain);
    else node_domain->counter++;
    free(name);
    free(local);
    return;
}

/**** COMANDO C ****/
void count_domain() {
    char domain_buffer[MAX_EMAIL];
    char *domain = NULL;
    domain_list_link node_domain = NULL;
    scanf(" %[0-9a-zA-Z-_.-]", domain_buffer);
    domain = strdup(domain_buffer);
    node_domain = d_search(list_domains->head, domain);
    if (node_domain == NULL) {
        printf("%s:%d\n", domain, 0);
        free(domain);
        return;
    }
    else {
        printf("%s:%d\n", domain, node_domain->counter);
        free(domain);
        return;
    }
}

/**** AUX ***/ 
void free_list(list_link head) { /* Liberta a lista dos contatctos */ 
    list_link t, aux;
    for (t = head; t != NULL; t = aux) {
        aux = t->next;
        free(t);
    }
}

void traverse(link h) { /* Liberta a arvore */
    if (h == NULL) return;
    traverse(h->l);
    traverse(h->r);
    deleteContact(h->contact);
    free(h);
}

void d_free_list(domain_list_link head) { /* Liberta a lista dos dominios */
    domain_list_link t, aux;
    for (t = head; t != NULL; t = aux) {
        aux = t->next;
        free(t->domain);
        free(t);
    }
}

/**** MAIN ****/
int main() {
    int x = TRUE;
    int c;
    list_simple = NEW();
    tree_head = NULL;
    list_domains = d_NEW();
    c = getchar();
    while (x == TRUE) {
        switch(c) {
            case 'a':
                add();
                break;
            case 'l':
                print(list_simple->head);
                break;
            case 'p':
                search_for_contact();
                break;
            case 'r':
                delete_contact();
                break;
            case 'e':
                change_email();
                break;
            case 'c':
                count_domain();
                break;
            case 'x':
                free_list(list_simple->head);
                traverse(tree_head);
                d_free_list(list_domains->head);
                x = FALSE;
        }
        c = getchar();
    }
    return 0;
}