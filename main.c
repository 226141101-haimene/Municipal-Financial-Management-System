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
