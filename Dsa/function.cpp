//summation of two number
#include <iostream>
using namespace std;
//sum function
int Sum(int n, int m){
    int ans= n+m;
    return ans;
}
//multiply function
int Mul(int a, int b){
    int ans=a*b;
    return ans;
}
//void function
void fun()
 {
    cout<<"Hello Rupesh, this is your answer";

}
int main() {
    int a,b;
    cout<<"Enter the two numbers :";
    cin>>a>>b;

    cout<<Sum(a,b);
    cout<<endl;
    cout<<Mul(a,b);
    cout<<endl;
    fun();
}
