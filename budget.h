#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 50
#define NAME_LEN 50

typedef struct
{
    char department[NAME_LEN];
    double allocatedBudget;
    double expenditure;
} Department;

double getPositiveDouble(const char *message);
void getDepartmentName(char name[], int size);

int findDepartment(Department budgets[], int count,
                   const char name[]);

int addDepartmentBudget(Department budgets[], int count);

void enterExpenditure(Department budgets[], int count);
void calculateRemainingBudget(Department budgets[], int count);
void displayAllBudgets(Department budgets[], int count);
void displayExceededBudgets(Department budgets[], int count);

void budgetMenu(void);

