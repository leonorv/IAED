#ifndef _CONTACTS_
#define _CONTACTS_
#define key(A) (A != NULL ? A->name : "")
#define less(A, B) strcmp(A, B) < 0
#define equal(A, B) strcmp(A, B) == 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *strdup(const char *s);

typedef char *Key;
typedef struct stru_Email {
    char *local;
    Key domain;
} *Email;

typedef struct stru_Contact {
    Email email;
    Key name;
    char *phone;
} *Contact;

Email createEmail(char*, char*);
Contact createContact(Key, char*, Email);
void deleteContact(Contact c);
void printContact(Contact c);

#endif
