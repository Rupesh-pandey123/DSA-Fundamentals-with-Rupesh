#include <bits/stdc++.h>
using namespace std;
int main()
{
  int arr[5] = {1,2,3,4,5};
  int *ptr = arr;
    //print adrress of first element 
    cout<<arr<<endl;
    cout<<arr+0<<endl;
    cout<<&arr[0]<<endl;
    cout<<ptr<<endl;
    // print the address of second  element or 1 index
    cout<<arr+1<<endl;
    cout<<&arr[1]<<endl;
    //print value of zero index
    cout<<arr[0]<<endl;
    cout<<*arr<<endl;
    cout<<*(arr+0)<<endl;
    cout<<*ptr<<endl;

    //all address print 
    for(int i=0;i<5;i++)
    cout<<arr+i<<endl;

    //all value  print 
    for(int i=0;i<5;i++)
    cout<<*(arr+i)<<endl;
    //get all address 
    for(int i=0;i<5;i++)
    {
      cout<<ptr+1<<endl;

    }
    //addition 
    ptr = ptr+3;
    cout<<*ptr;
}