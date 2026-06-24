#include "BankAccount.h"
#include <sstream>
BankAccount::BankAccount() : balance(0) {}
BankAccount::BankAccount(std::string a, std::string p, std::string n, double b) : accountNumber(a), pin(p), customerName(n), balance(b) {}
std::string BankAccount::getAccountNumber() const { return accountNumber; }
std::string BankAccount::getPin() const { return pin; }
std::string BankAccount::getCustomerName() const { return customerName; }
double BankAccount::getBalance() const { return balance; }
void BankAccount::deposit(double a)
{
    if (a > 0)
        balance += a;
}
bool BankAccount::withdraw(double a)
{
    if (a > 0 && a <= balance)
    {
        balance -= a;
        return true;
    }
    return false;
}
std::string BankAccount::serialize() const
{
    std::stringstream s;
    s << accountNumber << "," << pin << "," << customerName << "," << balance;
    return s.str();
}
