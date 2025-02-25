#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// Validation functions
int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name极[i] != ' ') {
            return 0; // Invalid name
        }
    }
    return 1; // Valid name
}

int isValidPhone(const char *phone) {
    if (strlen(phone) != 10) return 0; // Must be 10 digits
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0; // Invalid phone number
        }
    }
    return 1; // Valid phone number
}

int isValidEmail(const char *email) {
    if (strstr(email, "@") == NULL || strstr(email, ".com") == NULL) {
        return 0; // Invalid email
    }
    return 1; // Valid email
}

void initialize(AddressBook *addressBook) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/contact.txt", getcwd(NULL, 0));
    printf("Loading contacts from: %s\n", fullPath);
    
    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        printf("Error: Could not open %s\n", fullPath);
        return;
    }


    addressBook->contactCount = 0;
    addressBook->modified = 0;
    
    while (!feof(file) && addressBook->contactCount < MAX_CONTACTS) {
        Contact newContact;
        if (fscanf(file, "%49[^,],%19[^,],%49s\n", 
                  newContact.name, newContact.phone, newContact.email) == 3) {
            addressBook->contacts[addressBook->contactCount] = newContact;
            addressBook->contactCount++;
        }
    }

    fclose(file);
    printf("Loaded %d contacts from file.\n", addressBook->contactCount);
}

// ... [rest of the functions remain the same until save_contacts]

void save_contacts(AddressBook *addressBook) {
    // Print full file path for debugging
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/contact.txt", getcwd(NULL, 0));
    printf("Saving contacts to: %s\n", fullPath);

    FILE *file = fopen("contact.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save contacts to file\n");
        return;
    }

    int writeSuccess = 1;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email) < 0) {
            writeSuccess = 0;
            break;
        }
    }

    if (fclose(file) != 0) {
        printf("Error: Failed to properly close the file\n");
        return;
    }

    if (!writeSuccess) {
        printf("Error: Failed to write all contacts to file\n");
        return;
    }

    addressBook->modified = 0;
    printf("✅ Contacts saved successfully! (%d contacts written)\n", addressBook->contactCount);
}

// [Rest of the functions remain unchanged...]
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            addressBook->modified = 1;
            printf("Contact deleted successfully!\n");
            save_contacts(addressBook);
            return;
        }
    }
        int valid = 1;
        Contact newContact;




        if (valid) {
            printf("Enter email address: ");
            scanf("%s", newContact.email);
            // Check if email already exists
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcasecmp(addressBook->contacts[i].email, newContact.email) == 0) {
                    printf("!!!Email exists!!!\n");
                    valid = 0;
                    printf("Please enter a different email or choose another option.\n");
                    break;
                }
            }
        }

        // Validate name
        if (valid && !isValidName(newContact.name)) {
            printf("!!!Invalid name!!! Only alphabets and spaces are allowed.\n");
            valid = 0;
        }

        // Validate phone number
        if (valid && !isValidPhone(newContact.phone)) {
            printf("!!!Invalid phone number!!! Must be 10 digits.\n");
            valid = 0;
        }

        // Validate email
        if (valid && !isValidEmail(newContact.email)) {
            printf("!!!Invalid email!!! Must contain '@' and end with '.com'.\n");
            valid = 0;
        }
    }

    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++;
    addressBook->modified = 1;
    printf("!!!Contact added successfully!!!\n");
    save_contacts(addressBook);
}

