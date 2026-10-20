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
