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

    testAddressBook.fp = fopen("address_book.csv", "r");
	testAddressBook.list = NULL;
	testAddressBook.count = 0;

    /* Load the file from .csv file if any */
    if(testAddressBook.fp == NULL) {
        printf("Unable to open file");
        return 0;
    }

    // Test load file
	test = load_file(&testAddressBook);

    if(test == e_success) {
        for(int i = 0; i < testAddressBook.count; i++){
            printf("Name: %s\n", testAddressBook.list[i].name[0]);    // Print name

            // Print phone numbers
            printf("Phone Numbers: ");
            for(int j = 0; j < PHONE_NUMBER_COUNT; j++)
                printf("%s ", testAddressBook.list[i].phone_numbers[j]);
            printf("\n");

            // Print email address
            printf("Emails: ");
            for(int k = 0; k < EMAIL_ID_COUNT; k++)
                printf("%s ", testAddressBook.list[i].email_addresses[k]);
            printf("\n");
        }
    }

    if(test == e_fail) { 
        printf("Failed to load file :("); 
    }

    free(testAddressBook.list);

    return 0;
}