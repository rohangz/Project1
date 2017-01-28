#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;
int isprime(int n)
{
    if(n==1) return 0;
    else if(n==2) return 1;
    else
    {
         for(int i = 2;i<=sqrt(n); ++i)
          if(n%i==0)
            return 0;
        return 1;
    }
}
int main()
{

    fstream obj("1.txt",ios::out);
    for(int i = 101;i<=299;++i)
       if(isprime(i)) obj<<i<<endl;
    obj.close();
    return 0;
}
