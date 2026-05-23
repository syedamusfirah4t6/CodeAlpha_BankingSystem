#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// ===== ACCOUNT CLASS =====
class Account {
private:
    string ownerName;
    int accountNumber;
    float balance;

public:
    // Constructor
    Account(string name, int accNo, float bal) {
        ownerName = name;
        accountNumber = accNo;
        balance = bal;
    }

    // ===== DEPOSIT =====
    void deposit(float amount) {
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        balance += amount;
        cout << "Deposited: " << amount << endl;
        saveTransaction("Deposit", amount);
    }

    // ===== WITHDRAW =====
    void withdraw(float amount) {
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << endl;
        saveTransaction("Withdrawal", amount);
    }

    // ===== FUND TRANSFER =====
    void transfer(Account& receiver, float amount) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer!" << endl;
            return;
        }
        balance -= amount;
        receiver.balance += amount;
        cout << "Transferred " << amount << " to "
            << receiver.ownerName << endl;
        saveTransaction("Transfer", amount);
    }

    // ===== BALANCE ENQUIRY =====
    void displayInfo() {
        cout << "\n===== ACCOUNT INFO =====" << endl;
        cout << "Name:    " << ownerName << endl;
        cout << "Acc No:  " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }

    // ===== SAVE TRANSACTION TO FILE =====
    void saveTransaction(string type, float amount) {
        ofstream file("transactions.txt", ios::app);
        file << "Account: " << accountNumber
            << " | " << type
            << " | Amount: " << amount
            << " | Balance: " << balance << endl;
        file.close();
    }

    // ===== VIEW TRANSACTIONS =====
    void viewTransactions() {
        cout << "\n===== TRANSACTION HISTORY =====" << endl;
        ifstream file("transactions.txt");
        string line;
        bool found = false;
        string accStr = to_string(accountNumber);

        while (getline(file, line)) {
            if (line.find(accStr) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }
        if (!found) cout << "No transactions found!" << endl;
        file.close();
    }
};

// ===== MAIN MENU =====
int main() {
    // Create two accounts
    Account acc1("Musfirah", 1001, 5000);
    Account acc2("Ali", 1002, 3000);

    int choice;
    float amount;

    do {
        cout << "\n===== BANKING SYSTEM =====" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Fund Transfer" << endl;
        cout << "4. Balance Enquiry" << endl;
        cout << "5. Transaction History" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter deposit amount: ";
            cin >> amount;
            acc1.deposit(amount);
            break;
        case 2:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            acc1.withdraw(amount);
            break;
        case 3:
            cout << "Enter transfer amount: ";
            cin >> amount;
            acc1.transfer(acc2, amount);
            break;
        case 4:
            acc1.displayInfo();
            break;
        case 5:
            acc1.viewTransactions();
            break;
        case 6:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}