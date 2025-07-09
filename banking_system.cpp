#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;

        time_t now = time(0);
        date = ctime(&now);
        date.pop_back();
    }

    void display() {
        cout << type << " of Rs. " << amount << " on " << date << endl;
    }
};


class Account {
private:
    static int nextAccountNumber;
public:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

    Account() {
        accountNumber = ++nextAccountNumber;
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposit successful. New Balance: Rs. " << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance." << endl;
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        cout << "Withdrawal successful. New Balance: Rs. " << balance << endl;
        return true;
    }

    void displayTransactions() {
        cout << "Transaction History for Account " << accountNumber << ":\n";
        for (auto &t : transactions) {
            t.display();
        }
    }

    void displayAccountInfo() {
        cout << "Account Number: " << accountNumber << "\nBalance: Rs. " << balance << endl;
    }
};

int Account::nextAccountNumber = 1000;

class Customer {
public:
    string name;
    int id;
    Account account;

    Customer(string name, int id) : name(name), id(id) {}

    void displayCustomerInfo() {
        cout << "Customer ID: " << id << "\nName: " << name << endl;
        account.displayAccountInfo();
    }
};

class Bank {
private:
    vector<Customer> customers;

public:
    void createCustomer(string name) {
        int id = customers.size() + 1;
        customers.emplace_back(name, id);
        cout << "Customer created with ID: " << id << endl;
    }

    Customer* getCustomer(int id) {
        if (id <= 0 || id > customers.size()) {
            cout << "Invalid Customer ID!" << endl;
            return nullptr;
        }
        return &customers[id - 1];
    }

    void transferFunds(Customer* sender, Customer* receiver, double amount) {
        if (sender->account.withdraw(amount)) {
            receiver->account.deposit(amount);
            cout << "Transferred Rs. " << amount << " from " << sender->name
                 << " to " << receiver->name << "." << endl;
        }
    }
};

int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Customer\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Show Account Info\n6. Show Transactions\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, name);
            bank.createCustomer(name);

        } else if (choice == 2 || choice == 3 || choice == 5 || choice == 6) {
            int id;
            cout << "Enter customer ID: ";
            cin >> id;
            Customer* cust = bank.getCustomer(id);
            if (!cust) continue;

            if (choice == 2) {
                double amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                cust->account.deposit(amt);

            } else if (choice == 3) {
                double amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                cust->account.withdraw(amt);

            } else if (choice == 5) {
                cust->displayCustomerInfo();

            } else if (choice == 6) {
                cust->account.displayTransactions();
            }

        } else if (choice == 4) {
            int senderID, receiverID;
            double amt;
            cout << "Enter sender ID: ";
            cin >> senderID;
            cout << "Enter receiver ID: ";
            cin >> receiverID;
            cout << "Enter amount to transfer: ";
            cin >> amt;

            Customer* sender = bank.getCustomer(senderID);
            Customer* receiver = bank.getCustomer(receiverID);
            if (sender && receiver) {
                bank.transferFunds(sender, receiver, amt);
            }

        } else if (choice == 7) {
            cout << "Exiting... Thank you!" << endl;
            break;

        } else {
            cout << "Invalid option!" << endl;
        }
    }

    return 0;
}
