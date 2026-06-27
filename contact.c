#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"


#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW   "\033[1;33m"
#define BLUE   "\033[1;34m"
#define PURPLE "\033[1;35m"
#define RESET   "\033[0m"



//--------------------list of contacts-----------------------


void listContacts(AddressBook *addressBook) 
{
   // loadContactsFromFile(addressBook);

    if(addressBook->contactCount == 0)
    {
      printf(RED "No Contacts Available\n" RESET);
      return;
    }
    // Sort contacts based on the chosen criteria
    printf("\n--------------------------------------------------------------------------------------\n");
    printf(BLUE "| slno  | Name\t\t\t| phone_no\t| mail_id\t\t\t |\n" RESET);    
    printf("\n-------------------------------------------------------------------------------------- \n");



   for(int i=0; i< addressBook->contactCount - 1 ; i++){
    for(int j=0; j< addressBook->contactCount - 1 -i ; j++){
        if(strcasecmp(addressBook->contacts[j].name , addressBook->contacts[j+1].name) > 0){
            Contact temp;
            temp = addressBook->contacts[j];
            addressBook->contacts[j] = addressBook->contacts[j+1];
            addressBook->contacts[j+1] = temp;
            }
        }
    }

    for(int i=0 ; i< addressBook->contactCount; i++)
    {
    printf(GREEN "| %d \t| %-20s \t| %-11s \t| %-30s |\n" RESET,i+1 , addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

    }
}




//--------------------load contacts from database-----------------------


void initialize(AddressBook *addressBook){
     addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}


//--------------------save contacts to database-----------------------

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}



//--------------------validation of contacts-----------------------


int validate_name(char *name)
{
    for(int i =0 ; name[i] != '\0' ; i++){
        if(!((name[i]>= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] == '.' ) || (name[i] == '_')) )
        {
            return 0; // invalid
        }
    }
    return 1; // valid.
}


int validate_phone(char *phone_no)
{
    int len = strlen(phone_no); 
    if(len != 10){  //checking length
        return 0;
    }
    if(!(phone_no[0] == '6' || phone_no[0] == '7' || phone_no[0] == '8' || phone_no[0] == '9')){
        printf(RED "Phone number should start with 6 , 7 , 8 or 9\n" RESET);
        return 0;
    }
    for(int i = 0; phone_no[i] != '\0'; i++)
    {
        if(!(phone_no[i] >= '0' && phone_no[i] <= '9'))
            return 0; //invalid
    }
    return 1; //valid
}

int validate_mail(char *mail)
{
 int i = 0;
 int at = -1, dot_com = -1;
   
    if (!(mail[0] >= 'a' && mail[0] <= 'z'))
    {
        return 0;
    }
    
    for (i = 1; mail[i] != '\0'; i++)
    {
        if (mail[i] == '@')
        {
            at = i;
            break;
        }
        if (!((mail[i] >= 'a' && mail[i] <= 'z') ||
              (mail[i] >= '0' && mail[i] <= '9')))
        {
            return 0;
        }
    }

    if (at == -1)
    {
        return 0; //not found
    }

    for (i = at + 1; mail[i] != '\0'; i++)
    {
        if (mail[i] == '.' &&
            mail[i + 1] == 'c' &&
            mail[i + 2] == 'o' &&
            mail[i + 3] == 'm' &&
            mail[i + 4] == '\0')
        {
            dot_com = i;
            break;
        }

    if (!(mail[i] >= 'a' && mail[i] <= 'z'))        // b/w @ and .com there should be only alphabets
    {
        return 0;
    }

    }

    if (dot_com == -1){
        return 0;     // not found
    }

   

    if (dot_com == at + 1){ // to check domain name in b/w @ and .com
        return 0;
    }
    return 1;

}



//--------------------duplicates of contacts-----------------------



int duplicate_phone(AddressBook *addressBook,char *phone)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone) == 0)
            return 1; 
    }
    return 0;
}


int duplicate_email(AddressBook *addressBook,char *email)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
            return 1;
    }
    return 0;

}



//--------------------create of contacts-----------------------


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char name[20];
    char mobile[11];
    char mail[30];
    int valid;
    while(1)
    {
        printf(PURPLE "Enter the name : " RESET);
        scanf("%s", name);
        valid = validate_name(name);
        if(valid == 1)
            break;
        printf(RED "Invalid name. Enter again.\n" RESET);
    }
    while(1)
    {
        printf(PURPLE "Enter the phone : " RESET);
        scanf("%s", mobile);
        if(!validate_phone(mobile))
        {
            printf(RED "Invalid phone number. Enter again.\n" RESET);
            continue;
        }
        if(duplicate_phone(addressBook, mobile))
        {
            printf(RED "Phone number already exists.\n" RESET);
            continue;
        }
        break;
    }

    while(1)
    {
        printf(PURPLE "Enter the mail : " RESET);
        scanf("%s", mail);

        if(!validate_mail(mail))
        {
            printf(RED "Invalid mail. Enter again.\n" RESET);
            continue;
        }
        if(duplicate_email(addressBook, mail))
        {
            printf(RED "Email already exists.\n" RESET);
            continue;
        }
        break;
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
    
    addressBook->contactCount++;

    printf(GREEN "Contact Added Successfully\n" RESET);  
}




//--------------------search of contacts-----------------------



