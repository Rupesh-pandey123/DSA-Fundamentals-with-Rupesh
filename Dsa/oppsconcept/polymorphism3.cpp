#include <iostream>  //rumtime Virtual Function polymorphism
using namespace std;

class Animal
{
    public:
     virtual void speak()  //Pure virfuncytion=  virtual void speak() = 0;  //abstract class
    {
        cout<<"huhu\n";
    }
};

class Dog : public Animal
{
    public:
    void speak()
    {
        cout<<"Bark\n";
    }
};

int main()
{
    Animal *p;
    p = new Dog();
    p->speak();
}
//or Dog D1;
// D1.speak();

