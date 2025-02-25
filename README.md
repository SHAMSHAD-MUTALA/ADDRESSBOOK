# Address Book Application

## Overview
The Address Book application is a simple C-based contact management system that allows users to store, search, edit, delete, and list contacts. It supports basic validation and persistent storage using a text file.

## Features
- Add new contacts with name, phone number, and email.
- Search contacts by name, phone number, or email.
- Edit existing contact details.
- Delete contacts from the address book.
- List all saved contacts.
- Save and load contacts from a file (`contact.txt`).
- Ensures input validation for names, phone numbers, and email addresses.

## Files Structure
- `main.c`: Entry point of the application with a menu-driven interface.
- `contact.h`: Header file containing structure definitions and function prototypes.
- `contact.c`: Implementation of contact management functions.
- `dummy_contact.c`: Contains dummy contact data for testing purposes.
- `addressbook`: Contact storage file (created during execution).

## Compilation and Execution
To compile and run the program:
```sh
gcc main.c contact.c dummy_contact.c -o addressbook
./addressbook
```

## Usage
1. Run the executable.
2. Select options from the menu:
   - `1` to list contacts
   - `2` to create a new contact
   - `3` to search for a contact
   - `4` to edit a contact
   - `5` to delete a contact
   - `6` to save contacts
   - `7` to exit
3. Follow the prompts for each option.

## Future Enhancements
- Implement sorting options (by name, phone, email).
- Add undo functionality for accidental deletions.
- Improve error handling and file backup.

## License
This project is open-source and free to use for learning purposes.

