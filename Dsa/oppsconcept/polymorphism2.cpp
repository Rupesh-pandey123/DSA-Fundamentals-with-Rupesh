#include <iostream>  //complie time operator overloading
using namespace std;
class Complex
{
   int real,image;
   public:
    Complex()
    {

    }

   Complex(int real,int image)
   {
    this->real = real;
    this->image = image;
   }; 
   void dislpay()
    {
        cout<<real<<" +i"<<image<<endl;
    }
    Complex operator +(Complex &C)
    {
        Complex ans;
        ans.real = real+C.real;
        ans.image = image+C.image;
        return  ans;
    }
   
};
int main()
{
  Complex C1(3,4);
  Complex C2(5,6);
  Complex C3 = C1+C2;
  C3.dislpay();
}
