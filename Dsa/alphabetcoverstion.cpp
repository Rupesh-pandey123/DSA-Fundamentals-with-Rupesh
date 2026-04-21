//alphabetcoverstion from small to capital c++ series
#include <iostream>
using namespace std;
char convert(char name) {
    char ans=name-'a' + 'A';
   
    return ans;
}
int main() {
    char name;
    cout<<"Enter the alphabet :";
    cin>>name;
    cout<<convert(name)<<endl;
    return 0;
}