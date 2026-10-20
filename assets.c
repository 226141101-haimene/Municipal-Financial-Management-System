#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assets.h"

static Asset assets[MAX_ASSETS];
static int   count = 0;


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

static int readMoney(const char *prompt, double *value)
{
    char buf[TEXT_LEN];
    char *end;
    double v;

    readLine(prompt, buf, sizeof(buf));
    if (isBlank(buf)) return 0;

    v = strtod(buf, &end);
    if (*end != '\0' || v < 0.0) return 0;

    *value = v;
    return 1;
}

static int findByID(int id)
{
    for (int i = 0; i < count; i++)
        if (assets[i].id == id) return i;
    return -1;
}


static void addAsset(void)
{
    Asset a;

    if (count >= MAX_ASSETS) {
        puts("Asset register is full.");
        return;
    }

    puts("\n--- Add Asset ---");


    while (1) {
        if (!readPositiveInt("Asset ID: ", &a.id)) {
            puts("  Enter a positive whole number.");
        } else if (findByID(a.id) != -1) {
            puts("  That ID already exists.");
        } else {
            break;
        }
    }

    readText("Name:       ", a.name,       TEXT_LEN);
    readText("Type:       ", a.type,       TEXT_LEN);

    while (!readMoney("Value (N$): ", &a.purchaseValue))
        puts("  Enter a value of 0 or more.");

    readText("Department: ", a.department, TEXT_LEN);
    readText("Condition:  ", a.condition,  TEXT_LEN);

    assets[count++] = a;
    puts("Asset added successfully.");
}

static void printAsset(const Asset *a)
{
    printf("ID:         %d\n",   a->id);
    printf("Name:       %s\n",   a->name);
    printf("Type:       %s\n",   a->type);
    printf("Value:      N$%.2f\n", a->purchaseValue);
    printf("Department: %s\n",   a->department);
    printf("Condition:  %s\n",   a->condition);
}

static void displayAssets(void)
{
    puts("\n--- Asset Register ---");
    if (count == 0) { puts("No assets registered."); return; }

    for (int i = 0; i < count; i++) {
        printf("\nAsset %d of %d\n", i + 1, count);
        printAsset(&assets[i]);
    }
}

static void searchAsset(void)
{
    int choice, id, idx;
    char name[TEXT_LEN];
    int found = 0;

    if (count == 0) { puts("No assets registered."); return; }

    puts("\nSearch by:\n1. ID\n2. Exact name");
    if (!readPositiveInt("Choice: ", &choice) || choice > 2) {
        puts("Invalid choice.");
        return;
    }

    if (choice == 1) {
        if (!readPositiveInt("Asset ID: ", &id)) { puts("Invalid ID."); return; }
        idx = findByID(id);
        if (idx < 0) printf("No asset with ID %d.\n", id);
        else         { puts("\nFound:"); printAsset(&assets[idx]); }
    } else {
        readText("Exact name: ", name, sizeof(name));
        for (int i = 0; i < count; i++) {
            if (strcmp(assets[i].name, name) == 0) {
                puts("\nFound:");
                printAsset(&assets[i]);
                found = 1;
            }
        }
        if (!found) printf("No asset named \"%s\".\n", name);
    }
}


int assetCount(void) { return count; }

void displayAssetMenu(void)
{
    int choice;

    do {
        puts("\n================================");
        puts("       ASSET MANAGEMENT");
        puts("================================");
        puts("1. Add asset");
        puts("2. Display all assets");
        puts("3. Search asset");
        puts("4. Back to main menu");

        if (!readPositiveInt("Choice: ", &choice) || choice > 4) {
            puts("Invalid menu choice.");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            case 4: puts("Returning to main menu."); break;
        }
    } while (choice != 4);
}
main.c (driver to test it)
c
#include <stdio.h>
#include "assets.h"

static int readInt(const char *prompt)
{
    char buf[32];
    int v;
    printf("%s", prompt);
    if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%d", &v) == 1)
        return v;
    return -1;
}

int main(void)
{
    int choice;
    do {
        printf("\n=== MUNICIPAL FINANCIAL MANAGEMENT SYSTEM ===\n");
        printf("1. Asset Management\n");
        printf("0. Exit\n");
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: displayAssetMenu(); break;
            case 0: printf("Goodbye.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}
