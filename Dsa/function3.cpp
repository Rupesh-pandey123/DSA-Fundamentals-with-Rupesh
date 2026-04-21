//swap function
#include <iostream>
using namespace std;
void swap(int &a, int &b) //pass by refrence
{
    int c;
    c=a;
    a=b;
    b=c;

}
int main (){
    int a,b;
    cout<<"enter the both no : ";
    cin>>a>>b;
    swap(a,b);
    cout<<a<<" "<<b<<" ";
}