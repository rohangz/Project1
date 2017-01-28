#include<iostream>
#include"bigInt.h"
using namespace std;
BigInt modInverse(BigInt a, BigInt m)
{
    BigInt m0 = m, t, q;
    cout<<"\n M,t,q are created "<<endl;
    BigInt x0 = Integer("0");
        cout<<"\n x0 created "<<endl;
     BigInt x1 = Integer("1");
     cout<<"\n x1 created "<<endl;

    BigInt one = Integer("1");
    cout<<"\n 1";
    BigInt zero = Integer("0");
    cout<<"0";
    if (m==one)
    {
        cout<<" 0 returned ";
        return zero;
    }

    while (a>one)
    {
        // q is quotient
        cout<<"loop started ";
        q=a/m;
        cout<<" q = q/m";

        t=m;
        cout<<" t = m";

        // m is remainder now, process same as
        // Euclid's algo
        m=a%m;
        cout<<" m = a%m ";
         a = t;
        cout<<"  a = t;";
        t=x0;
        cout<<"   t=x0; ";

        x0 = x1-(q * x0);
        cout<<"  x0 = x1-(q * x0);";

        x1=t;
        cout<<"  x1=t;";
    }

    // Make x1 positive
    if (x1<zero)
       x1 += m0;

    return x1;
}
int main()
{
    Print(modInverse(Integer("37"),Integer("137")));
    return 0;
}
