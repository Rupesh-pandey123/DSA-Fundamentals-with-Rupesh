#include <iostream>
using namespace std;
class Human
{
    public:
    string name;
    void display()
    {
        cout<<"my name is: "<<endl;
    }
};
class Engineer : public virtual Human
{
    public:
    string specialization;
    void work(){
        cout<<"I have specialization in : "<<specialization<<endl;
    }

};
class Youtuber : public virtual Human
{
    public:
    int subscriber;
    void contentcreator(){
        cout<<"I have subscriber: "<<subscriber<<endl;
    }
};

class CodeTeacher :public Youtuber ,public Engineer
{
    public:
    int salary;
    CodeTeacher(string name,string specialization, int subscriber,int salary)
    {
        this->name=name;
        this->specialization=specialization;
        this->subscriber=subscriber;
        this->salary = salary;

    };
    void printSalary()
    {
        cout << "My salary is: " << salary << endl;
    }

    
    void showcase()
    {
        cout<<"My name is: "<<name<<endl;
        work();
        contentcreator();
        printSalary();
    }
};

int main() {
      CodeTeacher A1("Rohit","CSE",4500,565456);
      A1.showcase();
}