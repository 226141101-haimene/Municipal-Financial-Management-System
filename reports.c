#include <stdio.h>
#include <string.h>
#include "reports.h"

#define STATUS_GOOD "Good"
#define CURRENCY_SYMBOL "N$"

typedef struct {
    int totalEmployees;
    double averageSalary;
    double highestSalary;
    double lowestSalary;
    char sampleEmployeeName[50];
} EmployeeStats;

typedef struct {
    double totalAllocated;
    double totalExpenditure;
} BudgetStats;

typedef struct {
    char supplierName[50];
    char location[50];
} SupplierInfo;

typedef struct {
    char assetName[50];
    double assetValue;
    char condition[20];
} AssetInfo;

void printDivider(const char *title) {
    printf("\n--- %s ---\n", title);
}

void displayReports(void) {
    printf("\n========================================\n");
    printf("       REPORTS MODULE - Student 5\n");
    printf("========================================\n");

    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}

void employeeReport(void) {
    printDivider("Employee Report");

    EmployeeStats emp = {
        4, 18500.00, 42000.00, 8500.00, "Josef"
    };

    printf("Total Employees : %d\n", emp.totalEmployees);
    printf("Average Salary  : %s%.2f\n",
           CURRENCY_SYMBOL, emp.averageSalary);
    printf("Highest Salary  : %s%.2f\n",
           CURRENCY_SYMBOL, emp.highestSalary);
    printf("Lowest Salary   : %s%.2f\n",
           CURRENCY_SYMBOL, emp.lowestSalary);

    printf("Sample Employee : %s\n", emp.sampleEmployeeName);

    printf("Name Length     : %zu characters\n",
           strlen(emp.sampleEmployeeName));
}

void budgetReport(void) {
    printDivider("Budget Report");

    BudgetStats budget = {500000.00, 420000.00};

    double remaining =
        budget.totalAllocated - budget.totalExpenditure;

    printf("Total Allocated   : %s%.2f\n",
           CURRENCY_SYMBOL, budget.totalAllocated);
    printf("Total Expenditure : %s%.2f\n",
           CURRENCY_SYMBOL, budget.totalExpenditure);
    printf("Remaining Balance : %s%.2f\n",
           CURRENCY_SYMBOL, remaining);

    if (remaining >= 0) {
        printf("Status            : WITHIN BUDGET\n");
    } else {
        printf("Status            : OVER BUDGET!\n");
    }
}

void supplierReport(void) {
    printDivider("Supplier Report");

    SupplierInfo sup = {"NUST Supplies", "Windhoek"};

    printf("Supplier Name : %s\n", sup.supplierName);
    printf("Location      : %s\n", sup.location);
}

void assetReport(void) {
    printDivider("Asset Report");

    AssetInfo asset = {
        "Mazda Demio - Vehicle",
        75000.00,
        STATUS_GOOD
    };

    printf("Asset Name : %s\n", asset.assetName);
    printf("Value      : %s%.2f\n",
           CURRENCY_SYMBOL, asset.assetValue);

    if (strcmp(asset.condition, STATUS_GOOD) == 0) {
        printf("Condition  : %s (Verified)\n",
               asset.condition);
    } else {
        printf("Condition  : Needs Attention\n");
    }
}
