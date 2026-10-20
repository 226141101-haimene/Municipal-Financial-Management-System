#include <stdio.h>
#include <string.h>
#include "employees.h"

struct Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

float calculateNetSalary(struct Employee emp) {
    return emp.basicSalary + emp.housingAllowance + emp.transportAllowance; 
}

void displayEmployeeDetails(struct Employee emp) {
    printf("ID: %d | Name: %s | Dept: %s | Basic: N$%.2f | Housing: N$%.2f | Transport: N$%.2f | TOTAL: N$%.2f\n",
           emp.id, emp.name, emp.department, emp.basicSalary, emp.housingAllowance, emp.transportAllowance, calculateNetSalary(emp));
}

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Maximum employees reached!\n");
        return;
    }
    struct Employee emp;
    printf("\n--- Add Employee ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar();

    do {
        printf("Enter Full Name: ");
        fgets(emp.name, 50, stdin);
        emp.name[strcspn(emp.name, "\n")] = 0;
        if (strlen(emp.name) == 0) printf("Name cannot be empty!\n");
    } while (strlen(emp.name) == 0);

    printf("Enter Department: ");
    fgets(emp.department, 30, stdin);
    emp.department[strcspn(emp.department, "\n")] = 0;

    do {
        printf("Basic Salary N$: ");
        scanf("%f", &emp.basicSalary);
        if (emp.basicSalary < 0) printf("Cannot be negative!\n");
    } while (emp.basicSalary < 0);

    do {
        printf("Housing Allowance N$: ");
        scanf("%f", &emp.housingAllowance);
    } while (emp.housingAllowance < 0);

    do {
        printf("Transport Allowance N$: ");
        scanf("%f", &emp.transportAllowance);
    } while (emp.transportAllowance < 0);

    employees[employeeCount] = emp;
    employeeCount++;
    printf("Employee added successfully! Total: %d\n", employeeCount);
}

void displayEmployees() {
    printf("\n--- All Employees (%d) ---\n", employeeCount);
    if (employeeCount == 0) {
        printf("No employees to display.\n");
        return;
    }
    for (int i = 0; i < employeeCount; i++) {
        displayEmployeeDetails(employees[i]);
    }
}

void searchEmployee() {
    char searchName[50];
    printf("Enter Name to search (using strcmp): ");
    getchar();
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].name, searchName) == 0) {
            printf("FOUND: ");
            displayEmployeeDetails(employees[i]);
            return;
        }
    }
    printf("Employee '%s' not found.\n", searchName);
}

void employeeMenu() {
    int choice;
    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by Name\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}
