#include<stdio.h>
#include<string.h>
#include <stdlib.h>

// structure for storing values in run time or helping variables
typedef struct contacts{
    char name[50];
    char email[50];
    char phone[50];
} cont;

//=== Function prototype or declaration
void addContacts();
void viewContacts();
void searchContacts();
void deleteContacts();


int main(){
    int choice; // taking user choice to perform function accordingly
    printf("\n====== CONTACTS BOOK PROGRAME ======\n");

    // Menu loop will run until user choose 5 or invaild input
    while(1){
        printf("\n<--- Contact Book Menu --->\n");
        printf("1- Add contact\n");
        printf("2- View contacts\n");
        printf("3- Search contact\n");
        printf("4- Delete contact\n");
        printf("5- Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            addContacts(); // caling add contact function
            break;

            case 2:
            viewContacts(); // caling view contact function
            break;

            case 3:
            searchContacts(); // caling search contact function
            break;

            case 4:
            deleteContacts(); // caling delete contact function
            break;

            case 5:
            printf("Exiting succesfully...."); // exit programe
            return 0;

            default:
            printf("Invalid Entry"); 
            return 0;
        }
    }
    return 0;
}

// Function for adding contacts in file
void addContacts(){
    FILE *fp;
    fp = fopen("contacts.txt", "a"); // text file opening in Append mode
    cont c; // object creation
    //taking input from user and storing into structure object
    printf("Enter Name: ");
    scanf("%s", c.name);
    printf("Enter Email: ");
    scanf("%s", c.email);
    printf("Enter Phone Number: ");
    scanf("%s", c.phone);
    // Moving or printing values from structure object into txt file
    fprintf(fp, "%s %s %s\n", c.name, c.email, c.phone);
    fclose(fp);// closing file
    printf("Contact Added Succesfully.\n"); // printing success msg
}
// function to view all the contacts
void viewContacts(){
    FILE *fp;
    fp = fopen("contacts.txt", "r"); // opening file in read mode
    cont c; //object initializing
    int count = 0; // it is helping to count total contacts which have been printed
    // checking whether file exist or not
    if(fp == NULL){
        printf("No contacts exists");
    }
    // printing contacts through loop
    printf("\n<---- Contact List ---->\n");
    while (fscanf(fp, "%s %s %s", c.name, c.email, c.phone ) == 3) { // fscanf means accesing data from file and storing into structure object
    // printing data of object which came from file
    printf("\nContact %d", ++count);
    printf("\nName: %s\n", c.name);
    printf("Email: %s\n", c.email);
    printf("Phone Number: %s\n", c.phone);
    }

    if (count == 0){ // means there is no data came from file or no contacts
        printf("\nNO contact Found !\n");
    }

    fclose(fp);
}
// function to search a contact from contact list through name, email or phone as per user choice
void searchContacts(){
    FILE *fp;
    fp = fopen("contacts.txt", "r"); //opening file in read mode
    // it will check for file existence
    if (fp == NULL) {
        printf("Error while Fetching Contacts or No contacts!\n");
        return;
    }
    cont c; // object initialization
    int found = 0; // helping variable or contact counter
    char searchName[50]; // taking user input name,email,phone
    printf("Enter Name, Email or phone For Search: ");
    scanf("%s", &searchName);
    // searching contact from contact list
    while(fscanf(fp, "%s %s %s", c.name, c.email, c.phone) == 3){ // scaning every data from file
        // matching name or email or phone from file
        if(strcmp(c.name, searchName) == 0 || strcmp(c.email, searchName) == 0 || strcmp(c.phone, searchName) == 0){ 
            printf("\nContact Found!\n");
            printf("Name  : %s\n", c.name);
            printf("Email : %s\n", c.email);
            printf("Phone : %s\n", c.phone);
            found = 1; // when found 
            break;
        }
    }
    // if not found any matching 
    if (!found) {
        printf("Contact not found!\n");
    }
    fclose(fp);
}
// function for deleting contact
void deleteContacts(){
    FILE *fp, *temp;
    fp = fopen("contacts.txt", "r"); // opening file in read mode

    // checking file existence
    if(fp == NULL){
        printf("No contacts found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    int found = 0;
    char confirm[5];
    cont c;
    char searchName[50];

    printf("Enter Name, Email or phone For Search: ");
    scanf("%s", searchName);

    if(strcmp(searchName, "all") == 0 || strcmp(searchName, "All") == 0){
        FILE *dp = fopen("contacts.txt", "w");
        printf("\nAll contacts Deleted..\n");
        found = 0;
        fclose(dp);  
    }

    while(fscanf(fp, "%s %s %s", c.name, c.email, c.phone) == 3){

        if(strcmp(c.name, searchName) == 0 || strcmp(c.email, searchName) == 0 || strcmp(c.phone, searchName) == 0){

            printf("\nContact Found!\n");
            printf("Name  : %s\n", c.name);
            printf("Email : %s\n", c.email);
            printf("Phone : %s\n", c.phone);

            found = 1;

            printf("Are You sure want to delete this Contact (yes/no): ");
            scanf("%s", confirm);

            if(strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0){
                printf("Contact Deleted successfully..\n");
                continue; 
            } 
            else{
                fprintf(temp, "%s %s %s\n", c.name, c.email, c.phone);
            }

        } 
        else{
            fprintf(temp, "%s %s %s\n", c.name, c.email, c.phone);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if(!found){
        printf("Contact not found!\n");
    }
}