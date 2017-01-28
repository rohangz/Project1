#include<iostream>
#include<stdexcept>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<fstream>
#include"User.h"
#include"Sha1.h"
#include"RSA.h"
#include"bigint.h"

using namespace std;

int main()
{
    char ch;
    User us;
    while(1)
    {

        system("cls");
        cout<<"\n1.Register "<<endl;
        cout<<"\n2.Login "<<endl;
        cout<<"\n3.Exit "<<endl;
        ch = getchar();
        switch(ch)
        {
            case '1':us.Register();
                     break;
            case '2':us.login();
                     break;
            case '3':exit(0);
        }
    }
    return 0;
}
