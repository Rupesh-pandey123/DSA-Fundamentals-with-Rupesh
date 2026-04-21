#include <iostream>
using namespace std;
class Customer 
{
    string name;
    int *data;
    public:
    Customer(string name)
    {

      this->name = name;
      cout<<"Constructor is"<<name<<endl;
    }
    //destructor 
    ~Customer()
    {
        cout<<"destructor is"<<name<<endl;
    }
};

int main(){
      Customer A1("Rohit"),A2("PAwan"),A3("Anurag");
}