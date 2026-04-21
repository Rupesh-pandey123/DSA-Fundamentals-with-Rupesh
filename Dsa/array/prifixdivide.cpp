#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
bool divide(vector<int> arr){
    int prefix = 0, total_sum = 0, n = arr.size();

    // total sum
    for(int i = 0; i < n; i++)
        total_sum += arr[i];

    // check prefix == suffix
    for(int i = 0; i < n; i++) {
        prefix += arr[i];
        int suffix = total_sum - prefix;

        if(prefix == suffix)
            return true;
    }

    return false;
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> v(n);
    cout << "Enter the array elements: ";
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    if(divide(v))
        cout << "Yes, can be divided";
    else
        cout << "No, cannot be divided";

    return 0;
}
