#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr=fopen("data.txt","w");//open file in write mode
    fprintf(fptr,"%d\n",addressBook->contactCount);//write count value to the file
    //write all the details to the file
    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);//close the file
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr=fopen("data.txt","r");//open file in read mode
    //file not found return NULL 
    if(fptr==NULL){
        printf("File not Exist");
    }
    int c;//declaration
    fscanf(fptr,"%d\n",&c);//read count from file 
    addressBook->contactCount=c;//store count in contactcount
    //read all other elements from the file
    for(int i=0;i<addressBook->contactCount;i++){
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);//close the file
}
