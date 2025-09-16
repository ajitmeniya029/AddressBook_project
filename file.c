#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL) {
        printf("Error: Could not open file to save contacts.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; ++i) {
        Contact *c = &addressBook->contacts[i];
        fprintf(fp, "%s,%s,%s\n", c->name, c->phone, c->email);
    }

    fclose(fp);
    printf("Contacts saved successfully to '%s'.\n", FILE_NAME);
}
    

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("No saved contacts found. Starting with an empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }

    addressBook->contactCount = 0;
    while (fscanf(fp, " %49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;

        if (addressBook->contactCount >= MAX_CONTACTS)
            break;
    }

    fclose(fp);
    printf("Loaded %d contacts from file '%s'.\n", addressBook->contactCount, FILE_NAME);    
}
