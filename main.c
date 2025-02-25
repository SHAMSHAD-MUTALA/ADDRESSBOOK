#include <stdio.h>
#include "contact.h"

int main() {
    AddressBook addressBook;
    initialize(&addressBook);
    displayContacts(&addressBook);

    // Menu for user interaction

    int choice;
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. List Contacts\n");
        printf("2. Create Contact\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listContacts(&addressBook);
                break;
            case 2:
                createContact(&addressBook);
                break;
            case 3:
                searchContact(&addressBook);
                break;
            case 4:
                editContact(&addressBook);
                break;
            case 5:
                deleteContact(&addressBook);
                break;
            case 6: // Save Contacts
                save_contacts(&addressBook);
                break;
            case 7: // Exit
                printf("Warning: Do you want to save changes before exiting? (y/n): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    save_contacts(&addressBook);
                }
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 7);


    return 0;
}
