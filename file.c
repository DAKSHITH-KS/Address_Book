#include <stdio.h>
#include "file.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

void saveContactsToFile(AddressBook *addressBook) {
     FILE *fp = fopen("contacts.csv", "w");
    if(fp == NULL)
    {
        perror(RED "file is open "RESET);
        return;
    }
    fprintf(fp , "#%d\n",addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(fp);
    printf(GREEN "Contacts saved successfully\n" RESET);
  
}




void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.csv", "r");
    
    if(fp == NULL)
    {
        addressBook->contactCount = 0;
        return;
    }
    fscanf(fp, "#%d\n", &addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        }
    fclose(fp);
    }
