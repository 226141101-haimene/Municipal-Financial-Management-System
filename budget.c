#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"

double getPositiveDouble(const char *message)
{
    double value;
    int result;

    do
    {
        printf("%s", message);
        result = scanf("%lf", &value);

        if (result != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n')
            {
           
            }

            value = -1;
        }
        else if (value < 0)
        {
            printf("Amount cannot be negative.\n");
        }

    } while (value < 0);

    while (getchar() != '\n')
    {

    }

    return value;
}


void getDepartmentName(char name[], int size)
{
    int i;
    int valid;

    do
    {
        printf("Enter department name: ");

        if (fgets(name, size, stdin) == NULL)
        {
            name[0] = '\0';
            continue;
        }

        name[strcspn(name, "\n")] = '\0';

    
        valid = 0;

        for (i = 0; name[i] != '\0'; i++)
        {
            if (!isspace((unsigned char)name[i]))
            {
                valid = 1;
                break;
            }
        }

        if (!valid)
        {
            printf("Department name cannot be empty.\n");
        }

    } while (!valid);
}


int findDepartment(Department budgets[], int count, const char name[])
{
    int i;
    int j;
    int same;

    for (i = 0; i < count; i++)
    {
        same = 1;
        j = 0;

        while (budgets[i].department[j] != '\0' &&
               name[j] != '\0')
        {
            if (tolower((unsigned char)budgets[i].department[j]) !=
                tolower((unsigned char)name[j]))
            {
                same = 0;
                break;
            }

            j++;
        }

        if (budgets[i].department[j] != name[j])
        {
            same = 0;
        }

        if (same)
        {
            return i;
        }
    }

    return -1;
}


int addDepartmentBudget(Department budgets[], int count)
{
    char name[NAME_LEN];
    int existing;

    if (count >= MAX_DEPARTMENTS)
    {
        printf("Maximum number of departments reached.\n");
        return count;
    }

    getDepartmentName(name, NAME_LEN);

    existing = findDepartment(budgets, count, name);

    if (existing != -1)
    {
        printf("This department already has a budget.\n");
        return count;
    }

    strncpy(budgets[count].department, name, NAME_LEN - 1);
    budgets[count].department[NAME_LEN - 1] = '\0';

    budgets[count].allocatedBudget =
        getPositiveDouble("Enter allocated budget (N$): ");

    budgets[count].expenditure = 0.0;

    printf("Department budget added successfully.\n");

    return count + 1;
}


void enterExpenditure(Department budgets[], int count)
{
    char name[NAME_LEN];
    int index;
    double amount;

    if (count == 0)
    {
        printf("No departments available. Add a budget first.\n");
        return;
    }

    getDepartmentName(name, NAME_LEN);

    index = findDepartment(budgets, count, name);

    if (index == -1)
    {
        printf("Department not found.\n");
        return;
    }

    amount = getPositiveDouble("Enter expenditure amount (N$): ");

    budgets[index].expenditure += amount;

    printf("Expenditure recorded successfully.\n");

    if (budgets[index].expenditure >
        budgets[index].allocatedBudget)
    {
        printf("Warning: Department has exceeded its budget!\n");
    }
}

void calculateRemainingBudget(Department budgets[], int count)
{
    int i;
    double remaining;

    if (count == 0)
    {
        printf("No budget information available.\n");
        return;
    }

    printf("\n===== REMAINING BUDGET =====\n");

    for (i = 0; i < count; i++)
    {
        remaining = budgets[i].allocatedBudget -
                    budgets[i].expenditure;

        printf("\nDepartment: %s\n", budgets[i].department);
        printf("Allocated budget: N$%.2f\n",
               budgets[i].allocatedBudget);
        printf("Total expenditure: N$%.2f\n",
               budgets[i].expenditure);
        printf("Remaining budget: N$%.2f\n", remaining);

        if (remaining < 0)
        {
            printf("Status: OVER BUDGET\n");
        }
        else
        {
            printf("Status: WITHIN BUDGET\n");
        }
    }
}


void displayAllBudgets(Department budgets[], int count)
{
    int i;
    double remaining;

    if (count == 0)
    {
        printf("No departments registered.\n");
        return;
    }

    printf("\n===== ALL DEPARTMENTAL BUDGETS =====\n");

    printf("%-20s %12s %12s %12s %15s\n",
           "Department",
           "Allocated",
           "Spent",
           "Remaining",
           "Status");

    for (i = 0; i < count; i++)
    {
        remaining = budgets[i].allocatedBudget -
                    budgets[i].expenditure;

        printf("%-20s %12.2f %12.2f %12.2f %15s\n",
               budgets[i].department,
               budgets[i].allocatedBudget,
               budgets[i].expenditure,
               remaining,
               remaining < 0 ? "OVER BUDGET" : "WITHIN BUDGET");
    }
}


void displayExceededBudgets(Department budgets[], int count)
{
    int i;
    int found = 0;
    double excess;

    printf("\n===== DEPARTMENTS OVER BUDGET =====\n");

    for (i = 0; i < count; i++)
    {
        if (budgets[i].expenditure >
            budgets[i].allocatedBudget)
        {
            excess = budgets[i].expenditure -
                     budgets[i].allocatedBudget;

            printf("%s exceeded its budget by N$%.2f\n",
                   budgets[i].department, excess);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No departments have exceeded their budgets.\n");
    }
}


void budgetMenu(void)
{
    Department budgets[MAX_DEPARTMENTS];
    int count = 0;
    int choice;

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Calculate Remaining Budget\n");
        printf("4. Display All Budgets\n");
        printf("5. Show Departments Exceeding Budget\n");
        printf("0. Return to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid menu choice. Try again.\n");

            while (getchar() != '\n')
            {
              
            }

            choice = -1;
            continue;
        }

        while (getchar() != '\n')
        {
        
        }

        switch (choice)
        {
            case 1:
                count = addDepartmentBudget(budgets, count);
                break;

            case 2:
                enterExpenditure(budgets, count);
                break;

            case 3:
                calculateRemainingBudget(budgets, count);
                break;

            case 4:
                displayAllBudgets(budgets, count);
                break;

            case 5:
                displayExceededBudgets(budgets, count);
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Select an option from 0 to 5.\n");
        }

    } while (choice != 0);
}
