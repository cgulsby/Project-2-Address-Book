#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

// Keana & Chris
Status load_file(AddressBook *address_book)
{
	address_book->fp = fopen(DEFAULT_FILE, "r+");		// If file exists, opens in read/write mode with the file pointer at the beginning of the file

	if(address_book->fp == NULL) {
		address_book->fp = fopen(DEFAULT_FILE, "w+");	// Creates new, empty file for reading/writing if it didn't previously exist
		address_book->count = 0;
		address_book->list = NULL;
		fclose(address_book->fp);
		address_book->fp = NULL;

		return e_success;
	}

	// Check if the file is empty (exists but has no data)
	fseek(address_book->fp, 0, SEEK_END);
	if(ftell(address_book->fp) == 0) {
		address_book->count = 0;
		address_book->list = NULL;
		fclose(address_book->fp);
		address_book->fp = NULL;

		return e_success;
	}
	rewind(address_book->fp);

	// Data has previously existed, must be loaded into current address book
	// Assuming first line of the csv file will have the total number of contacts
	// Assuming csv format = si_no,name,phone1,phone2,phone3,phone4,phone5,email1,email2,email3,email4,email5

	int contactCount;
	if(fscanf(address_book->fp, "%d\n", &contactCount) != 1) {	// Read number of contacts in the file
		fclose(address_book->fp);
		address_book->fp = NULL;
		printf("Could not read contactCount\n");
		return e_fail;
	}
	address_book->count = contactCount;

	// Variables to hold data that's read in from the file
	int si_no;
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

	address_book->list = malloc(sizeof(ContactInfo) * contactCount);

	if(address_book->list == NULL) {
		printf("Not enough space for the array\n");
		fclose(address_book->fp);
		address_book->fp = NULL;
		return e_fail;
	}

	ContactInfo *tempContactPtr = address_book->list;	// contactCount should've been read already, should be pointing at first ContactInfo

	for(int i = 0; i < contactCount; i++) {
		if(fscanf(address_book->fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
		&si_no, name,
		phoneNum1, phoneNum2, phoneNum3, phoneNum4, phoneNum5,
		email1, email2, email3, email4, email5) != 12) {
			fclose(address_book->fp);
			address_book->fp = NULL;
			printf("Could not read values\n");
			return e_fail;
		}

		// Convert " " placeholders back to empty strings
		// Add name
		strcpy(tempContactPtr->name[0], strcmp(name, " ") == 0 ? "" : name);
		// Add phone numbers
		strcpy(tempContactPtr->phone_numbers[0], strcmp(phoneNum1, " ") == 0 ? "" : phoneNum1);
		strcpy(tempContactPtr->phone_numbers[1], strcmp(phoneNum2, " ") == 0 ? "" : phoneNum2);
		strcpy(tempContactPtr->phone_numbers[2], strcmp(phoneNum3, " ") == 0 ? "" : phoneNum3);
		strcpy(tempContactPtr->phone_numbers[3], strcmp(phoneNum4, " ") == 0 ? "" : phoneNum4);
		strcpy(tempContactPtr->phone_numbers[4], strcmp(phoneNum5, " ") == 0 ? "" : phoneNum5);
		// Add emails
		strcpy(tempContactPtr->email_addresses[0], strcmp(email1, " ") == 0 ? "" : email1);
		strcpy(tempContactPtr->email_addresses[1], strcmp(email2, " ") == 0 ? "" : email2);
		strcpy(tempContactPtr->email_addresses[2], strcmp(email3, " ") == 0 ? "" : email3);
		strcpy(tempContactPtr->email_addresses[3], strcmp(email4, " ") == 0 ? "" : email4);
		strcpy(tempContactPtr->email_addresses[4], strcmp(email5, " ") == 0 ? "" : email5);

		tempContactPtr->si_no = si_no;

		tempContactPtr++;
	}

	fclose(address_book->fp);
	address_book->fp = NULL;

	return e_success;
}

// Keana and Chris
Status save_file(AddressBook *address_book)
{
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	fprintf(address_book->fp, "%d\n", address_book->count);	// Prints count of contacts

	for(int i = 0; i < address_book->count; i++) {
		ContactInfo *c = &address_book->list[i];

		// Write empty fields as " " so fscanf can parse them back
		// Should write as "si_no,name,phoneNum1,phoneNum2,phoneNum3,phoneNum4,phoneNum5,email1,email2,email3,email4,email5"
		// Write si_no and name
		fprintf(address_book->fp, "%d,%s,", c->si_no, strlen(c->name[0]) > 0 ? c->name[0] : " ");
		// Write phone numbers
		fprintf(address_book->fp, "%s,%s,%s,%s,%s,",
		strlen(c->phone_numbers[0]) > 0 ? c->phone_numbers[0] : " ",
		strlen(c->phone_numbers[1]) > 0 ? c->phone_numbers[1] : " ",
		strlen(c->phone_numbers[2]) > 0 ? c->phone_numbers[2] : " ",
		strlen(c->phone_numbers[3]) > 0 ? c->phone_numbers[3] : " ",
		strlen(c->phone_numbers[4]) > 0 ? c->phone_numbers[4] : " ");
		//Write email addresses
		fprintf(address_book->fp, "%s,%s,%s,%s,%s\n",
		strlen(c->email_addresses[0]) > 0 ? c->email_addresses[0] : " ",
		strlen(c->email_addresses[1]) > 0 ? c->email_addresses[1] : " ",
		strlen(c->email_addresses[2]) > 0 ? c->email_addresses[2] : " ",
		strlen(c->email_addresses[3]) > 0 ? c->email_addresses[3] : " ",
		strlen(c->email_addresses[4]) > 0 ? c->email_addresses[4] : " ");
	}

	fclose(address_book->fp);
	address_book->fp = NULL;

	return e_success;
}
