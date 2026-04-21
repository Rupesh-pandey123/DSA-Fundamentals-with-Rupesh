#include <iostream>
using namespace std;
int main(){
    int i,j;
    int count=1;
    //i=row,j=column
    for(i=1;i<=5;i=i+1)
    {
       for(j=1;j<=5;j=j+1)
       {
        cout<<count<<" ";
        count=count+1;

       }
      cout<<endl;

}
}