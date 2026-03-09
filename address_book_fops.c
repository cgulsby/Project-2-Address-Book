#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	address_book->fp = fopen(DEFAULT_FILE, "r+");		// If file exists, opens in read/write mode with the file pointer at the beginning of the file
	
	if(address_book->fp == NULL) {
		address_book->fp = fopen(DEFAULT_FILE, "w+");	// Creates new, empty file for reading/writing if it didn't previously exist
	}

	// Data has previously existed, must be loaded into current address book
	// Assuming csv format = name,phoneNumber,emailAddress,si_no

	FILE *tempFP = address_book->fp;

	char checkEmpty = fgetc(tempFP);
	if(checkEmpty != EOF) {								// File isn't empty
		fseek(tempFP, 0, SEEK_SET);						// Makes sure pointer is at beginning of file

		// Variables to hold data that's read in from the file
		char name[NAME_LEN];
		char phoneNum1[NUMBER_LEN];
		char phoneNum2[NUMBER_LEN];
		char phoneNum3[NUMBER_LEN];
		char phoneNum4[NUMBER_LEN];
		char phoneNum5[NUMBER_LEN];
		char email1[EMAIL_ID_LEN];
		char email2[EMAIL_ID_LEN];
		char email3[EMAIL_ID_LEN];
		char email4[EMAIL_ID_LEN];
		char email5[EMAIL_ID_LEN];

		int tempCount = 0;	// Counts the number of Contacts read in
		ContactInfo *tempContactPtr = address_book->list;
		fseek(tempContactPtr, 0, SEEK_SET);	// Set to beginning of list..?

		while (fscanf(tempFP, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", 
		name, 
		phoneNum1, phoneNum2, phoneNum3, phoneNum4, phoneNum5, 
		email1, email2, email3, email4, email5) == 11) {

			// Add name
			strcpy(tempContactPtr->name, name);
			// Add phone numbers
			strcpy(tempContactPtr->phone_numbers[0], phoneNum1);
			strcpy(tempContactPtr->phone_numbers[1], phoneNum2);
			strcpy(tempContactPtr->phone_numbers[2], phoneNum3);
			strcpy(tempContactPtr->phone_numbers[3], phoneNum4);
			strcpy(tempContactPtr->phone_numbers[4], phoneNum5);
			// Add emails
			strcpy(tempContactPtr->email_addresses[0], email1);
			strcpy(tempContactPtr->email_addresses[1], email2);
			strcpy(tempContactPtr->email_addresses[2], email3);
			strcpy(tempContactPtr->email_addresses[3], email4);
			strcpy(tempContactPtr->email_addresses[4], email5);

			tempCount++;

			tempContactPtr->si_no = tempCount;

			tempContactPtr += sizeof(ContactInfo);
    	}

		address_book->count = tempCount;
	}


	return e_success;
}





Status save_file(AddressBook *address_book)
{
    FILE *fp = fopen(DEFAULT_FILE, "w");
    if (fp == NULL)
        return e_fail;

    for (int i = 0; i < address_book->count; i++)
    {
        ContactInfo *c = &address_book->list[i];
        fprintf(fp, "%d,%s,%s,%s\n",
                c->si_no,
                c->name,
                c->phone_numbers,
                c->email_addresses);
    }

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	FILE *tempFP = address_book->fp;
	fseek(tempFP, 0, SEEK_SET);	// Set pointer to beginning of file
	
	for(int i = 0; i < address_book->count; i++) {

		// Should write as "name,phoneNum1,phoneNum2,phoneNum3,phoneNum4,phoneNum5,email1,email2,email3,email4,email5"
		// Write name
		fprintf(tempFP, "%s,", address_book->list->name[0]);
		// Write phone numbers
		fprintf(tempFP, "%s,%s,%s,%s,%s,", address_book->list->phone_numbers[0], address_book->list->phone_numbers[1],
		address_book->list->phone_numbers[2], address_book->list->phone_numbers[3], address_book->list->phone_numbers[4]);
		//Write email addresses
		fprintf(tempFP, "%s%s,%s,%s,%s,%s\n", address_book->list->email_addresses[0], address_book->list->email_addresses[1],
		address_book->list->email_addresses[2], address_book->list->email_addresses[3], address_book->list->email_addresses[4]);

		tempFP += sizeof(ContactInfo);	// Increments pointer to next Contact
	}

	fclose(address_book->fp);

	return e_success;
}
