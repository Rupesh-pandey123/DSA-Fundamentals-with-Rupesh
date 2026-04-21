#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ofstream fout;
    fout.open("z1.txt");
    fout<<"Hello Rupesh\n";
    fout<<"Hello Anurag\n";
    fout<<"Hello Rupesh\n";
    fout.close();
    

    ifstream fin;
    fin.open("z1.txt");
    string line;
    while (getline(fin,line))
    {
        cout<<line<<endl;
    }
    fin.close();

}
