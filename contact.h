#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
    int modified;
} AddressBook;


void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void save_contacts(AddressBook *addressBook);
void undo_last_change(AddressBook *addressBook);
void export_contacts(AddressBook *addressBook);
void sort_contacts(AddressBook *addressbook, int mode);

// Validation function prototypes
int isValidName(const char *name);
int isValidPhone(const char *phone);
int isValidEmail(const char *email);

// Sorting comparison functions
int compare_name(const void *a, const void *b);
int compare_phone(const void *a, const void *b);
int compare_email(const void *a, const void *b);


#endif
