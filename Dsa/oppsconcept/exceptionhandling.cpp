#include <iostream>
using namespace std;
class Customer
{
    string name;
    int balance,account_number;
    public:
    Customer(string name,int balance,int account_number)
    {
        this->name=name;
        this->balance= balance;
        this->account_number = account_number;
    };
    //deposit
    void deposit(int amount)
    {
        if(amount>0)
        {
            balance += amount;
             cout<<amount<<" "<<"is credited succesfully\n"; 
        }
        else 
        {
            throw "amount should be greater that 0\n";
        }
    }
    //withdrwal
    void withdraw(int amount)
    {
        if (amount>0 && amount<=balance)
        {
            balance -=amount;
            cout<<amount<<"is debited successfully";
        }
        else if(amount<0)
        {
            throw "amount should be greater than 0";
        }
        else 
        {
            throw "your balance is low";
        }
    }
};

int main()
{
    Customer C1("Rohit",5000,10);
    try{
    C1.deposit(100);
    C1.withdraw(2090090);
    C1.deposit(123382); //ye nah chlega 
    } catch(const char *e)
    {
        cout<<"Exception occured: "<<e<<endl;
    }
} 