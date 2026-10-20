#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

struct Employee {
    int id;
    char name[50];
    char department[30];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
};

extern struct Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

float calculateNetSalary(struct Employee emp);
void displayEmployeeDetails(struct Employee emp);
void addEmployee();
void displayEmployees();
void searchEmployee();
void employeeMenu();

#endif
