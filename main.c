/*
Name        : Dakshith K S
Project     : AddressBook
Date        : 17/06/2026
Batch       : 26005A
Description : 
            This project is a console-based Address Book Management System developed in C. 
            It allows users to add, view, search, edit, and delete contact details like name, mobile number, and email ID. 
            The system includes input validation to ensure correct and unique data entry. 
            We can multiple contacts at once based on user input. File handling is implemented to save and load contacts to database. 
            This project helps to organize contacts and easy to maintain.

*/


#include <stdio.h>
#include "contact.h"


#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW   "\033[1;33m"
#define BLUE   "\033[1;34m"
#define PURPLE "\033[1;35m"
#define RESET   "\033[0m"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf(YELLOW "\nAddress Book Menu:\n"RESET);
        printf(GREEN "1. Create contact\n"RESET);
        printf(GREEN "2. Search contact\n"RESET);
        printf(GREEN "3. Edit contact\n"RESET);
        printf(GREEN "4. Delete contact\n"RESET);
        printf(GREEN "5. List all contacts\n"RESET);
    	printf(GREEN "6. Save and Exit\n"RESET);		
        // printf("7. Exit\n");
        printf(YELLOW "Enter your choice: "RESET);
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:           
                listContacts(&addressBook);
                break;
            case 6:
                printf(GREEN "Saving and Exiting...\n" RESET);
                saveContactsToFile(&addressBook);
                break;
            default:
                printf(RED "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 6);
    
    return 0;
}
