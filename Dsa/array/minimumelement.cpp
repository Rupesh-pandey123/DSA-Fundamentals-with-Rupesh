#include <bits/stdc++.h>
using namespace std;
//to find minimumm element in a array
int main() {
    int arr[5] = {5,10,11,2,3};
    int ans = INT_MAX;
    for(int i=0;i<5;i++)
    {
    if(arr[i]<ans)
    ans = arr[i];
    }
    cout<<ans;


}