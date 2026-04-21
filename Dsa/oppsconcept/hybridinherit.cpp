#include <iostream>
using namespace std;

// male
class Male
{
public:
    void Maleprint()
    {
        cout << "I am a male\n";
    }
};

// female
class Female
{
public:
    void Femaleprint()
    {
        cout << "I am a female\n";
    }
};

// student
class Student
{
public:
    void print()
    {
        cout << "I am a student\n";
    }
};

// boy
class Boy : public Student, public Male
{
public:
    void Boyprint()
    {
        cout << "I am a boy\n";
    }
};

// girl
class Girl : public Student, public Female
{
public:
    void Girlprint()
    {
        cout << "I am a Girl\n";
    }
};

int main()
{
    Girl G1;
    G1.Girlprint();
    G1.print();
    
}