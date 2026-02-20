#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

// ----- Input helpers -----
void ClearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double GetDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cout << "Invalid input. Try again.\n";
        ClearInput();
    }
}

double GetNonNegativeDouble(const string& prompt) {
    double value;
    while (true) {
        value = GetDouble(prompt);
        if (value >= 0.0) return value;
        cout << "Please enter 0 or higher.\n";
    }
}

int GetPositiveInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) return value;
        cout << "Invalid input. Enter a whole number > 0.\n";
        ClearInput();
    }
}

// ----- Core logic -----
void PrintReport(double income, double expenses, int months, double annualRatePercent) {
    cout << "\n==============================\n";
    cout << "   Monthly Budget Projection\n";
    cout << "==============================\n";

    cout << fixed << setprecision(2);
    double monthlySavings = income - expenses;

    cout << "Monthly Income:   $" << income << "\n";
    cout << "Monthly Expenses: $" << expenses << "\n";
    cout << "Monthly Savings:  $" << monthlySavings << "\n";
    cout << "Months:           " << months << "\n";
    cout << "Annual Interest:  " << annualRatePercent << "%\n";

    if (monthlySavings <= 0) {
        cout << "\nWarning: You are not saving money monthly, so no growth projection can be made.\n";
        return;
    }

    // Convert annual % to monthly decimal rate
    double monthlyRate = (annualRatePercent / 100.0) / 12.0;

    cout << "\n----- Growth Table (Monthly Compounding) -----\n";
    cout << left << setw(8) << "Month"
        << setw(18) << "Deposit"
        << setw(18) << "Interest"
        << "Balance\n";
    cout << "-------------------------------------------------------------\n";

    double balance = 0.0;

    for (int m = 1; m <= months; ++m) {
        // deposit at start of month
        balance += monthlySavings;

        // interest earned this month
        double interestEarned = balance * monthlyRate;

        // apply interest
        balance += interestEarned;

        cout << left << setw(8) << m
            << "$" << setw(17) << monthlySavings
            << "$" << setw(17) << interestEarned
            << "$" << balance << "\n";
    }

    cout << "\nFinal Balance after " << months << " months: $" << balance << "\n";
}

int main() {
    double income = 0.0;
    double expenses = 0.0;
    double annualRatePercent = 0.0;
    int months = 12;

    bool hasData = false;

    while (true) {
        cout << "\n=== Monthly Budget Growth Planner ===\n";
        cout << "1) Enter/Update budget data\n";
        cout << "2) Print projection report\n";
        cout << "3) Exit\n";
        cout << "Choose an option: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Try again.\n";
            ClearInput();
            continue;
        }

        if (choice == 1) {
            income = GetNonNegativeDouble("Enter monthly income: $");
            expenses = GetNonNegativeDouble("Enter monthly expenses: $");
            months = GetPositiveInt("Enter number of months to project: ");
            annualRatePercent = GetNonNegativeDouble("Enter annual interest rate (example 5 for 5%): ");
            hasData = true;

            cout << "\nSaved!\n";
        }
        else if (choice == 2) {
            if (!hasData) {
                cout << "\nPlease enter data first (option 1).\n";
            }
            else {
                PrintReport(income, expenses, months, annualRatePercent);
            }
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Please choose 1, 2, or 3.\n";
        }
    }

    return 0;
}