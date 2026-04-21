#include <iostream>
using namespace std;
class Customer {
    string name;
    int account_num;
    int balance;
    //here is a constructor that is hidden it is automatically created
    public:
    //default constroctor
    Customer()
    {
      name = "Rohit";
      account_num = 1091;
      balance = 111;

    }
    //parameterized constructor
 Customer(string a,int b,int c)
    {
        name = a;
        account_num = b;
        balance = c;
    }
    Customer(string name,int account_num) //for this case this-> pointer will be used so that it will give output
    {
        this->name = name;
        this->account_num = account_num;
        balance = 50;
    }
    //inline constructor
    inline Customer (string a, int b, int c): name(a),account_num(b),balance(c)
    {
        
    }
    //copy constructor
    Customer(Customer &B)
    {
        name = B.name;
        account_num= B.account_num;
        balance = B.balance;
        
    }
    void display()
    {
        cout<<name<<" "<<account_num<<" "<<balance<<endl;
    }
};
int main() {
       Customer A1;
       Customer A2("pawan" , 18819,19819);
       Customer A3("Anurag", 182);
       A1.display();
       A2.display();
       A3.display();
}