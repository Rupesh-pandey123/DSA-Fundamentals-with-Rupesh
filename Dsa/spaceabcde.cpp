#include <iostream>
using namespace std;
int main(){
    int i,j,n;
    cout<<"Enter n:";
    cin>>n;
    //i=row,j=column
    for(i=1;i<=n;i=i+1)
    {
       for(j=1;j<=n-i;j=j+1)
       {
        cout<<"  ";
       }
       for(char name='A';name<='A'+i-1;name = name+1)
        cout<<name<<" ";
      cout<<endl;

}
}