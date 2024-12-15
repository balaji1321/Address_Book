#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void listContacts(AddressBook *addressBook) 
{
    //if cotactcount is 0 
    if(addressBook->contactCount==0){
        printf("No Data Found!");  //print data not found
    }
    //list the contact details
    else{
        printf("_____________________________________________________________\n");
        printf("| Name           |     Mobile     |         Email           |\n");
        printf("|----------------|----------------|-------------------------|\n");
        for(int i=0;i<addressBook->contactCount;i++){
            printf("|%-15s |%15s |%-25s|\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);//list the details
        }
        printf("|-----------------------------------------------------------|\n");\
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
   // exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int flag=1;
    printf("Enter Name: ");
    while(flag){
        //read name from the user
        scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
        int i=0;
        //validate name
        while(addressBook->contacts[addressBook->contactCount].name[i]){
            //name is valid print it
            if(isalpha(addressBook->contacts[addressBook->contactCount].name[i])||addressBook->contacts[addressBook->contactCount].name[i]==' '){
                flag=0;
            }
            //if name is not valid enter again
            else{
                printf("Name is Not Valid!\n");
                printf("Enter Valid Name : ");
                flag=1;
                break;
            }
            i++;
        }
    }
    printf("Enter mobile: ");
    flag=1;
    //validate mobile to create
    while(flag){
        int c=0,len=0;
        scanf("%s",addressBook->contacts[addressBook->contactCount].phone);//read new mobile from the user
        for(int i=0;i<10;i++){
            //validate mobile
            if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])){
                c++;
            }
        }
        if(addressBook->contacts[addressBook->contactCount].phone[10]){
            len++;
        }
        //if mobile not valid enter again
        if(c!=10||len!=0){
            printf("Mobile Number is wrong! Enter again\n");
            printf("Enter valid mobile : ");
        }
        //if mobile is valid search mobile is exist or not
        if(c==10&&len==0&&addressBook->contactCount!=0){
            for(int j=0;j<addressBook->contactCount;j++){
                //if mobile is not exist create it
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[addressBook->contactCount].phone)){
                    flag=0;
                }
                //if mobile is exist enter again
                else{
                    printf("Mobile is Exist for %s!\n",addressBook->contacts[j].name);
                    printf("Enter New Mobile Number : ");
                    flag=1;
                    break;
                }
            }
        }
        //valid data is found or not
        if(c==10&&len==0&&addressBook->contactCount==0){
            flag=0;
        }
    }
    flag=1;
    printf("Enter Email : ");
    //validate email to create
    while(flag){
        scanf("%s",addressBook->contacts[addressBook->contactCount].email);//read email from the user
        //validate email is exist or not
        if(strchr(addressBook->contacts[addressBook->contactCount].email,'@')&&strstr(addressBook->contacts[addressBook->contactCount].email,".com")){
            for(int k=0;k<addressBook->contactCount;k++){
                //if email is not exist create new email
                if(strcmp(addressBook->contacts[k].email,addressBook->contacts[addressBook->contactCount].email)){
                    flag=0;
                }
                //if email is exist enter new email
                else{
                    printf("Email is exist for %s!\n",addressBook->contacts[k].name);
                    printf("Enter new Email : ");
                    flag=1;
                    break;
                }
            }
            if(addressBook->contactCount==0){
                flag=0;
            }
        }
        //if email is wrong enter new email
        else{
            printf("Email is wrong! Enter again\n");
            printf("Enter Valid Email : ");
        }
    }
    
    addressBook->contactCount++;//increase addressbook count
    //if you want save your creates enter y
    printf("Do you want to save? y/n\n");
    char ch;
    scanf(" %c",&ch);
    if(ch=='y'){
    saveAndExit(addressBook);
    }
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("Select Menu : \n1.By Name\n2.By mobile\n3.By Mail\n4.Exit\n");//menu for search contact
    int k;//declare choice of menu
    printf("Enter Your Choice : ");
    scanf("%d",&k); //read choice from the user
    switch(k){
        case 1: if(addressBook->contactCount==0){
                    printf("No Data Found to Search!");//check data is found or not
                }
                //condition for search name
                else{
                int flag=0;
                while(flag==0){
                    char srr[20];
                    printf("Enter Name : ");
                    scanf(" %[^\n]",srr);//read name from the user
                    //check name is exist or not
                    for(int i=0;i<addressBook->contactCount;i++){
                        //condition for name check
                        if(!strcmp(addressBook->contacts[i].name,srr)){
                            int c=0;
                            //search multiple names are exist or not
                            for(int j=0;j<addressBook->contactCount;j++){
                                if(!strcmp(addressBook->contacts[j].name,srr)){
                                    c++;
                                }
                            }
                            //if name is single print
                            if(c==1){
                                flag=1;
                                printf("_____________________________________________________________\n");
                                printf("| Name           |   Mobile       |         Email           |\n");
                                printf("|----------------|----------------|-------------------------|\n");
                                printf("|%-15s |%15s |%25s|\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                printf("-------------------------------------------------------------\n");
                                break;
                            }
                            //if multiple names are exist try with mobile
                            else{
                                //check mobile number which contact you want sarch
                                flag=1;
                                printf("Multiple names are Present! Try with Mobile number\n");
                                printf("Enter Mobile number : ");
                                int flag1=1;
                                while(flag1){
                                    char mobile4[11];
                                    scanf(" %[^\n]",mobile4); //read mobile from the user
                                    for(int l=0;l<addressBook->contactCount;l++){
                                        //if mobile is exist print it
                                        if(!strcmp(addressBook->contacts[l].phone,mobile4)){
                                            flag1=0;
                                            printf("_____________________________________________________________\n");
                                            printf("| Name           |   Mobile       |         Email           |\n");
                                            printf("|----------------|----------------|-------------------------|\n");
                                            printf("|%-15s |%15s |%25s|\n",addressBook->contacts[l].name,addressBook->contacts[l].phone,addressBook->contacts[l].email);
                                            printf("-------------------------------------------------------------\n");
                                            break;
                                        }
                                    }
                                    //if mobile is not found enter again
                                    if(flag1==1){
                                        printf("Mobile Not Found!\n");
                                        printf("Enter valid Mobile : ");
                                    }
                                }
                                break;
                            }
                        }
                    }
                    //if name is not found enter valid name
                    if(flag==0){
                        printf("Name not found! Try Again\n");
                    }
                }
                }
                break;
        case 2: if(addressBook->contactCount==0){
                    printf("No Data Found to Search!");//check data is found or not
                }
                //condition for search mobile
                else{
                int flag=0;
                while(flag==0){
                    printf("Enter phone : ");
                    char phone1[20];
                    scanf("%s",phone1);//read mobile from the user
                    for(int i=0;i<addressBook->contactCount;i++){
                        //if mobile is found print it
                        if(!strcmp(addressBook->contacts[i].phone,phone1)){
                            flag=1;
                            printf("_____________________________________________________________\n");
                            printf("| Name           |   Mobile       |         Email           |\n");
                            printf("|----------------|----------------|-------------------------|\n");
                            printf("|%-15s |%15s |%25s|\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            printf("-------------------------------------------------------------\n");
                            break;
                        }
                    }
                    //if mobile is not found enter again
                    if(flag==0){
                        printf("Phone not found! Try Again\n");
                    }
                }
                }
                break;
        case 3: if(addressBook->contactCount==0){
                    printf("No Data Found to Search!");//check data is found or not
                }
                //codition for search email
                else{
                int flag=0;
                while(flag==0){
                    printf("Enter Email : ");
                    char email1[20];
                    scanf("%s",email1);//read email from the user
                    //check for email
                    for(int i=0;i<addressBook->contactCount;i++){
                        //if email is found print the contact
                        if(!strcmp(addressBook->contacts[i].email,email1)){
                            flag=1;
                            printf("_____________________________________________________________\n");
                            printf("| Name           |   Mobile       |         Email           |\n");
                            printf("|----------------|----------------|-------------------------|\n");
                            printf("|%-15s |%15s |%25s|\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            printf("-------------------------------------------------------------\n");
                            break;
                        }
                    }
                    //if email is not found enter again
                    if(flag==0){
                        printf("Email not found! Try Again\n");
                    }
                }
                }
                break;
        case 4 : exit(0); //exit from the contact 
                break;
        default : printf("Invalid input\n");
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf("Edit Contact Menu :\n1.Edit Name\n2.Edit Mobile\n3.Edit Email\n");
    int n;//declare n
    printf("Enter the Option : ");
    scanf("%d",&n);//read input from thr user
    switch(n){
        case 1: if(addressBook->contactCount==0){
                    printf("No Data Found to Search!");//check data is found or not
                }
                else{
                //check edit number
                int flag=1;
                printf("Enter Name : ");
                while(flag){
                    char name1[100];//intialize string
                    scanf(" %[^\n]",name1);//read input from the user
                    //find name in the list
                    for(int i=0;i<addressBook->contactCount;i++){
                        if(!strcmp(addressBook->contacts[i].name,name1)){
                            int c=0;
                            for(int m=0;m<addressBook->contactCount;m++){
                                //count how many times name is present
                                if(!strcmp(addressBook->contacts[m].name,name1)){
                                    c++;
                                }
                            }
                            //if it is found enter new name to edit when name count is 1
                            if(c==1){
                                flag=0;
                                printf("Enter New Name : ");
                                int flag2=1;
                                while(flag2){
                                    char name2[100];
                                    scanf(" %[^\n]",name2);//read new name from the user
                                    int r=0,flag3=0;
                                    while(name2[r]){
                                        if(isalpha(name2[r])||name2[r]==' '){
                                            flag3=1;
                                        }
                                        else{
                                            flag3=0;
                                            break;
                                        }
                                        r++;
                                    }
                                    //if name is valid copy new name to list 
                                    if(flag3==1){
                                        flag2=0;
                                        strcpy(addressBook->contacts[i].name,name2);
                                    }
                                    //otherwise name not valid try again with another name
                                    else{
                                        flag2=1;
                                        printf("Name is Not Valid\n");
                                        printf("Enter Valid Name : ");
                                    }
                                }
                                break;
                            }
                            //if multipe names are exist try with mobile number
                            else{
                                printf("Multiple Names are Exist! Try with Mobile Numner\n");
                                printf("Enter Mobile Number: ");
                                int flag1=1;
                                while(flag1){
                                    char mobile5[11];
                                    scanf(" %[^\n]",mobile5);//read mobile number from the user
                                    //search for that mobile number
                                    for(int o=0;o<addressBook->contactCount;o++){
                                        //condition check for mobile number
                                        if(!strcmp(addressBook->contacts[o].phone,mobile5)){
                                            flag1=0;
                                            flag=0;
                                            //if it mobile found enter new name
                                            printf("Enter New Name : ");
                                            int flag2=1;
                                            while(flag2){
                                                char name2[100];
                                                scanf(" %[^\n]",name2);//read new name from the user
                                                int r=0,flag3=0;
                                                //check condition for new name is valid or not
                                                while(name2[r]){
                                                    if(isalpha(name2[r])||name2[r]==' '){
                                                        flag3=1;
                                                    }
                                                    else{
                                                        flag3=0;
                                                        break;
                                                    }
                                                    r++;
                                                }
                                                //if it is valid copy to address book
                                                if(flag3==1){
                                                    flag2=0;
                                                    strcpy(addressBook->contacts[o].name,name2);
                                                }
                                                //otherwise enter valid name
                                                else{
                                                    flag2=1;
                                                    printf("Name is Not Valid\n");
                                                    printf("Enter Valid Name : ");
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    //if mobile not found enter valid mobile number
                                    if(flag1==1){
                                        printf("Mobile Not found!\n");
                                        printf("Enter valid mobile : "); 
                                    }
                                }
                                break;
                            }
                        }
                    }
                    //if name is not found enter new name
                    if(flag==1){
                        printf("Name Not Found! Try again\n");
                        printf("Enter Valid Name : ");
                    }
                }
                }
                break;
        case 2: if(addressBook->contactCount==0){
                    printf("No Data Found to Search!");//check data is found or not if it is not found print no data
                }
                //if data is found enter mobile to search in the list
                else{
                printf("Enter mobile : ");
                int flag=1;
                //contion for edit mobile
                while(flag){
                    char name1[100];
                    scanf(" %[^\n]",name1);//read mobile from the user for search
                    for(int i=0;i<addressBook->contactCount;i++){
                        //search mobile
                        if(!strcmp(addressBook->contacts[i].phone,name1)){
                            flag=0;
                            int flag1=1;
                            //if mobile number is found enter new mobile
                            printf("Enter New Mobile : ");
                            while(flag1){
                                int c=0,len=0;
                                char name2[100];
                                scanf(" %[^\n]",name2);//read new mobile from the user
                                //validate mobile
                                for(int j=0;j<10;j++){
                                    if(isdigit(name2[j])){
                                        c++;
                                    }
                                }
                                if(name2[10]){
                                    len++;
                                }
                                //if mobile not valid enter again
                                if(c!=10||len!=0){
                                    printf("Mobile is not valid! Try again\n");
                                    printf("Enter Valid Mobile Number : ");
                                }
                                //if mobile is valid now find mobile is exist or not
                                if(c==10&&len==0){
                                    int c1=0;
                                    for(int w=0;w<addressBook->contactCount;w++){
                                        if(!strcmp(addressBook->contacts[w].phone,name2))
                                        {
                                            c1++;
                                        }
                                    }
                                    //if new mobile is not exist edit mobile
                                    if(c1==0){
                                        flag1=0;
                                        strcpy(addressBook->contacts[i].phone,name2);
                                    }
                                    //if new mobile is exist enter new mobile
                                    else{
                                        printf("Mobile already Exist!\n");
                                        printf("Enter new Mobile : ");
                                    }
                                }
                            }
                            break;
                        }
                    }
                    //if mobile is not found enter again
                    if(flag==1){
                        printf("Mobile Not Found! Try again\n");
                        printf("Enter Valid Mobile : ");
                    }
                }
                }
                break;
        case 3: if(addressBook->contactCount==0){
                    printf("No Data Found to Search!"); //check data is found or not if it is not found print no data 
                }
                //if data is found enter email to search in the list
                else{
                printf("Enter Email : ");
                int flag=1;
                //contion for edit email
                while(flag){
                    char name1[100];
                    scanf(" %[^\n]",name1);//read email from the user for search
                    for(int i=0;i<addressBook->contactCount;i++){
                        //search email
                        if(!strcmp(addressBook->contacts[i].email,name1)){
                            flag=0;
                            int flag1=1;
                            //if email is found enter new email
                            printf("Enter New Email : ");
                            while(flag1){
                                char name2[100];
                                scanf(" %[^\n]",name2);//read new email from the user
                                //validate email
                                if(strchr(name2,'@')&&strstr(name2,".com")){
                                    int c3=0;
                                    for(int f=0;f<addressBook->contactCount;f++){
                                        if(!strcmp(addressBook->contacts[f].email,name2)){
                                            c3++;
                                        }
                                    }
                                    //if new email is not exist edit email
                                    if(c3==0){
                                        flag1=0;
                                        strcpy(addressBook->contacts[i].email,name2);
                                    }
                                    //if new email is alrady exist enter new email
                                    else{
                                        printf("Email Already Exist!\n");
                                        printf("Enter New Email : ");
                                    }
                                }
                                //if email not valid enter again
                                else{
                                    printf("Email not Valid! Try Again\n");
                                    printf("Enter Valid Email : ");
                                }
                            }
                            break;
                        }
                    }
                    //if email not found enter again
                    if(flag==1){
                        printf("Email Not Found! Try again\n");
                        printf("Enter Valid Email : ");
                    }
                }
                }
                break;
    }
    //do you want to save your edits
    printf("Do you want to save? y/n\n");
    char ch;
    scanf(" %c",&ch);
    if(ch=='y'){
        saveAndExit(addressBook);//function call 
    }
    
}

void deleteContact(AddressBook *addressBook)
{
    printf("1.By Name\n2.By Phone\n3.By Email\n");
    printf("Enter Chioce : ");
    int b;
    scanf("%d",&b);
    switch(b){
        case 1:
                            /* Define the logic for deletecontact */
                            printf("Enter Name : ");
                            int flag=1;
                            //condition for delete contact by name
                            while(flag){
                                char delete_name[100];
                                scanf(" %[^\n]",delete_name); //read name from the user
                                //check name is found or not
                                for(int i=0;i<addressBook->contactCount;i++){
                                    //check condition for multiple names are exist or not
                                    if(!strcmp(addressBook->contacts[i].name,delete_name)){
                                        int c=0;
                                        for(int b=0;b<addressBook->contactCount;b++){
                                            if(!strcmp(addressBook->contacts[b].name,delete_name)){
                                                c++;
                                            }
                                        }
                                        //if single name is exist delete it
                                        if(c==1){
                                            flag=0;
                                            int j=i;
                                            while(j<addressBook->contactCount){
                                                addressBook->contacts[j]=addressBook->contacts[j+1];
                                                j++;
                                            }
                                            addressBook->contactCount--;
                                        }
                                        //if multiple names are exist search with mobile and delete it
                                        else{
                                            printf("Multiple Names are exist! Try with Mobile\n");
                                            printf("Enter mobile : ");
                                            int flag7=1;
                                            while(flag7){
                                                char mobile6[11];
                                                scanf(" %[^\n]",mobile6);//read mobile from the user
                                                for(int s=0;s<addressBook->contactCount;s++){
                                                    //search for the mobile
                                                    if(!strcmp(addressBook->contacts[s].phone,mobile6)){
                                                        flag7=0;
                                                        flag=0;
                                                        int j=s;
                                                        //if mobile is found delete it
                                                        while(j<addressBook->contactCount){
                                                        addressBook->contacts[j]=addressBook->contacts[j+1];
                                                        j++;
                                                        }
                                                        addressBook->contactCount--;
                                                        break;
                                                    }
                                                }
                                                //if mobile is not fond enter again
                                                if(flag7==1){
                                                    printf("Mobile Not Exist!\n");
                                                    printf("Enter Valid Mobile NUmber : ");
                                                }
                                            }
                                        }
                                        break;
                                    }
                                }
                                //if name is not found enter again
                                if(flag==1){
                                    printf("Name not found! Try again\n");
                                    printf("Enter Valid Name : ");
                                }
                            }
                            break;
        case 2: //delete by mobile number
                printf("Enter Mobile Number : ");
                flag=1;
                while(flag){
                    char str[20];
                    scanf(" %s",str);//read mobile number from the user
                    //check enter is in the list or not
                    for(int i=0;i<addressBook->contactCount;i++){
                        //if entered phone is in the list delete it
                        if(!strcmp(addressBook->contacts[i].phone,str)){
                            int j=i;
                            flag=0;
                            while(j<addressBook->contactCount){
                                addressBook->contacts[j]=addressBook->contacts[j+1];
                                j++;
                            }
                            addressBook->contactCount--; //decrese the addresscount
                            break;
                        }
                    }
                    //if entered mobile is not in the list enter again
                    if(flag==1){
                        printf("Invalid Mobile \n");
                        printf("Enter Valid Mobile : ");
                    }
                }
                break;
        case 3: //Delete by email
                printf("Enter Email : ");
                flag=1;
                
                while(flag){
                    char str[20];
                    scanf(" %[^\n]",str);//read email from the user
                    //check entered email is in the list or not
                    for(int i=0;i<addressBook->contactCount;i++){
                        //if email is found delete it
                        if(!strcmp(addressBook->contacts[i].email,str)){
                            flag=0;
                            int j=i;
                            while(j<addressBook->contactCount){
                                addressBook->contacts[j]=addressBook->contacts[j+1];
                                j++;
                            }
                            addressBook->contactCount--;//decrease addresscount
                            break;
                        }
                    }
                    //if email is not found enter again
                    if(flag==1){
                        printf("invalid Email\n");
                        printf("Enter valid Email : ");
                    }
                }
                break;


    }
    //if you want delete enter y otherwise n
    printf("Do you want to Delete? y/n\n");
    char ch;
    scanf(" %c",&ch);
    if(ch=='y'){
    saveAndExit(addressBook); //function call
    }

}
