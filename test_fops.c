// TEST FILE FOR address_book_fops.c
// Keana De Padua

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"

int main() {
    AddressBook testAddressBook;
    Status test;

    testAddressBook.fp = fopen("test_fops.csv", "r");
	testAddressBook.list = NULL;
	testAddressBook.count = 0;

    /* Load the file from .csv file if any */
	test = load_file(&testAddressBook);

    if(test == e_success) {
        for(int i = 0; i < testAddressBook.count; i++){
            printf("Name: %s\n", testAddressBook.list->name[0]);    // Print name

            // Print phone numbers
            printf("Phone Numbers: ");
            for(int j = 0; j < PHONE_NUMBER_COUNT; j++)
                printf("%s ", testAddressBook.list->phone_numbers[j]);
            printf("\n");

            // Print email address
            printf("Emails: ");
            for(int k = 0; k < EMAIL_ID_COUNT; k++)
                printf("%s ", testAddressBook.list->email_addresses[k]);
            printf("\n");

            testAddressBook.list += sizeof(ContactInfo);
        }
    }

    if(test == e_fail) { printf("Fail :("); }

    return 0;
}