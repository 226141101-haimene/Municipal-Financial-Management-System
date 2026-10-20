#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

static Supplier suppliers[MAX_SUPPLIERS];
static int      count = 0;


static void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
    }
}

static int readInt(const char *prompt) {
    char buf[32];
    int value;
    while (1) {
        printf("%s", prompt);
        readLine(buf, sizeof(buf));
        if (sscanf(buf, "%d", &value) == 1) return value;
        printf("  Invalid number. Try again.\n");
    }
}

static void readNonEmpty(const char *prompt, char *out, int size) {
    while (1) {
        printf("%s", prompt);
        readLine(out, size);
        if (strlen(out) > 0) return;
        printf("  Cannot be empty. Try again.\n");
    }
}


int supplierCount(void) { return count; }

int findSupplierById(int id) {
    for (int i = 0; i < count; i++)
        if (suppliers[i].id == id) return i;
    return -1;
}

void addSupplier(void) {
    if (count >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;

   
    while (1) {
        s.id = readInt("Supplier ID: ");
        if (s.id <= 0) { printf("  ID must be positive.\n"); continue; }
        if (findSupplierById(s.id) != -1) { printf("  ID already exists.\n"); continue; }
        break;
    }

    readNonEmpty("Name:  ", s.name,  NAME_LEN);
    readNonEmpty("Email: ", s.email, EMAIL_LEN);
    readNonEmpty("Phone: ", s.phone, PHONE_LEN);
    readNonEmpty("Town:  ", s.town,  TOWN_LEN);

    suppliers[count++] = s;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(void) {
    if (count == 0) { printf("No suppliers registered.\n"); return; }

    printf("\n%-5s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-25s %-15s %-15s\n",
               suppliers[i].id, suppliers[i].name, suppliers[i].email,
               suppliers[i].phone, suppliers[i].town);
    }
}

void searchSupplier(void) {
    if (count == 0) { printf("No suppliers registered.\n"); return; }

    char keyword[NAME_LEN];
    readNonEmpty("Enter supplier name or ID to search: ", keyword, sizeof(keyword));

    int found = 0;
    int byId = atoi(keyword);

    for (int i = 0; i < count; i++) {
        if ((byId > 0 && suppliers[i].id == byId) ||
            strstr(suppliers[i].name, keyword) != NULL) {
            printf("\nID   : %d\nName : %s\nEmail: %s\nPhone: %s\nTown : %s\n",
                   suppliers[i].id, suppliers[i].name, suppliers[i].email,
                   suppliers[i].phone, suppliers[i].town);
            found = 1;
        }
    }
    if (!found) printf("No matching supplier found.\n");
}


void supplierMenu(void) {
    int choice;
    do {
        printf("\n--- SUPPLIER MANAGEMENT ---\n");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search supplier\n");
        printf("0. Back to main menu\n");
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
