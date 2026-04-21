#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
       vector<int> v;
       v.push_back(10);
       v.push_back(50);
       v.push_back(30);
       v.push_back(60);
       //for sorting
       sort(v.begin(),v.end());
       for(auto i=0;i<v.size();i++)
              cout<<v[i]<<" "<<endl;
              //searching in binary search
       cout<<binary_search(v.begin(),v.end(),30)<<endl;
       //to fin address
       cout<<find(v.begin(),v.end(),60)-v.begin()<<endl;
}