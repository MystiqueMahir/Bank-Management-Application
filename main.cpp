#include <iostream>
#include "BankSystem.h"
using namespace std;
int main()
{
    cout << "*=*=*=*=*=**=*=* Welcome! *=*=*=*=*=**=*=*" << endl;
    BankSystem bank;
    int c;
    do
    {
        cout << "\n1. Create a new Account\n2. Deposit Amount \n3. Withdraw Amount";
        cout << "\n4. Balance\n5. Exit Application \nEnter Choice here :  ";
        cin >> c;
        switch (c)
        {
        case 1:
            bank.createAccount();
            break;
        case 2:
            bank.depositMoney();
            break;
        case 3:
            bank.withdrawMoney();
            break;
        case 4:
            bank.checkBalance();
            break;
        }
    } while (c != 5);
}
