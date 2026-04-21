#include <iostream>
using namespace std;
int main(){
    int i,j,n;
    //i=row,j=column
    cout<<"Enter n: ";
    cin>>n;
    for(i=1;i<=n;i=i+1)
    {
       for(j=1;j<=n-i;j=j+1)
        cout<<"  ";
       for(j=1;j<=i;j=j+1)
        cout<<j<<" ";
      cout<<endl;

}
}