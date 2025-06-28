#include <iostream>
#include <ctime>
using namespace std;

class Person {
protected:
    string name, number, email;
public:
    Person(string name, string number, string email) {
        this->name = name;
        this->number = number;
        this->email = email;
    }
};

struct Transaction {
    string type;
    int amount;
    string timestamp;
    Transaction* next;

    Transaction(string t, int amt, string time)
        : type(t), amount(amt), timestamp(time), next(nullptr) {
    }
};

class BankAccount : public Person {
private:
    int pin, money;
    Transaction* head;

public:
    BankAccount(string name, string number, string email, int pin, int money)
        : Person(name, number, email), pin(pin), money(money), head(nullptr) {
    }

    ~BankAccount() {
        Transaction* current = head;
        while (current) {
            Transaction* next = current->next;
            delete current;
            current = next;
        }
    }

    int getPin() {
        return pin;
    }

    void addTransaction(string type, int amount) {
        time_t now = time(0);
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &now);
        string dt(timeStr);
        dt.erase(dt.find_last_not_of("\n") + 1);
        Transaction* newTrans = new Transaction(type, amount, dt);
        newTrans->next = head;
        head = newTrans;
    }

    void deposit(int amount) {
        if (amount > 0) {
            money += amount;
            addTransaction("Deposit", amount);
            cout << "Deposit successful.\n";
        }
        else {
            cout << "Invalid amount.\n";
        }
    }

    void withdraw(int amount) {
        if (amount > 0 && amount <= money) {
            money -= amount;
            addTransaction("Withdraw", amount);
            cout << "Withdrawal successful.\n";
        }
        else if (amount <= 0) {
            cout << "Invalid amount.\n";
        }
        else {
            cout << "Insufficient funds.\n";
        }
    }

    void showAccountInfo() {
        cout << "\n--- Account Info ---\n";
        cout << "Name: " << name << endl;
        cout << "Number: " << number << endl;
        cout << "Email: " << email << endl;
        cout << "Balance: $" << money << endl;
    }

    void showTransactionHistory() {
        if (!head) {
            cout << "No transactions yet.\n";
            return;
        }

        cout << "\n--- Transaction History ---\n";
        Transaction* current = head;
        while (current) {
            cout << "[" << current->timestamp << "] "
                << current->type << ": $" << current->amount << endl;
            current = current->next;
        }
    }
};

int main() {
    BankAccount account("Tom", "031234", "tom@email.com", 1234, 1000);
    int enteredPin, option;

    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (enteredPin == account.getPin()) {
        do {
            cout << "\nSelect Option:\n";
            cout << "1. Account Info\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Transaction History\n";
            cout << "5. Exit\n";
            cout << "Your choice: ";
            cin >> option;

            switch (option) {
            case 1:
                account.showAccountInfo();
                break;
            case 2: {
                int amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                account.deposit(amount);
                break;
            }
            case 3: {
                int amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account.withdraw(amount);
                break;
            }
            case 4:
                account.showTransactionHistory();
                break;
            case 5:
                cout << "Thank you! Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
                break;
            }
        } while (option != 5);
    }
    else {
        cout << "Incorrect PIN.\n";
    }

    return 0;
}