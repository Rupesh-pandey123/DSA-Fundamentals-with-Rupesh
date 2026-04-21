#include <iostream>
using namespace std;
class Human
{
   protected:
   string name;
   int age;
   public:
   void work() //it can be accesible due to public
   {
      cout<<"I am working\n";
   }
};
class Student : public Human
{
   int roll_no,fees;
    public :
    Student (string name,int age,int roll_no, int fees)
      {
        this->name = name;
        this->age = age;
        this->roll_no = roll_no;
        this->fees=fees;
      }  
};

int main()
{
   Student A1("Rohit",26,11,9900);
   A1.work();
}