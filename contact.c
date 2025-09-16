#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    printf("----------------------------------------------------------------------\n");
    printf("\t\t ENTERED INTO LIST CONTACT");
    printf("\n----------------------------------------------------------------------\n");
    // Sort contacts based on the chosen criteria
   if (addressBook->contactCount == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("-------------------------------------------------------\n");
    printf("| %-20s | %-12s | %-25s |\n", "Name", "Phone", "Email");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; ++i) {
        Contact c = addressBook->contacts[i];
        printf("| %-20s  %-12s  %-25s \n", c.name, c.phone, c.email);
    }

    printf("-------------------------------------------------------\n");
}
    

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("Address book is full. Cannot add more contacts.\n");
        return;
    }

    Contact newContact;

    printf("\nENTERED INTO CREATE CONTACT\n");

    // Clear any leftover newline from previous input (like scanf)
    while ((getchar()) != '\n');

    printf("Enter the name  : ");
    fgets(newContact.name, sizeof(newContact.name), stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter ph no     : ");
    fgets(newContact.phone, sizeof(newContact.phone), stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';

    printf("Enter the email : ");
    fgets(newContact.email, sizeof(newContact.email), stdin);
    newContact.email[strcspn(newContact.email, "\n")] = '\0';

    addressBook->contacts[addressBook->contactCount++] = newContact;

    printf("Contact added successfully.\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char keyword[50];
    printf("----------------------------------------------------------------------\n");
    printf("\t\t ENTERED INTO SEARCH CONTACT");
    printf("\n----------------------------------------------------------------------\n");
    printf("Search By:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while ((getchar()) != '\n'); // flush newline

    printf("Enter the value you want to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';  // Remove newline

    int found = 0;

    //printf("\n----------------------------------------------------------------------\n");
    //printf("| %-20s | %-12s | %-25s |\n", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; ++i) {
        Contact c = addressBook->contacts[i];
        if ((choice == 1 && strcasecmp(c.name, keyword) == 0) ||
            (choice == 2 && strcmp(c.phone, keyword) == 0) ||
            (choice == 3 && strcasecmp(c.email, keyword) == 0)) {
            printf("| %-20s | %-12s | %-25s |\n", c.name, c.phone, c.email);
            found = 1;
        }
    }

    if (!found) {
        printf("| %-65s |\n", "Contact not found.");
    }

    printf("----------------------------------------------------------------------\n");
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    if (addressBook->contactCount == 0) {
        printf("No contacts available to edit.\n");
        return;
    }

    int searchChoice;
    char keyword[50];
    int foundIndex = -1;

    printf("----------------------------------------------------------------------\n");
    printf("\t\t ENTERED INTO EDIT CONTACT");
    printf("\n----------------------------------------------------------------------\n");

    printf("Search by\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    printf("ENTER your choice : ");
    scanf("%d", &searchChoice);
    while ((getchar()) != '\n'); // flush newline

    printf("Enter the ");
    if (searchChoice == 1) printf("name : ");
    else if (searchChoice == 2) printf("phone : ");
    else if (searchChoice == 3) printf("email : ");
    else {
        printf("Invalid choice.\n");
        return;
    }

    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    // Find the contact
    for (int i = 0; i < addressBook->contactCount; ++i) {
        Contact c = addressBook->contacts[i];
        if ((searchChoice == 1 && strcasecmp(c.name, keyword) == 0) ||
            (searchChoice == 2 && strcmp(c.phone, keyword) == 0) ||
            (searchChoice == 3 && strcasecmp(c.email, keyword) == 0)) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Contact not found.\n");
        return;
    }

    // Display found contact
    Contact *c = &addressBook->contacts[foundIndex];
    printf("%-12s %-16s %s\n", c->name, c->phone, c->email);

    int editChoice;
    printf("You want to edit by\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice : ");
    scanf("%d", &editChoice);
    while ((getchar()) != '\n'); // flush newline

    if (editChoice == 1) {
        printf("Enter the new name : ");
        fgets(c->name, sizeof(c->name), stdin);
        c->name[strcspn(c->name, "\n")] = '\0';
    } else if (editChoice == 2) {
        printf("Enter the new phone number : ");
        fgets(c->phone, sizeof(c->phone), stdin);
        c->phone[strcspn(c->phone, "\n")] = '\0';
    } else if (editChoice == 3) {
        printf("Enter the new email : ");
        fgets(c->email, sizeof(c->email), stdin);
        c->email[strcspn(c->email, "\n")] = '\0';
    } else {
        printf("Invalid choice.\n");
        return;
    }

    printf("Contact updated successfully.\n");
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    if (addressBook->contactCount == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    int searchChoice;
    char keyword[50];
    int foundIndex = -1;

    printf("----------------------------------------------------------------------\n");
    printf("\t\t ENTERED INTO DELETE CONTACT");
    printf("\n----------------------------------------------------------------------\n");
    

    printf("Search by\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    printf("ENTER your choice : ");
    scanf("%d", &searchChoice);
    while ((getchar()) != '\n'); // flush newline

    printf("Enter the ");
    if (searchChoice == 1) printf("name : ");
    else if (searchChoice == 2) printf("phone : ");
    else if (searchChoice == 3) printf("email : ");
    else {
        printf("Invalid choice.\n");
        return;
    }

    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    // Find matching contact
    for (int i = 0; i < addressBook->contactCount; ++i) {
        Contact *c = &addressBook->contacts[i];
        if ((searchChoice == 1 && strcasecmp(c->name, keyword) == 0) ||
            (searchChoice == 2 && strcmp(c->phone, keyword) == 0) ||
            (searchChoice == 3 && strcasecmp(c->email, keyword) == 0)) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Contact not found.\n");
        return;
    }

    // Show contact details
    Contact *c = &addressBook->contacts[foundIndex];
    printf("\n%s\t%s\t%s\n", c->name, c->phone, c->email);

    // Ask for confirmation
    char confirm;
    printf("Do you want to delete this contact ? (y/n): ");
    scanf(" %c", &confirm);  // space before %c to skip any leftover newline

    if (confirm == 'y' || confirm == 'Y') {
        // Shift contacts to delete
        for (int i = foundIndex; i < addressBook->contactCount - 1; ++i) {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("Contact deleted successfully.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
   
}



