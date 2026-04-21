#include <iostream>
using namespace std;
class Human
{
   protected:
   string name;
   int age;
   public:
   Human()
   {

   };
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
      void dis()
      {
        cout<<name<<" "<<age<<" "<<roll_no<<" "<<fees<<endl;
      }
};

class Teacher: public Human
{
   int salary;
   public:
   Teacher(int salary,string name,int age)
   {
    this->salary=salary;
    this->name=name;
    this->age=age;
   }
   void display()
   {
    cout<<name<<" "<<age<<" "<<salary<<endl;
   }
};

int main()
{
   Student A1("Rohit",26,11,9900);
   A1.dis();
   Teacher A2(1000,"Mohit",18);
   A2.display();

}