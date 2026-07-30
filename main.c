/*
	AddressBook application holds the contact details of user that include name, phone.no and email.id. The contact details are validated against certain criteria and stored. 
	The application also allows the features of editing , searching and deleting contacts by means of all contact details and holds the them in a .csv file.
*/
#include <stdio.h>
#include "contact.h"
int main() 
{
    int choice;
    char ch;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        // printf("7. Exit\n");
        printf("Enter your choice: ");

        if(scanf("%d", &choice)!=1)
	{
		printf("Invalid input format\n");
		while((ch=getchar())!='\n' && ch!=EOF);
		main();
	}
        
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
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
