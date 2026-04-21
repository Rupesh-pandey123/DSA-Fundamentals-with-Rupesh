#include <iostream>
using namespace std;

class Engineer
{
    public:
    string specialization;
    void work(){
        cout<<"I have specialization in : "<<specialization<<endl;
    }

};
class Youtuber 
{
    public:
    int subscriber;
    void contentcreator(){
        cout<<"I have subscriber: "<<subscriber<<endl;
    }
};

class CodeTeacher :public Engineer,public Youtuber
{
    public:
    string name;
    CodeTeacher(string name,string specialization, int subscriber)
    {
        this->name=name;
        this->specialization=specialization;
        this->subscriber=subscriber;

    }
    void showcase()
    {
        cout<<"My name is: "<<name<<endl;
        work();
        contentcreator();
    }
};

int main() {
      CodeTeacher A1("Rohit","CSE",4500);
      A1.showcase();
}