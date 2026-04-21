#include <iostream>
using namespace std;
class Customer 
{
    string name;
    int account_num,balance;
    static int total_customer;
    static int total_balance;
    public:
    Customer(string name,int account_num,int balance)
    {
        this->name = name;
        this->account_num = account_num;
        this->balance= balance;
        total_customer++;
        total_balance += balance;


    }
    static void accessStatic()
    {
        cout<<" Total no of customer: "<<total_customer<<endl;
        cout<<"Total balance : "<<total_balance<<endl;
    }
    void deposit(int amount)
    {
        if(amount>0)
        {
            balance += amount;
            total_balance += amount;
        }
    }
    void withdrwal(int amount)
    {
        if(amount<=balance && amount>0)
        {
            balance -= amount;
            total_balance -= amount;

        }
    }
    void display()
    {
        cout<<name<<" "<<account_num<<" "<<balance<<" "<<endl<<total_customer<<endl;
    }
};
int Customer :: total_customer=0;
int Customer :: total_balance=0;
//just below is like abstraction 
int main() {
Customer A1("Rohit",152,762);
Customer A2("Anurag",122,272);
Customer A3("Nitin",172,172);
A1.deposit(1000);// ye  function mai chalu to chal jaaye kaam kaise kr rha mujhe ye nhi janna hai
A2.withdrwal(72);
Customer::accessStatic();


}