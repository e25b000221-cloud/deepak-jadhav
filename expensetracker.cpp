#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Abstract Base Class
class Expense {
protected:
    int id;
    string category;
    double amount;
    string date;

public:
    Expense(int i, string c, double a, string d) {
        id = i;
        category = c;
        amount = a;
        date = d;
    }

    virtual void display() = 0;

    double getAmount() {
        return amount;
    }

    string getCategory() {
        return category;
    }

    int getId() {
        return id;
    }

    virtual ~Expense() {}
};

// Inheritance - Food Expense
class FoodExpense : public Expense {
public:
    FoodExpense(int i, double a, string d)
        : Expense(i, "Food", a, d) {}

    void display() override {
        cout << id << "\tFood\t"
             << amount << "\t" << date << endl;
    }
};

// Inheritance - Travel Expense
class TravelExpense : public Expense {
public:
    TravelExpense(int i, double a, string d)
        : Expense(i, "Travel", a, d) {}

    void display() override {
        cout << id << "\tTravel\t"
             << amount << "\t" << date << endl;
    }
};

// General Expense
class OtherExpense : public Expense {
public:
    OtherExpense(int i, string c, double a, string d)
        : Expense(i, c, a, d) {}

    void display() override {
        cout << id << "\t" << category
             << "\t" << amount << "\t" << date << endl;
    }
};

// Expense Tracker Class
class ExpenseTracker {

private:
    vector<Expense*> expenses;
    int nextId = 1;

public:

    // Add Expense
    void addExpense() {

        int choice;
        double amount;
        string date;

        cout << "\n1. Food";
        cout << "\n2. Travel";
        cout << "\n3. Other";
        cout << "\nSelect Category: ";
        cin >> choice;

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }

        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> date;

        if (choice == 1) {
            expenses.push_back(
                new FoodExpense(nextId++, amount, date));
        }

        else if (choice == 2) {
            expenses.push_back(
                new TravelExpense(nextId++, amount, date));
        }

        else if (choice == 3) {
            string category;

            cout << "Enter Category: ";
            cin >> category;

            expenses.push_back(
                new OtherExpense(nextId++, category, amount, date));
        }

        else {
            cout << "Invalid Choice!\n";
            return;
        }

        cout << "Expense Added Successfully!\n";
    }

    // Display Expenses
    void viewExpenses() {

        if (expenses.empty()) {
            cout << "\nNo Expenses Found!\n";
            return;
        }

        cout << "\nID\tCategory\tAmount\tDate\n";
        cout << "--------------------------------------\n";

        for (Expense* e : expenses) {
            e->display();
        }
    }

    // Calculate Total Expenses
    void totalExpenses() {

        double total = 0;

        for (Expense* e : expenses) {
            total += e->getAmount();
        }

        cout << "\nTotal Expenses: Rs. "
             << fixed << setprecision(2) << total << endl;
    }

    // Search Expense
    void searchExpense() {

        string searchCategory;
        bool found = false;

        cout << "\nEnter Category to Search: ";
        cin >> searchCategory;

        for (Expense* e : expenses) {

            if (e->getCategory() == searchCategory) {
                e->display();
                found = true;
            }
        }

        if (!found) {
            cout << "No Expense Found!\n";
        }
    }

    // Delete Expense
    void deleteExpense() {

        int id;

        cout << "\nEnter Expense ID to Delete: ";
        cin >> id;

        for (int i = 0; i < expenses.size(); i++) {

            if (expenses[i]->getId() == id) {

                delete expenses[i];

                expenses.erase(expenses.begin() + i);

                cout << "Expense Deleted Successfully!\n";
                return;
            }
        }

        cout << "Expense Not Found!\n";
    }

    // Destructor
    ~ExpenseTracker() {

        for (Expense* e : expenses) {
            delete e;
        }
    }
};

// Main Function
int main() {

    ExpenseTracker tracker;
    int choice;

    do {

        cout << "\n========== EXPENSE TRACKER ==========\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Total Expenses\n";
        cout << "4. Search Expense\n";
        cout << "5. Delete Expense\n";
        cout << "6. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                tracker.addExpense();
                break;

            case 2:
                tracker.viewExpenses();
                break;

            case 3:
                tracker.totalExpenses();
                break;

            case 4:
                tracker.searchExpense();
                break;

            case 5:
                tracker.deleteExpense();
                break;

            case 6:
                cout << "Thank You for Using Expense Tracker!\n";
                break;

            default:
                cout << "Invalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}
