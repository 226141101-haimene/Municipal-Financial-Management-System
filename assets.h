#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define NAME_LEN      50
#define EMAIL_LEN     60
#define PHONE_LEN     20
#define TOWN_LEN      40

typedef struct {
    int  id;
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    char town[TOWN_LEN];
} Supplier;

/* Function declarations */
void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
int  findSupplierById(int id);
int  supplierCount(void);

#endif
