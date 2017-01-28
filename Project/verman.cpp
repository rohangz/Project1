#include<iostream>
#include<stdlib.h>
#include<string>
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
string xorr(string a,string b)
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
int main()
{
    string s;
    do{
 //
    string s;
    string key = "";
    string message = "";
    getline(cin,s);
    int l = s.size();
    int *arr = new int[l];
    for(int i = 0;i<l;++i)
    {
        string b = "";
        b = binary(s[i]);
        b = makeit(b,8);
        message = message + b;
        arr[i] = rand()%100;
//        cout<<arr[i]<<endl;
        b = binary(arr[i]);//<<endl;
    //    cout<<b<<endl;
        b = makeit(b,8);
        key = key+b;
//        cout<<key<<endl;
    }
    cout<<message<<endl<<key<<endl;//
    cout<<message.size()<<endl<<key.size()<<endl;
    string cipher = xorr(message,key);
    message = xorr(cipher,key);
    cipher = doit(l,cipher);
    cout<<cipher<<endl;
    cout<<message<<endl;
    message = doit(l,message);
    cout<<message<<endl;
    }while(s!="exit");
    return 0;

}
