#include <iostream>
using namespace std;
int main(){
    int i,j;
    //i=row,j=column
    for(i=5;i>=1;i=i-1)
    {
       for(j=1;j<=i;j=j+1)
       {
        cout<<j<<" ";
       }
      cout<<endl;

}
}