#include <iostream>
using namespace std;
class Student
{
 public: 
 string name;
 int age, roll_no;
 string grade;
 //Funtion Getter and setter
 public:
 void setname(string n)
 {
    name = n;
 }
 void setage(int a)
 {
    age =a;
 }


};


int main() {
    Student S1;
    S1.name = "Rohit;";
    S1.age = 10;
    S1.roll_no = 123;
    S1.grade = "A++";
    cout<<S1.age<<" "<<endl;

    Student S2;
    S2.name = "Mohit;";
    S2.age = 18;
    S2.roll_no = 345;
    S2.grade = "A+";
    cout<<S2.age<<" "<<S2.grade<<" ";
}