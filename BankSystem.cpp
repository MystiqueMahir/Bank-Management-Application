#include "BankSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;
static string confirmAcc()
{
    string a, b;
    for (;;)
    {
        cout << "Enter Account Number: ";
        cin >> a;
        cout << "Re-enter Account Number: ";
        cin >> b;
        if (a == b)
            return a;
        cout << "Mismatch\n";
    }
}
static string confirmPin()
{
    string a, b;
    for (;;)
    {
        cout << "Create 6 Digit PIN: ";
        cin >> a;
        cout << "Re-enter PIN: ";
        cin >> b;
        bool ok = a == b && a.size() == 6;
        for (char c : a)
            if (!isdigit(c))
                ok = false;
        if (ok)
            return a;
        cout << "Invalid PIN\n";
    }
}
BankSystem::BankSystem() { loadAccounts(); }
void BankSystem::loadAccounts()
{
    ifstream f("accounts.txt");
    string line;
    while (getline(f, line))
    {
        stringstream ss(line);
        string a, p, n, b;
        getline(ss, a, ',');
        getline(ss, p, ',');
        getline(ss, n, ',');
        getline(ss, b);
        if (!a.empty())
            accounts.push_back(BankAccount(a, p, n, stod(b)));
    }
}
void BankSystem::saveAccounts()
{
    ofstream f("accounts.txt");
    for (auto &a : accounts)
        f << a.serialize() << endl;
}
BankAccount *BankSystem::findAccount(string a)
{
    for (auto &x : accounts)
        if (x.getAccountNumber() == a)
            return &x;
    return nullptr;
}
void BankSystem::createAccount()
{
    string acc = confirmAcc();
    if (findAccount(acc))
    {
        cout << "Exists\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string n1, n2;
    do
    {
        cout << "Enter Name: ";
        getline(cin, n1);
        cout << "Re-enter Name: ";
        getline(cin, n2);
    } while (n1 != n2);
    string pin = confirmPin();
    double b1, b2;
    do
    {
        cout << "Enter Initial Deposit: ";
        cin >> b1;
        cout << "Re-enter Initial Deposit: ";
        cin >> b2;

        while (b1 < 0 || b2 < 0)
        {
            cout << "\n Negative amount not allowed" << endl;

            cout << "Enter Initial Deposit: ";
            cin >> b1;
            cout << "Re-enter Initial Deposit: ";
            cin >> b2;
        }

    } while (b1 != b2);

    accounts.push_back(BankAccount(acc, pin, n1, b1));
    saveAccounts();
    cout << "Created\n";
}
void BankSystem::depositMoney()
{
    string a, p;
    cout << "Enter Account Number: ";
    cin >> a;
    auto x = findAccount(a);
    if (!x)
    {
        cout << "Account Not Found\n";
        return;
    }
    cout << "Enter PIN: ";
    cin >> p;
    if (p != x->getPin())
    {
        cout << "Wrong PIN\n";
        return;
    }

    double amt;
    cout << "Enter Amount: ";
    cin >> amt;

    if (amt <= 0)
    {
        cout << "\n Negative Amount not allowed" << endl;
        depositMoney();
    }
    x->deposit(amt);
    saveAccounts();
}
void BankSystem::withdrawMoney()
{
    string a, p;
    cout << "Account Number: ";
    cin >> a;
    auto x = findAccount(a);
    if (!x)
    {
        cout << "Not Found\n";
        return;
    }
    cout << "PIN: ";
    cin >> p;
    if (p != x->getPin())
    {
        cout << "Wrong PIN\n";
        return;
    }
    double amt;
    cout << "Amount: ";
    cin >> amt;
    if (amt <= 0)
    {
        cout << "\n Negative Amount not allowed" << endl;
        withdrawMoney();
    }
    if (x->withdraw(amt))
    {
        saveAccounts();
        cout << "Success\n";
    }
    else
        cout << "Insufficient\n";
}
void BankSystem::checkBalance()
{
    string a, p;
    cout << "Account Number: ";
    cin >> a;
    auto x = findAccount(a);
    if (!x)
    {
        cout << "Not Found\n";
        return;
    }
    cout << "PIN: ";
    cin >> p;
    if (p != x->getPin())
    {
        cout << "Wrong PIN\n";
        return;
    }
    cout << "Name: " << x->getCustomerName() << "\nBalance: " << x->getBalance() << endl;
}
