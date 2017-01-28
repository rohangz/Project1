#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
#include"Verman.h"
#include"bigint.h"
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

class RSA
{
    private: BigInt pkey;
             BigInt p1,p2,pq;
             BigInt qn;
             BigInt e,d;
             BigInt e1,d1;
             int arr[1000],size;
     public: BigInt pubkey;
             RSA();
             RSA(BigInt n,BigInt qqn,BigInt ee);
             BigInt Encrypt(BigInt message);
             BigInt Decrypt(BigInt message);
             BigInt gcdprime();
             BigInt returne1();
             BigInt returnd1();
             void getPrimes();
             BigInt modInverse(BigInt a,BigInt m);
             BigInt returnp1();
             BigInt returnp2();
             BigInt returne();
             BigInt returnqn();
             BigInt returnn();
};
RSA::RSA(BigInt n,BigInt qqn,BigInt ee)
{
    pq = n;
    qn = qqn;
    e = ee;
    d = modInverse(e,qn);
//    Print(d);
 //   Print(d);
}
BigInt RSA::returnqn()
{
    return qn;
}
BigInt RSA::returnn()
{
    return pq;
}
BigInt RSA::returne()
{
    return e;
}
BigInt RSA::returnp1()
{
    return p1;
}
BigInt RSA::returnp2()
{
    return p2;
}
BigInt RSA::returne1()
{
    return e1;
}
BigInt RSA::returnd1()
{
    return d1;
}
unsigned long long int gcd(unsigned long long int u, unsigned long long int v)  //Binary GCD Algorithm
{
    // simple cases (termination)
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
	if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);

    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);

    return gcd((v - u) >> 1, u);
}
RSA::RSA()
{
      int i = 0;
    fstream obj;

    obj.open("1.txt",ios::in);
    while(!obj.eof())
          obj>>arr[i++];
    size = i-2;
    obj.close();
}
BigInt RSA::modInverse(BigInt a, BigInt m)
{
    BigInt m0 = m, t, q;
   // cout<<"\n M,t,q are created "<<endl;
    BigInt x0 = Integer("0");
     //   cout<<"\n x0 created "<<endl;
     BigInt x1 = Integer("1");
   //  cout<<"\n x1 created "<<endl;

    BigInt one = Integer("1");
   // cout<<"\n 1";
    BigInt zero = Integer("0");
   // cout<<"0";
    if (m==one)
    {
       // cout<<" 0 returned ";
        return zero;
    }

    while (a>one)
    {
        // q is quotient

        q=a/m;


        t=m;


        // m is remainder now, process same as
        // Euclid's algo
        m=a%m;

         a = t;

        t=x0;


        x0 = x1-(q * x0);


        x1=t;

    }

    // Make x1 positive
    if (x1<zero)
       x1 += m0;

    return x1;
}
void RSA::getPrimes()
{

    int alpha,beta;
    alpha = rand()%size;
    beta = alpha;
    while(beta == alpha)
        beta = rand()%size;
    alpha = arr[alpha];
    beta = arr[beta];
    p1 = Integer(alpha);
    p2 = Integer(beta);
    pq = p1*p2;
 //   cout<<"\nCalculated pq"<<endl;
    qn = (p1-1)*(p2-1);
//    cout<<"\nCalculated qn"<<endl;
    e = Integer("31");
   // d = Integer("38000");
    do
    {
        while(gcd(e,qn)!=Integer(1))
        {
            e=e+2;
        }
        d = modInverse(e,qn);
        if(d>Integer("30000"))
            e=e+2;
    }while(d>Integer("30000"));
 //   cout<<"\nCalculated Mod inverse "<<endl;
//    Print(e);
//    Print(d);
//    obj.close();
        Print(e);
        Print(d);
}
BigInt RSA::Encrypt(BigInt message)
{
    e1 = pow(message,e);
    BigInt qwer = e1%pq;
    return qwer;
}
BigInt RSA::Decrypt(BigInt message)
{
    d1 = pow(message,d);
    BigInt de =d1%pq;
    return de;
}
#endif // RSA_H_INCLUDED
