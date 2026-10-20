#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define TEXT_LEN      50

typedef struct {
    int  id;
    char name[TEXT_LEN];
    char email[TEXT_LEN];
    char phone[TEXT_LEN];
    char town[TEXT_LEN];
} Supplier;

void displaySupplierMenu(void);
int  supplierCount(void);

#endif
suppliers.c
c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

static Supplier suppliers[MAX_SUPPLIERS];
static int      count = 0;


static void readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) { buf[0] = '\0'; return; }
    buf[strcspn(buf, "\n")] = '\0';
}

static int isBlank(const char *s)
{
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

static void readText(const char *prompt, char *buf, int size)
{
    do {
        readLine(prompt, buf, size);
        if (isBlank(buf)) puts("  Field cannot be empty.");
    } while (isBlank(buf));
}

static int readPositiveInt(const char *prompt, int *value)
{
    char buf[TEXT_LEN];
    char *end;
    long v;

    readLine(prompt, buf, sizeof(buf));
    if (isBlank(buf)) return 0;

    v = strtol(buf, &end, 10);
    if (*end != '\0' || v <= 0) return 0;

    *value = (int)v;
    return 1;
}

static int findByID(int id)
{
    for (int i = 0; i < count; i++)
        if (suppliers[i].id == id) return i;
    return -1;
}


static void addSupplier(void)
{
    Supplier s;

    if (count >= MAX_SUPPLIERS) { puts("Supplier list is full."); return; }

    puts("\n--- Add Supplier ---");


    while (1) {
        if (!readPositiveInt("Supplier ID: ", &s.id)) {
            puts("  Enter a positive whole number.");
        } else if (findByID(s.id) != -1) {
            puts("  That ID already exists.");
        } else {
            break;
        }
    }

    readText("Name:  ", s.name,  TEXT_LEN);
    readText("Email: ", s.email, TEXT_LEN);
    readText("Phone: ", s.phone, TEXT_LEN);
    readText("Town:  ", s.town,  TEXT_LEN);

    suppliers[count++] = s;
    puts("Supplier added successfully.");
}

static void printSupplier(const Supplier *s)
{
    printf("ID:    %d\n", s->id);
    printf("Name:  %s\n", s->name);
    printf("Email: %s\n", s->email);
    printf("Phone: %s\n", s->phone);
    printf("Town:  %s\n", s->town);
}

static void displayAllSuppliers(void)
{
    puts("\n--- Supplier List ---");
    if (count == 0) { puts("No suppliers registered."); return; }

    for (int i = 0; i < count; i++) {
        printf("\nSupplier %d of %d\n", i + 1, count);
        printSupplier(&suppliers[i]);
    }
}

static void searchSupplier(void)
{
    char name[TEXT_LEN];
    int  found = 0;

    if (count == 0) { puts("No suppliers registered."); return; }

    readText("Exact supplier name: ", name, sizeof(name));

    for (int i = 0; i < count; i++) {
        if (strcmp(suppliers[i].name, name) == 0) {
            puts("\nFound:");
            printSupplier(&suppliers[i]);
            found = 1;
        }
    }
    if (!found) printf("No supplier named \"%s\".\n", name);
}


static void saveToFile(void)
{
    FILE *fp = fopen("suppliers.txt", "w");
    if (!fp) { perror("Cannot open suppliers.txt"); return; }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%s|%s|%s\n",
                suppliers[i].id, suppliers[i].name, suppliers[i].email,
                suppliers[i].phone, suppliers[i].town);
    }

    fclose(fp);
    printf("Saved %d supplier(s) to suppliers.txt.\n", count);
}

static void loadFromFile(void)
{
    FILE *fp = fopen("suppliers.txt", "r");
    if (!fp) { puts("No saved file found. Starting fresh."); return; }

    int n = 0;
    Supplier s;

    while (n < MAX_SUPPLIERS &&
           fscanf(fp, "%d|%49[^|]|%49[^|]|%49[^|]|%49[^\n]\n",
                  &s.id, s.name, s.email, s.phone, s.town) == 5) {
        suppliers[n++] = s;
    }

    fclose(fp);
    count = n;
    printf("Loaded %d supplier(s) from suppliers.txt.\n", count);
}


int supplierCount(void) { return count; }

void displaySupplierMenu(void)
{
    int choice;

    do {
        puts("\n================================");
        puts("      SUPPLIER MANAGEMENT");
        puts("================================");
        puts("1. Add supplier");
        puts("2. Display all suppliers");
        puts("3. Search by name");
        puts("4. Save to file");
        puts("5. Load from file");
        puts("6. Back to main menu");

        if (!readPositiveInt("Choice: ", &choice) || choice > 6) {
            puts("Invalid menu choice.");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: addSupplier();         break;
            case 2: displayAllSuppliers(); break;
            case 3: searchSupplier();      break;
            case 4: saveToFile();          break;
            case 5: loadFromFile();        break;
            case 6: puts("Returning to main menu."); break;
        }
    } while (choice != 6);
}
