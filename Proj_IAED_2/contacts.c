#include "contacts.h"

Email createEmail(char *local, char *domain) {
    Email new = (Email) malloc(sizeof(struct stru_Email));
    new->local = strdup(local);
    new->domain = strdup(domain);
    return new; 
}

Contact createContact(char *name, char *phone, Email email) {
    Contact new = (Contact) malloc(sizeof(struct stru_Contact));
    new->name = strdup(name);
    new->phone = strdup(phone);
    new->email = email;
    return new;
}

void deleteContact(Contact c) {
    free(c->email->local);
    free(c->email->domain);
    free(c->email);
    free(c->name);
    free(c->phone);
    free(c);
}

void printContact(Contact c) {
    printf("%s %s@%s %s\n", c->name, c->email->local, c->email->domain, c->phone);
    return;
}