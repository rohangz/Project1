#ifndef VERMAN_H_INCLUDED
#define VERMAN_H_INCLUDED
#include<string>
#include<iostream>
#include<math.h>

using namespace std;

string binary(int a)
{
       string b = "";
      if(a == 0)
        b = "00000000";
      else
      {
          while(a!=0)
          {
              int r = a%2;
              a = a/2;
              b = (char)(r+48) + b;
          }
      }
      return b;
}
string makeit(string s,int i)
{
    int k = 0;
    string alpha = s;
    while(k<(i-s.length()))
    {
        alpha = "0" + alpha;
        ++k;
    }
    return alpha;
}
string vxor(string a,string b)
{
    string x ="";
    int l = a.size(),i=0;
    while(i<l)
    {
        if(a[i] == b[i])
            x=x+"0";
        else
            x=x+"1";
        ++i;
    }
    return x;
}
string doit(int size,string s)
{
    string m = "";
    for(int i = 0;i<8*size;i+=8)
    {
        string alpha = s.substr(i,8);
        int k = 0;
        for(int j=7;j>=0;--j)
            k = k + (alpha[j]-48)*pow(2,7-j);
        m = m+(char)k;
    }
    return m;
}

#endif // VERMAN_H_INCLUDED
