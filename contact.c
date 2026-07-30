#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

//#include "populate.h"
int a[100]={-1};
void listContacts(AddressBook *addressBook) 
{
   	 // Print the exsisting contacts
  	 int size=addressBook->contactCount;
   
   	// Message to indicate no contacts
  	 if(size==0)
	   	printf("The List is empty");

   	// Display the existing contacts
   	else{
	  	 printf("\t CONTACTS \n");
   	for(int i=0;i<size;i++)
   	{
		printf("%s ",addressBook->contacts[i].name);
		printf("%s ",addressBook->contacts[i].phone);
		printf("%s ",addressBook->contacts[i].email);
		printf("\n");
   	}
   	}
}

void initialize(AddressBook *addressBook) {

    	// Function to intialize count of contacts and load the contact details from addressBook
	addressBook->contactCount = 0;
    	loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {

    	// Function to save the contact details to addressbook and exit
    	saveContactsToFile(addressBook); 
    	exit(EXIT_SUCCESS); 
}

int namevalid(char *n,int *c,AddressBook *p)
{
	// Function to validate name
	int i=0,count=0,l=strlen(n);

	// Looping through the input string to validate on various conditions
	while(n[i]!=0)
	{
		if((n[i]>='A' && n[i]<='Z') || (n[i]>='a' && n[i]<='z'))
			i++;
		else
		{
			printf("Only alphabetic characters are allowed\n");
			return 0;
		}
	}
	/*for(int i=0;i<*c;i++)
	{
	if(!strcmp(p->contacts[i].name,n))
		return 0;
	}*/

	// Return 1 if name is valid
	if(n[i]==0 && i==l && l>3)
		return 1;
	else if(l<=3)
	{
		printf("Length should be greater than 3\n");
		return 0;
	}
}
int phonevalid(char *ph,int *c, AddressBook *p)
{
	// Function to validate phone number
	int i=0,count=0,l=strlen(ph),flag=0;

	// Looping through the input string to validate on various conditions
	while(ph[i]!=0)
	{
		if(ph[0]>='6' && ph[0]<='9'){
			flag=1;
			count++;
			i++;
		}
		else 
		{
			printf("Phone.No should start with numbers 6-9 and only numbers\n");
			return 0;
		}
		if(ph[i]>='0' && ph[i]<='9')
		{
			count++;
			i++;
			}
	}

	// Check if the entered phone number already exsists
	for(int i=0;i<*c;i++)
	{
	if(!strcmp(p->contacts[i].phone,ph))
	{
		printf("Phone number already exsists\n");
		return 0;
	}
	}
	
	// Return 1 if name is valid, else 0
	if(ph[i]==0 && count==10 && flag==1)
		return 1;
	else
	{
		printf("Phone number should have exactly 10 numbers\n");
		return 0;
	}
	
}
int emailvalid(char *em,int *c,AddressBook  *p)
{
	// Function to validate email id
	int i=0,count=0,l=strlen(em),flag=0;

	// Looping through the input string to validate various conditions
	while(em[i]!=0)
	{
		if(em[0]>='0' && em[0]<='9')
		{
			printf("Email cannot start with number\n");
			return 0;
		}
		else if((em[i]>=97 && em[i]<=122) || (em[i]>='0' && em[i]<='9'))
			i++;
		else if(em[i]=='@')
		{
			if(count==0)
			{
				count=1;
				i++;
			}
			else
			{
				printf("@ character is used more than once\n");
				return 0;
			}
		}
		else if(count==1 && em[i]=='.')
		{
			if((em[i-1]>=97 && em[i-1]<=122) || (em[i-1]>='0' && em[i-1]<='9'))
		        {
				if(!strcmp(&em[i],".com") && em[i+4]==0)
				{
					flag=1;
					i=i+4;
				}
				else
				{
					printf("Email should of format xxx@gmail.com\n");
					return 0;
				}
			}
			else 
			{
				printf("Email should include a domain\n");
				return 0;
			}
		}
		else
		{
			printf("Email should be of format xxx@domain.com\n");
			return 0;
		}
	}
	
	// Check if the entered email id already exsists
	for(int i=0;i<*c;i++)
	{
		if(!strcmp(p->contacts[i].email,em))
		{
			printf("Email already exsists\n");
			return 0;
		}
	}

	// Return 1 if email is valid,else 0
	if(flag==1 && em[i]==0)
		return 1;
	else 
	{
		printf("Email should be of format xxx@domain.com\n");
		return 0;
	}

}
void createContact(AddressBook *addressBook)
{
	// Function that adds a contact if details are valid
   	char name[50],phone[20],email[50];
	int num=0,count=0,i=0,size=0;
	size=addressBook->contactCount;
	
	// Enter the details of new contact
	printf("New contact: ");
	scanf("%s %s %s",name,phone,email);

	// Call function to validate input name with upto 3 attempts to retry
	int n=namevalid(name,&size,addressBook);
	while(num<3)
	{
		if(n)
		{
			//printf("Valid name\n");
			count++;
			break;
		}
		else
		{
			printf("Invalid name\n");
			num++;
			if(num!=3)
			{
				printf("Enter name again : ");
				scanf("%s",name);
				n=namevalid(name,&size,addressBook);
			}
		else
			{
				printf("3 attempts done\n");
				printf("Contact not created\n");
				return;
			}
		}
	}
	num=0;

	// Call function to validate input phone number with upto 3 attempts to retry
	int num1=phonevalid(phone,&size,addressBook);
	while(num<3)
	{
		if(num1)
		{
			//printf("Valid phone\n");
			count++;
			break;
		}
		else
		{
			printf("Invalid Phone.No\n");
			num++;
			if(num==3)
			{
				printf("3 attempts done\n");
				printf("Contact not created\n");
				return;
			}
			else
			{
				printf("Enter Phone.No again : ");
				scanf("%s",phone);
				num1=phonevalid(phone,&size,addressBook);
			}
		}
	}
	num=0;
	
	// Call function to validate input email with upto 3 attempts to retry
	int num2=emailvalid(email,&size,addressBook);
	while(num<3)
	{       		
		if(num2)
		{
			//printf("Valid email");
			count++;
			break;
		}
		else
		{
			printf("Invialid email\n");
			num++;
			if(num==3)
			{
				printf("3 attempts done\n");
				printf("Contact not created\n");
				return;
			}
			else
			{
				printf("Enter email again:");
				scanf("%s",email);
				num2=emailvalid(email,&size,addressBook);
			}
		}
	}

	// Add the new contact info to the Contacts list, if all are valid
	if(count==3)
	{
		strcpy(addressBook->contacts[size].name,name);
		strcpy(addressBook->contacts[size].phone,phone);
		strcpy(addressBook->contacts[size].email,email);
		printf("\nContact created sucessfully!");

		// Update the overall contacts count
		addressBook->contactCount+=1; 
		printf("%d",addressBook->contactCount);
	}
	else
		printf("Contact not created\n");
}
int searchContactbyindex(AddressBook *addressBook)
{
 	// Function that finds contacts based on user choice
	// Print menu for choosing method of searching contact
	printf("\t Menu\n1.Search by name\n2.Search by phone\n3.Search by email\n4.Exit\nEnter the Choice: ");
	int option=0,x=0,i=0,flag=0,size=addressBook->contactCount;
	char name[20],phone[20],email[50],ch;
	for(int i=0;i<99;i++)
	{
		a[i]=-1;
	}
	if(scanf("%d",&option)!=1)
	{
		printf("Invalid input format\n");
		while((ch=getchar())!='\n' && ch!=EOF);
		searchContactbyindex(addressBook);
	}
	switch(option)
	{
		// Search contact by input name on its successful validation
		case 1:printf("Enter Name: ");
		       scanf("%s",name);
		       if(namevalid(name,&size,addressBook))
		      {
				for(i=0;i<addressBook->contactCount;i++)
		      		{
					if(!strcmp(addressBook->contacts[i].name,name))
					{
						a[x]=i;
						x++;
					}
		      			}
		       		if(x>0)
		      		 {
		       			for(i=0;i<x;i++)
		       			{
						printf("%d. %s %s %s",i+1,addressBook->contacts[a[i]].name,addressBook->contacts[a[i]].phone,addressBook->contacts[a[i]].email);
						printf("\n");
		      			}
		       			printf("\nSelect a serial number: ");
		       			scanf("%d",&option);
		       			return a[option-1];
		       		}
		       		else if(x==0)
		       		{
			       		printf("Contact not found\n");
			       		return -1;
			       }
		       		else
					return a[x];
			}
		       else
		       {
			       printf("Invalid name\n");
			       searchContactbyindex(addressBook);
		       }
		       break;

		// Search contact by input phone.no on its successful validation 
		case 2:printf("Enter Phone.No:");
			scanf("%s",phone);
		       if(phonevalid(phone,&size,addressBook))
		       	{
				for(i=0;i<addressBook->contactCount;i++)
				{
					if(!strcmp(addressBook->contacts[i].phone,phone))
						return i;
					else
						flag=1;
				}
				if(flag==1)
				{
					printf("Contact not found.\n");
					return -1;
				}
		       }
		       else
		       {
			       printf("Invalid Phone.No\n");
			       searchContactbyindex(addressBook);
		       }
			break;

		// Search contact by input email on its successful validation
		case 3:printf("Enter Email:");
			scanf("%s",email);
		       if(emailvalid(email,&size,addressBook))
			{
				for(i=0;i<addressBook->contactCount;i++)
				{
					if(!strcmp(addressBook->contacts[i].email,email))
						return i;
					else 
						flag=1;
			}
				if(flag==1)
				{
					printf("Contact not found.\n");
					return -1;
				}
			}
		       else
		       {
				printf("Invalid Email\n");
				searchContactbyindex(addressBook);
		       }
			break;
		// Exit the addressbook without saving any changes to contacts list
		case 4: exit(EXIT_SUCCESS);
		default: return -1;
	}


}
int searchContact(AddressBook *addressBook) 
{
    	// Function that searches contact and displays contact details
	// Print menu for choosing method of searching contact 
	printf("\t Menu\n1.Search by name\n2.Search by phone\n3.Search by email\n4.Exit\nEnter the Choice: ");
	int option=0,x=0,i=0,flag=0,size=addressBook->contactCount;
	char name[20],phone[20],email[50],ch;
	for(int i=0;i<99;i++)
	{
		a[i]=-1;
	}
	if(scanf("%d",&option)!=1)
	{
		printf("Invalid input format\n");
		while((ch=getchar())!='\n' && ch!=EOF);
		searchContact(addressBook);
	}
	switch(option)
	{
		// Search contact by input name on its successful validation and display complete contact details
		case 1:printf("Enter Name: ");
		       scanf("%s",name);
		       if(namevalid(name,&size,addressBook))
		       {
		       		for(i=0;i<addressBook->contactCount;i++)
		      		 {
					if(!strcmp(addressBook->contacts[i].name,name))
					{
						a[x]=i;
						x++;
					}
		     		  }
		    		if(x>0)
		      		 {
					 for(i=0;i<x;i++)
					 {
						printf("%d. %s %s %s",i+1,addressBook->contacts[a[i]].name,addressBook->contacts[a[i]].phone,addressBook->contacts[a[i]].email);
						printf("\n");
		      			 }
		     		  printf("\nSelect a serial number: ");
		       		  scanf("%d",&option);
		       		  printf("%s %s %s",addressBook->contacts[a[option-1]].name,addressBook->contacts[a[option-1]].phone,addressBook->contacts[a[option-1]].email);
		       		  return a[option-1];
		       		 }
		       		else if(x==0)
				{
			      		 printf("Contact not found\n");
			     		 return -1;
		       		}
		      		else
			      		return a[x];
		       }
			else
			{
				printf("Invalid Name\n");
				searchContact(addressBook);
			}
		       break;
		
		// Search contact by input phone.no on its valdiation and display complete contact details
		case 2:printf("Enter Phone.no:");
			scanf("%s",phone);
		       if(phonevalid(phone,&size,addressBook))
		       {
				for(i=0;i<addressBook->contactCount;i++)
				{
					if(!strcmp(addressBook->contacts[i].phone,phone))
					{
						printf("%s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); 
						return i;
					}
				else 
					flag=1;
				}
			if(flag==1)
			{
				printf("Contact not found.\n");
				return -1;
			}
		       }
		       else
		       {
				printf("Invalid Phone.No\n");
				searchContact(addressBook);
		       }
			break;

		// Search contact by input email on its validation and display complete contact details
		case 3:printf("Enter Email:");
			scanf("%s",email);
		       if(emailvalid(email,&size,addressBook))
		       {
				for(i=0;i<addressBook->contactCount;i++)
				{
					if(!strcmp(addressBook->contacts[i].email,email))
					{
						printf("%s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); 
						return i;
					}
					else
						flag=1;
				}
				if(flag==1)
				{
					printf("Contact not found.\n");
					return -1;
				}
		       }
		       else
		       {
				printf("Invalid email\n");
				searchContact(addressBook);
		       }
			break;

		// Exit the addressbook without saving any changes to contacts list
		case 4: exit(EXIT_SUCCESS);
		default : printf("Invalid");
	}
}

void editContact(AddressBook *addressBook)
{
    
    	// Function to edit the details of a contact
    	// Collect the contacts location by searching contact 
    	int x=searchContactbyindex(addressBook),choice=0,size=0;
    	size=addressBook->contactCount;
    	if(x==-1){
	    	printf("Invalid operation");
	    	return ;
    	}
    	char name[20],phone[20],email[20],ch;
    
   	 // Print menu to choose the details of a contact to be edited
   	 printf("\t Menu:\n1.Edit name\n2.Edit phone\n3.Edit email\n4.Exit\nEnter the choice: ");
   	 if(scanf("%d",&choice)!=1)
	 {
		printf("Invalid input format\n");
		while((ch=getchar())!='\n' && ch!=EOF);
		editContact(addressBook);
	 }
   	 switch(choice)
    	{
		// Edit the name of the selected contact with input name on its successful validation
		case 1: printf("Enter the new name:");
			scanf("%s",name);
			if(namevalid(name,&size,addressBook))
			{
				strcpy(addressBook->contacts[x].name,name);
				printf("\nContact edited");
			}
			else
				printf("\nContact not edited");
			break;
	
		// Edit the phone.no of the selected contact with input phone.no on its successful validation
		case 2: printf("Enter the new phone.no:");
			scanf("%s",phone);
			if(phonevalid(phone,&size,addressBook))
			{
				strcpy(addressBook->contacts[x].phone,phone);
				printf("\nContact edited");
			}
			else
				printf("\nContact not edited");
			break;

		// Edit the email of the selected contact with input email on its successful validation
		case 3: printf("Enter the new email:");
			scanf("%s",email);
			if(emailvalid(email,&size,addressBook))
			{
				strcpy(addressBook->contacts[x].email,email);
				printf("\nContact edited");
			}
			else
				printf("\nContact not edited");
			break;	

		// Exit the addressbook without saving any changes to contacts list
		case 4: exit(EXIT_SUCCESS);

		// Default message 
		default : printf("\nInvalid");;
    }
}

void deleteContact(AddressBook *addressBook)
{

	// Function to delete the selected contact
   	// Collect the contact location by searching the contact
   	int x=searchContactbyindex(addressBook);
   	if(x==-1)
   	{
		printf("\nInvalid Operation");
	   	return ;
   	}
   
   	// Update the list by shifiting location of other contacts
   	for(int i=x;i<addressBook->contactCount-1;i++)
   	{
		strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
		strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
		strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
  	}

   	// Update the total contacts count
   	addressBook->contactCount=addressBook->contactCount-1;
   	printf("\nContact deleted sucessfully");
}
