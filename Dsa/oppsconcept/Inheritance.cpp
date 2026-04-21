#include <iostream>
using namespace std;
//acces modifier
class Human
{
    string religion ,color; //prtive sghould be
    protected: 
    string name;
    int age,weight;

};

class Student: protected  Human
{
    private: 
    int roll_no, fees;
    public:
    
  void  fun(string n,int a ,int c)
        {
           name = n;
           age =a;
           weight = c;
        }
    void display()
    {
             cout<<name<<" "<<age<<" "<<weight;

        }

};


int main()
{
   Student A;
   A.fun("Rohit",10,50);
   A.display();
}