void searchContact(AddressBook *addressBook) {
    int option;
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option) {
        case 1: {
            char name[50];
            printf("Enter name to search: ");
            scanf(" %[^\n]", name);
            printf("Matching contacts:\n");
            int found = 0;
            int matchingIndices[MAX_CONTACTS];
            
            // Convert search input to lowercase
            char lowerName[50];
            strcpy(lowerName, name);
            for (int j = 0; lowerName[j]; j++) {
                lowerName[j] = tolower(lowerName[j]);
            }
            
            for (int i = 0; i < addressBook->contactCount; i++) {
                // Convert contact name to lowercase
                char lowerContactName[50];
                strcpy(lowerContactName, addressBook->contacts[i].name);
                for (int j = 0; lowerContactName[j]; j++) {
                    lowerContactName[j] = tolower(lowerContactName[j]);
                }
                
                if (strstr(lowerContactName, lowerName) != NULL) {
                    matchingIndices[found] = i;
                    printf("%d. %s - %s - %s\n", 
                           found + 1, 
                           addressBook->contacts[i].name, 
                           addressBook->contacts[i].phone, 
                           addressBook->contacts[i].email);
                    found++;
                }
            }
            if (found > 0) {
                int choice;
                printf("Enter the number of the contact you want to view: ");
                scanf("%d", &choice);
                if (choice > 0 && choice <= found) {
                    printf("Contact details:\n");
                    printf("Name: %s\n", addressBook->contacts[matchingIndices[choice - 1]].name);
                    printf("Phone: %s\n", addressBook->contacts[matchingIndices[choice - 1]].phone);
                    printf("Email: %s\n", addressBook->contacts[matchingIndices[choice - 1]].email);

                } else {
                    printf("Invalid choice.\n");
                }
            } else {
                printf("Contact not found.\n");
            }
            break;
        }
        case 2: {
            char phone[20];
            printf("Enter phone number to search: ");
            scanf("%s", phone);
            printf("Matching contacts:\n");
            int found = 0;
            int matchingIndices[MAX_CONTACTS];
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].phone, phone) != NULL) {
                    matchingIndices[found] = i;
                    printf("%d. %s - %s - %s\n", 
                           found + 1, 
                           addressBook->contacts[i].name, 
                           addressBook->contacts[i].phone, 
                           addressBook->contacts[i].email);
                    found++;
                }
            }
            if (found > 0) {
                int choice;
                printf("Enter the number of the contact you want to view: ");
                scanf("%d", &choice);
                if (choice > 0 && choice <= found) {
                    printf("Contact details:\n");
                    printf("Name: %s\n", addressBook->contacts[matchingIndices[choice - 1]].name);
                    printf("Phone: %s\n", addressBook->contacts[matchingIndices[choice - 1]].phone);
                    printf("Email: %s\n", addressBook->contacts[matchingIndices[choice - 1]].email);
                } else {
                    printf("Invalid choice.\n");
                }
            } else {
                printf("Contact not found.\n");
            }
            break;
        }
        case 3: {
            char email[50];
            printf("Enter email to search: ");
            scanf("%s", email);
            printf("Matching contacts:\n");
            int found = 0;
            int matchingIndices[MAX_CONTACTS];
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].email, email) != NULL) {
                    matchingIndices[found] = i;
                    printf("%d. %s - %s - %s\n", 
                           found + 1, 
                           addressBook->contacts[i].name, 
                           addressBook->contacts[i].phone, 
                           addressBook->contacts[i].email);
                    found++;
                }
            }
            if (found > 0) {
                int choice;
                printf("Enter the number of the contact you want to view: ");
                scanf("%d", &choice);
                if (choice > 0 && choice <= found) {
                    printf("Contact details:\n");
                    printf("Name: %s\n", addressBook->contacts[matchingIndices[choice - 1]].name);
                    printf("Phone: %s\n", addressBook->contacts[matchingIndices[choice - 1]].phone);
                    printf("Email: %s\n", addressBook->contacts[matchingIndices[choice - 1]].email);
                } else {
                    printf("Invalid choice.\n");
                }
            } else {
                printf("Contact not found.\n");
            }
            break;
        }
        default:
            printf("Invalid option.\n");
            break;
    }
}

