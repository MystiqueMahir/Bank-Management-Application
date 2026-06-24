#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H
#include <vector>
#include "BankAccount.h"
class BankSystem
{
    std::vector<BankAccount> accounts;
    void loadAccounts();
    void saveAccounts();

public:
    BankSystem();
    void createAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    BankAccount *findAccount(std::string);
};
#endif
