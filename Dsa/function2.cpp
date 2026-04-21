//prime number function
#include <iostream>
using namespace std;
bool Prime(int n)
{
    if(n<2)
    return 0;
    for(int i=2;i<n;i++)
    {
        if(n%i == 0)
        return 0;
    }
    return 1;


}

int Fact(int n=3) //default parameter
{
    int ans=1;
    for(int i=1;i<=n;i++)
    ans = ans*i;
    return ans;
}
int main() {
    int a,b;
    cout<<"Enter the number";
    cin>>a>>b;
    cout<<Prime(a)<<endl;
    cout<<Fact(a)<<endl;
    cout<<Prime(b-a)<<endl;
    cout<<Fact(b-a)<<endl;
}