void editContact(AddressBook *addressBook) {
    char name[50];
    int option;
    printf("Enter a partial name to search for the contact to edit: ");
    scanf(" %[^\n]", name);
    printf("Matching contacts:\n");
    int found = 0;
    int matchingIndices[MAX_CONTACTS];
    // Convert search input to lowercase
    char lowerName[50];
    strcpy(lowerName, name);
    for (int j = 0; lowerName[j]; j++) {
        lowerName[j] = tolower(lowerName[j]);
    }
    
    for (int i = 0; i < addressBook->contactCount; i++) {
        // Convert contact name to lowercase
        char lowerContactName[50];
        strcpy(lowerContactName, addressBook->contacts[i].name);
        for (int j = 0; lowerContactName[j]; j++) {
            lowerContactName[j] = tolower(lowerContactName[j]);
        }
        
        if (strstr(lowerContactName, lowerName) != NULL) {
            matchingIndices[found] = i;
            printf("%d. %s - %s - %s\n", 
                   found + 1, 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found++;
        }
    }

    if (found > 0) {
        int choice;
        printf("Enter the number of the contact you want to edit: ");
        scanf("%d", &choice);
        if (choice > 0 && choice <= found) {
            printf("What do you want to edit?\n");
            printf("1. Edit all (name, phone, email)\n");
            printf("2. Edit name and phone\n");
            printf("3. Edit name and email\n");
            printf("4. Edit only name\n");
            printf("5. Edit only phone\n");
            printf("6. Edit only email\n");
            printf("Enter your choice: ");
            scanf("%d", &option);

            int valid = 0;
            char newName[50], newPhone[20], newEmail[50];
            switch (option) {
                case 1: // Edit all
                    while (!valid) {
                        valid = 1;
                        printf("Enter new name: ");
                        scanf(" %[^\n]", newName);
                        printf("Enter new phone: ");
                        scanf("%s", newPhone);
                        printf("Enter new email: ");
                        scanf("%s", newEmail);
                        // Check for uniqueness
                        for (int j = 0; j < addressBook->contactCount; j++) {
                            if (j != matchingIndices[choice - 1]) {
                                if (strcasecmp(addressBook->contacts[j].name, newName) == 0) {
                                    printf("!!!Name already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different name.\n");
                                }
                                if (strcmp(addressBook->contacts[j].phone, newPhone) == 0) {
                                    printf("!!!Phone number already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different phone number.\n");
                                }
                                if (strcasecmp(addressBook->contacts[j].email, newEmail) == 0) {
                                    printf("!!!Email already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different email.\n");
                                }
                            }
                        }
                        // Check if new details are the same as existing
                        if (strcasecmp(addressBook->contacts[matchingIndices[choice - 1]].name, newName) == 0) {
                            printf("The new name is the same as the existing name. Please enter a different name.\n");
                            valid = 0;
                        }
                        if (strcmp(addressBook->contacts[matchingIndices[choice - 1]].phone, newPhone) == 0) {
                            printf("The new phone number is the same as the existing phone number. Please enter a different phone number.\n");
                            valid = 0;
                        }
                        if (strcasecmp(addressBook->contacts[matchingIndices[choice - 1]].email, newEmail) == 0) {
                            printf("The new email is the same as the existing email. Please enter a different email.\n");
                            valid = 0;
                        }
                    }
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].name, newName);
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].phone, newPhone);
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].email, newEmail);
                    printf("Contact updated successfully!\n");
                    addressBook->modified = 1;
                    save_contacts(addressBook);
                    break;
                case 2: // Edit name and phone
                    while (!valid) {
                        valid = 1;
                        printf("Enter new name: ");
                        scanf(" %[^\n]", newName);
                        printf("Enter new phone: ");
                        scanf("%s", newPhone);
                        // Check for uniqueness
                        for (int j = 0; j < addressBook->contactCount; j++) {
                            if (j != matchingIndices[choice - 1]) {
                                if (strcasecmp(addressBook->contacts[j].name, newName) == 0) {
                                    printf("!!!Name already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different name.\n");
                                }
                                if (strcmp(addressBook->contacts[j].phone, newPhone) == 0) {
                                    printf("!!!Phone number already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different phone number.\n");
                                }
                            }
                        }
                        // Check if new details are the same as existing
                        if (strcasecmp(addressBook->contacts[matchingIndices[choice - 1]].name, newName) == 0) {
                            printf("The new name is the same as the existing name. Please enter a different name.\n");
                            valid = 0;
                        }
                    }
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].name, newName);
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].phone, newPhone);
                    printf("Contact updated successfully!\n");
                    addressBook->modified = 1;
                    save_contacts(addressBook);
                    break;
                case 3: // Edit name and email
                    while (!valid) {
                        valid = 1;
                        printf("Enter new name: ");
                        scanf(" %[^\n]", newName);
                        printf("Enter new email: ");
                        scanf("%s", newEmail);
                        // Check for uniqueness
                        for (int j = 0; j < addressBook->contactCount; j++) {
                            if (j != matchingIndices[choice - 1]) {
                                if (strcasecmp(addressBook->contacts[j].name, newName) == 0) {
                                    printf("!!!Name already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different name.\n");
                                }
                                if (strcasecmp(addressBook->contacts[j].email, newEmail) == 0) {
                                    printf("!!!Email already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different email.\n");
                                }
                            }
                        }
                        // Check if new details are the same as existing
                        if (strcasecmp(addressBook->contacts[matchingIndices[choice - 1]].name, newName) == 0) {
                            printf("The new name is the same as the existing name. Please enter a different name.\n");
                            valid = 0;
                        }
                    }
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].name, newName);
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].email, newEmail);
                    printf("Contact updated successfully!\n");
                    addressBook->modified = 1;
                    save_contacts(addressBook);
                    break;
                case 4: // Edit only name
                    while (!valid) {
                        valid = 1;
                        printf("Enter new name: ");
                        scanf(" %[^\n]", newName);
                        // Check for uniqueness
                        for (int j = 0; j < addressBook->contactCount; j++) {
                            if (j != matchingIndices[choice - 1]) {
                if (strcasecmp(addressBook->contacts[j].name, newName) == 0) {

                                    printf("!!!Name already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different name.\n");
                                }
                            }
                        }
                        // Check if new details are the same as existing
                        if (strcasecmp(addressBook->contacts[matchingIndices[choice - 1]].name, newName) == 0) {
                            printf("The new name is the same as the existing name. Please enter a different name.\n");
                            valid = 0;
                        }
                    }
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].name, newName);
                    printf("Contact updated successfully!\n");
                    addressBook->modified = 1;
                    save_contacts(addressBook);
                    break;
                case 5: // Edit only phone
                    while (!valid) {
                        valid = 1;
                        printf("Enter new phone: ");
                        scanf("%s", newPhone);
                        // Check for uniqueness
                        for (int j = 0; j < addressBook->contactCount; j++) {

                            if (j != matchingIndices[choice - 1]) {
                                if (strcmp(addressBook->contacts[j].phone, newPhone) == 0) {
                                    printf("!!!Phone number already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different phone number.\n");
                                }
                            }
                        }
                        // Check if new details are the same as existing
                        if (strcmp(addressBook->contacts[matchingIndices[choice - 1]].phone, newPhone) == 0) {
                            printf("The new phone number is the same as the existing phone number. Please enter a different phone number.\n");
                            valid = 0;
                        }
                    }
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].phone, newPhone);
                    printf("Contact updated successfully!\n");
                    addressBook->modified = 1;
                    save_contacts(addressBook);
                    break;
                case 6: // Edit only email
                    while (!valid) {
                        valid = 1;
                        printf("Enter new email: ");
                        scanf("%s", newEmail);
                        // Check for uniqueness
                        for (int j = 0; j < addressBook->contactCount; j++) {
                            if (j != matchingIndices[choice - 1]) {
                                if (strcasecmp(addressBook->contacts[j].email, newEmail) == 0) {
                                    printf("!!!Email already exists!!!\n");
                                    valid = 0;
                                    printf("Please enter a different email.\n");
                                }
                            }
                        }
                        // Check if new details are the same as existing
                        if (strcasecmp(addressBook->contacts[matchingIndices[choice - 1]].email, newEmail) == 0) {
                            printf("The new email is the same as the existing email. Please enter a different email.\n");
                            valid = 0;
                        }
                    }
                    strcpy(addressBook->contacts[matchingIndices[choice - 1]].email, newEmail);
                    printf("Contact updated successfully!\n");
                    addressBook->modified = 1;
                    save_contacts(addressBook);
                    break;
                default:
                    printf("Invalid option.\n");
                    break;
            }
        } else {
            printf("Invalid choice.\n");
        }
    } else {
        printf("No matching contacts found.\n");
    }
}

// Function to save contacts to file
void save_contacts(AddressBook *addressBook) {

    FILE *file = fopen("contact.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save contacts to file\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    addressBook->modified = 0;
    printf("✅ Contacts saved successfully!\n");
}

// Function to exit the program
void displayContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts found.\n");
        return;
    }
    
    printf("\nCurrent Contacts:\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%d. %s - %s - %s\n", 
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------\n");
}

void exit_program(AddressBook *addressBook) {


    if (addressBook->modified) {
        printf("\n⚠️  You have unsaved changes! Do you want to save before exiting? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            save_contacts(addressBook);
        }
    }
    printf("👋 Exiting program...\n");
    exit(0);
}

// Function to delete a contact
void deleteContact(AddressBook *addressBook) {

    char name[50];
    printf("Enter the full name of the contact you wish to delete: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasecmp(addressBook->contacts[i].name, name) == 0) {
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            addressBook->modified = 1;
            printf("Contact deleted successfully!\n");
            save_contacts(addressBook);
            return;
        }
    }
    printf("Contact not found.\n");
}
