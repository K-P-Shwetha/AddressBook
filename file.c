#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
	// Function to save contacts to the addressbook
	FILE *f=fopen("contacts.csv","w");
	/*if(f)
		printf("File opened");
	else
		printf("File not opened");*/
	fprintf(f,"#%d\n",addressBook->contactCount);
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(f,"%s,",addressBook->contacts[i].name);
		fprintf(f,"%s,",addressBook->contacts[i].phone);
		fprintf(f,"%s\n",addressBook->contacts[i].email);
	}
}

void loadContactsFromFile(AddressBook *addressBook)
{
    	// Function to load contacts from the addressbook to the program 
    	FILE *fp=fopen("contacts.csv","r");
    	/*if(fp)
		printf("File opened");
	else
		printf("File not opened");*/

    	fscanf(fp,"#%d\n",&addressBook->contactCount);
    	int x=addressBook->contactCount;
    	for(int i=0;i<=x;i++)
    	{
		fscanf(fp,"%[^,],",addressBook->contacts[i].name);
		fscanf(fp,"%[^,],",addressBook->contacts[i].phone);
		fscanf(fp,"%[^\n]\n",addressBook->contacts[i].email);
    	}
}
