Individual Contribution Record – Project A
Student Name: [Jamie Hango]
Student Number: [223050261]
Course: PAP521S – Programming in Practice
Project: Project A – Municipal Financial Management System

Assigned Responsibility
Budget Management Module

Functions / Modules Developed
Files Created

budget.h – Header file with the Department struct and function prototypes

budget.c – Implementation of the Budget Management module

Functions Implemented in budget.c

Function	Purpose
budgetMenu()	Displays the Budget Management sub-menu and handles user navigation
addDepartmentBudget()	Prompts the user to add a new department with an allocated budget
enterExpenditure()	Records expenditure against an existing department
calculateRemainingBudget()	Calculates remaining budget and displays WITHIN/OVER status
displayAllBudgets()	Displays all departments in a formatted table
displayExceededBudgets()	Lists departments that have exceeded their allocated budget
getPositiveDouble()	Validates and returns a non-negative numerical input (helper)
getDepartmentName()	Validates and returns a non-empty department name (helper)
findDepartment()	Case-insensitive check for existing departments (helper)
GitHub Contribution
Branch: budget-management

Pull Request: #[PR number] – Add Budget Management module

Commit: [commit hash] – "Add Budget Management module"

Lines of Code: 213 insertions across 2 files

GitHub Username: [your GitHub username]

Testing Performed
Compilation Testing

Compiled with: gcc -std=c99 -Wall -Wextra -c budget.c -o budget.o

Result: Clean compile, no errors or warnings

Manual Functional Testing

Test Case	Expected Result	Actual Result
Add a department with valid budget	Department added successfully	✅ Pass
Add a department with negative budget	Rejected with error message	✅ Pass
Add a department with empty name	Rejected with error message	✅ Pass
Add a duplicate department	Rejected with duplicate message	✅ Pass
Enter expenditure within budget	Recorded, status "WITHIN BUDGET"	✅ Pass
Enter expenditure that exceeds budget	Recorded with warning, status "OVER BUDGET"	✅ Pass
Calculate remaining budget for all departments	Correct calculations displayed	✅ Pass
Display all budgets in table format	All departments shown correctly	✅ Pass
Show departments exceeding budget	Only over-budget departments shown	✅ Pass
Enter invalid menu choice	Handled with error message	✅ Pass
Edge Cases Tested

Negative expenditure values

Zero budget values

Very large expenditure values

More than one department added

Attempting to enter expenditure when no departments exist

Case-insensitive department name matching (e.g. "finance" vs "Finance")

Individual Understanding
I understand the complete Budget Management module, including:

How the Department struct stores department name, allocated budget, and expenditure

How the array of structs holds multiple departments (Department budgets[MAX_DEPARTMENTS])

How case-insensitive string comparison is implemented in findDepartment() using tolower()

How the remaining budget is calculated (allocatedBudget - expenditure)

How over-budget detection works (expenditure > allocatedBudget)

How getPositiveDouble() validates numeric input and rejects negatives

How getDepartmentName() rejects blank or whitespace-only names

Why input validation is critical for financial data

How the module integrates with main.c via the budgetMenu() function

Declaration
I confirm that the work described above is my own individual contribution to the group project. I have not submitted another group member's work as my own.

Signed: [Jamie Hango]
Date: 20 October 2026
