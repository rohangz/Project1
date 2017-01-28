#include<iostream>
#include<math.h>
#include<stdlib.h>
#include"bigInt.h"
using namespace std;

void f1()
{
    cout<<"Function 1 "<<endl;
}
void f2()
{
    cout<<"Function 2 "<<endl;

}
void f3()
{
    cout<<"Function 3 "<<endl;
    atexit(f1);
}
int main()
{

    cout<<"Hello "<<endl;
 //  atexit(f1);
 //  atexit(f2);
    atexit(f3);
 //   f1(); f2(); f3();
//  cout<<s<<endl;
    return 0;
}
