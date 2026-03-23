#include<stdio.h>
#include<string.h>
#include <stdlib.h>
typedef struct contacts{
    char name[50];
    char email[50];
    char phone[50];
} cont;

void addContacts();
void viewContacts();
void searchContacts();
void deleteContacts();

int main(){
    int choice;
    printf("\n====== CONTACTS BOOK PROGRAME ======\n");
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
            addContacts();
            break;

            case 2:
            viewContacts();
            break;

            case 3:
            searchContacts();
            break;

            case 4:
            deleteContacts();
            break;

            case 5:
            printf("Exiting succesfully....");
            return 0;

            default:
            printf("Invalid Entry");
            return 0;
        }
    }
    return 0;
}

void addContacts(){
    FILE *fp;
    fp = fopen("contacts.txt", "a");
    cont c;
    printf("Enter Name: ");
    scanf("%s", c.name);
    printf("Enter Email: ");
    scanf("%s", c.email);
    printf("Enter Phone Number: ");
    scanf("%s", c.phone);
    fprintf(fp, "%s %s %s\n", c.name, c.email, c.phone);
    fclose(fp);
    printf("Contact Added Succesfully.\n");
}
void viewContacts(){
    FILE *fp;
    fp = fopen("contacts.txt", "r");
    cont c;
    int count = 0;
    
    if(fp == NULL){
        printf("No contacts exists Choose 1 to add new..\n");
    }else{
    //fread(&c, sizeof(c), 1, fp
    printf("\n<---- Contact List ---->\n");
    while (fscanf(fp, "%s %s %s", c.name, c.email, c.phone) == 3) {
    printf("\nContact %d", ++count);
    printf("\nName: %s\n", c.name);
    printf("Email: %s\n", c.email);
    printf("Phone Number: %s\n", c.phone);
    }
    if (count == 0){
        printf("\nNO contact Found !\n");
    }
}

    fclose(fp);
}

void searchContacts(){
    FILE *fp;
    fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        printf("Error while Fetching Contacts or No contacts!\n");
        return;
    }
    cont c;
    int found = 0;
    char searchName[50];
    printf("Enter Name, Email or phone For Search: ");
    scanf("%s", &searchName);
    while(fscanf(fp, "%s %s %s", c.name, c.email, c.phone) == 3){
        if(strcmp(c.name, searchName) == 0 || strcmp(c.email, searchName) == 0 || strcmp(c.phone, searchName) == 0){
            printf("\nContact Found!\n");
            printf("Name  : %s\n", c.name);
            printf("Email : %s\n", c.email);
            printf("Phone : %s\n", c.phone);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Contact not found!\n");
    }
    fclose(fp);
}

void deleteContacts(){
    FILE *fp, *temp;
    fp = fopen("contacts.txt", "r");

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

        if(strcmp(c.name, searchName) == 0 || 
           strcmp(c.email, searchName) == 0 || 
           strcmp(c.phone, searchName) == 0){

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