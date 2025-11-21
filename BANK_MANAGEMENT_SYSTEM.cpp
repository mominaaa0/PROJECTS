/*
 Bank Management System (console)
 Compile: g++ -std=c++11 bank_system.cpp -o bank
 Run: ./bank
 Note: Plain-text password used here for simplicity — in real apps use hashing.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Account {
    int accNo;
    string name;
    string password;
    double balance;
};

string accFile = "accounts.txt";
string txnFile = "transactions.txt";

vector<Account> loadAccounts() {
    vector<Account> v;
    ifstream fin(accFile);
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Account a;
        string tmp;
        getline(ss, tmp, ','); a.accNo = stoi(tmp);
        getline(ss, a.name, ',');
        getline(ss, a.password, ',');
        getline(ss, tmp, ','); a.balance = stod(tmp);
        v.push_back(a);
    }
    fin.close();
    return v;
}

void saveAccounts(const vector<Account>& v) {
    ofstream fout(accFile, ios::trunc);
    for (auto &a: v) {
        fout << a.accNo << ',' << a.name << ',' << a.password << ',' << a.balance << '\n';
    }
    fout.close();
}

int nextAccNo(const vector<Account>& v) {
    int maxn = 1000;
    for (auto &a : v) if (a.accNo > maxn) maxn = a.accNo;
    return maxn + 1;
}

void logTransaction(int accNo, const string &type, double amount) {
    ofstream fout(txnFile, ios::app);
    time_t t = time(nullptr);
    fout << accNo << ',' << type << ',' << amount << ',' << t << '\n';
    fout.close();
}

void createAccount() {
    vector<Account> v = loadAccounts();
    Account a;
    a.accNo = nextAccNo(v);
    cout << "Enter name: "; getline(cin, a.name);
    cout << "Set password: "; getline(cin, a.password);
    cout << "Initial deposit: "; cin >> a.balance; cin.ignore();
    v.push_back(a);
    saveAccounts(v);
    cout << "Account created. Account No: " << a.accNo << "\n";
    logTransaction(a.accNo, "OPEN", a.balance);
}

Account* findAccount(vector<Account> &v, int accNo) {
    for (auto &a: v) if (a.accNo == accNo) return &a;
    return nullptr;
}

void deposit() {
    vector<Account> v = loadAccounts();
    cout << "Account No: "; int acc; cin >> acc; cin.ignore();
    Account* a = findAccount(v, acc);
    if (!a) { cout << "Not found.\n"; return; }
    cout << "Enter password: "; string pw; getline(cin, pw);
    if (pw != a->password) { cout << "Auth failed.\n"; return; }
    cout << "Amount to deposit: "; double amt; cin >> amt; cin.ignore();
    a->balance += amt;
    saveAccounts(v);
    logTransaction(a->accNo, "DEPOSIT", amt);
    cout << "Deposit successful. New balance: " << a->balance << "\n";
}

void withdraw() {
    vector<Account> v = loadAccounts();
    cout << "Account No: "; int acc; cin >> acc; cin.ignore();
    Account* a = findAccount(v, acc);
    if (!a) { cout << "Not found.\n"; return; }
    cout << "Enter password: "; string pw; getline(cin, pw);
    if (pw != a->password) { cout << "Auth failed.\n"; return; }
    cout << "Amount to withdraw: "; double amt; cin >> amt; cin.ignore();
    if (amt > a->balance) { cout << "Insufficient balance.\n"; return; }
    a->balance -= amt;
    saveAccounts(v);
    logTransaction(a->accNo, "WITHDRAW", amt);
    cout << "Withdraw successful. New balance: " << a->balance << "\n";
}

void checkBalance() {
    vector<Account> v = loadAccounts();
    cout << "Account No: "; int acc; cin >> acc; cin.ignore();
    Account* a = findAccount(v, acc);
    if (!a) { cout << "Not found.\n"; return; }
    cout << "Enter password: "; string pw; getline(cin, pw);
    if (pw != a->password) { cout << "Auth failed.\n"; return; }
    cout << "Balance: " << a->balance << "\n";
}

void showMenu() {
    cout << "---- Bank System ----\n";
    cout << "1. Create account\n2. Deposit\n3. Withdraw\n4. Check balance\n5. Exit\nChoose: ";
}

int main() {
    // ensure files exist
    ofstream f1(accFile, ios::app); f1.close();
    ofstream f2(txnFile, ios::app); f2.close();

    while (true) {
        showMenu();
        int opt; cin >> opt; cin.ignore();
        switch (opt) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: cout << "Goodbye\n"; return 0;
            default: cout << "Invalid option\n";
        }
        cout << "\n";
    }
    return 0;
}