void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choose;
    char name[20];
    char mobile[11];
    char mail[30];
    int found = 0;

    printf(YELLOW "Select the method to search contact\n" RESET);
    printf(PURPLE "1. Name\n" RESET);
    printf(PURPLE "2. Phone no\n" RESET);
    printf(PURPLE "3. Mail id\n" RESET);

    printf(YELLOW "Enter your choice : " RESET);
    scanf("%d", &choose);

    switch(choose)
    {
        case 1:
            printf(PURPLE "Enter the name to search : " RESET);
            scanf(" %[^\n]", name);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    printf("\nName  : %s\n" RESET, addressBook->contacts[i].name);
                    printf("Phone : %s\n" RESET, addressBook->contacts[i].phone);
                    printf("Email : %s\n" RESET, addressBook->contacts[i].email);
                    found = 1;

                }
            }
            break;

        case 2:
            printf(PURPLE "Enter the phone number : " RESET);
            scanf("%s", mobile);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, mobile) == 0)
                {
                    printf(BLUE "\nName  : %s\n" RESET, addressBook->contacts[i].name);
                    printf(BLUE "Phone : %s\n" RESET, addressBook->contacts[i].phone);
                    printf(BLUE "Email : %s\n" RESET, addressBook->contacts[i].email);
                    found = 1;
                    break;
                }
            }
            break;

        case 3:
            printf(PURPLE "Enter the mail id : " RESET);
            scanf("%s", mail);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, mail) == 0)
                {
                    printf(BLUE "\nName  : %s\n" RESET, addressBook->contacts[i].name);
                    printf(BLUE "Phone : %s\n" RESET, addressBook->contacts[i].phone);
                    printf(BLUE "Email : %s\n" RESET, addressBook->contacts[i].email);
                    found = 1;
                    break;
                }
            }
            break;

        default:
            printf(RED "Invalid Choice\n" RESET);
            return;
    }
    if(found == 0)
    {
        printf(RED "Contact Not Found\n" RESET);
    }

   

}




//--------------------edit of contacts-----------------------



void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
     int choice, edit_choice, i;
    char name[50], phone[20], email[50];

    listContacts(addressBook);

    printf(YELLOW "\nsearch contact to Edit by\n" RESET);
    printf(PURPLE "1. Name\n" RESET);
    printf(PURPLE "2. Phone Number\n" RESET);
    printf(PURPLE "3. Email\n" RESET);
    printf(YELLOW "Enter the choice\n" RESET);
    scanf("%d", &choice);
    int found = -1;
    switch(choice)
    {
        case 1:
            printf(PURPLE "Enter Name : " RESET);
            scanf("%s", name);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    found = i;
                    break;
                }
            }
            break;

        case 2:
            printf(PURPLE "Enter Phone : " RESET);
            scanf("%s", phone);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    found = i;
                    break;
                }
            }
            break;

        case 3:
            printf(PURPLE "Enter Email : " RESET);
            scanf("%s", email);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    found = i;
                    break;
                }
            }
            break;
    }
    if(found == -1)
    {
        printf(RED "Contact Not Found\n" RESET);
        return;
    }

    printf(YELLOW "\nContact Found\n" RESET);
    printf(GREEN "%s\t%s\t%s\n" RESET,
           addressBook->contacts[found].name,
           addressBook->contacts[found].phone,
           addressBook->contacts[found].email);

    printf(YELLOW "\nEdit\n" RESET);
    printf(PURPLE "1. Name\n" RESET);
    printf(PURPLE "2. Phone\n" RESET);
    printf(PURPLE "3. Email\n" RESET);
    printf(YELLOW "Enter the choice : " RESET);
    scanf("%d", &edit_choice);

    switch(edit_choice)
    {
        case 1:
            printf(PURPLE "Enter New Name : " RESET);
            scanf("%s", addressBook->contacts[found].name);
            break;

        case 2:
            printf(PURPLE "Enter New Phone : " RESET);
            scanf("%s", addressBook->contacts[found].phone);
            break;

        case 3:
            printf(PURPLE "Enter New Email : " RESET);
            scanf("%s", addressBook->contacts[found].email);
            break;
    }

    printf(GREEN "Contact Updated Successfully\n" RESET);
    
    
}




//--------------------delete of contacts-----------------------



void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice, i, found = -1;
    char name[50], phone[20], email[50];

    listContacts(addressBook);

    printf(YELLOW "\nSelect to Delete contact by\n" RESET);
    printf(PURPLE "1. Name\n" RESET);
    printf(PURPLE "2. Phone Number\n" RESET);
    printf(PURPLE "3. Email\n" RESET);
    printf(YELLOW "Enter the choice : \n" RESET);
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf(PURPLE "Enter Name : " RESET);
            scanf("%s", name);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    found = i;
                    break;
                }
            }
            break;

        case 2:
            printf(PURPLE "Enter Phone : " RESET);
            scanf("%s", phone);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    found = i;
                    break;
                }
            }
            break;

        case 3:
            printf(PURPLE "Enter Email : " RESET);
            scanf("%s", email);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    found = i;
                    break;
                }
            }
            break;
    }
    if(found == -1)
    {
        printf(RED "Contact Not Found\n" RESET);
        return;
    }
    for(i = found; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf(RED "Contact Deleted Successfully\n" RESET);
   
}
