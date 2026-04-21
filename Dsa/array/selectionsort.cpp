#include <iostream>
using namespace std;
int main (){
    //by taking input from user
    int arr[1000];
    int n;
    cout<<"Enter size of array";
    cin>>n;
    cout<<"Enter the array: ";
    for(int i=0;i<n;i++)
    cin>>arr[i];
    // int arr[6] = {10,4,5,8,1,7};
    for(int i=0;i<n-1;i++)
    {
        int index=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[index])
            index=j;
        }
        swap(arr[i],arr[index]);
    }
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
}