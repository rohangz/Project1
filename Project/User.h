#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include"RSA.h"
#include<iostream>
#include"SHA1.h"
#include<string>
#include<stdlib.h>
#include"Verman.h"

using namespace std;

string getpassword( const string& prompt = "Enter password> " )
  {
  string result;

  // Set the console mode to no-echo, not-line-buffered input
  DWORD mode, count;
  HANDLE ih = GetStdHandle( STD_INPUT_HANDLE  );
  HANDLE oh = GetStdHandle( STD_OUTPUT_HANDLE );
  if (!GetConsoleMode( ih, &mode ))
    throw runtime_error(
      "getpassword: You must be connected to a console to use this program.\n"
      );
  SetConsoleMode( ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  // Get the password string
  WriteConsoleA( oh, prompt.c_str(), prompt.length(), &count, NULL );
  char c;
  while (ReadConsoleA( ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
    {
    if (c == '\b')
      {
      if (result.length())
        {
        WriteConsoleA( oh, "\b \b", 3, &count, NULL );
        result.erase( result.end() -1 );
        }
      }
    else
      {
      WriteConsoleA( oh, "*", 1, &count, NULL );
      result.push_back( c );
      }
    }

  // Restore the console mode
  SetConsoleMode( ih, mode );

  return result;
  }
class User
{
    private: string username;
             string password;
             string name;
             string balance;
     public: User();
             int getpass();
             int Register();
             string Vencrypt();
             int login();
};
int User::login()
{
    string u,p;
    system("cls");
    cout<<"\nEnter Username ";
    cin>>u;
    username=u;
    p=getpassword("Enter password>");
    SHA1 Hash(u);
    Hash.compute();
    u=Hash.retvalue();
    u=u+".txt";
    fstream obj(u.c_str());
    if(!obj)
    {
        cout<<"\nError "<<endl;
        system("pause");
        obj.close();
        return 0;
    }
    obj.close();
    obj.open(u.c_str(),ios::in);
    string alpha = "";
    string beta = "";
    obj>>alpha;
//    cout<<"Alpha == "<<alpha<<endl;
    obj>>beta;
    BigInt Beta = Integer(beta);
 //   obj>>name;
 //   fflush(obj);
 //    obj.get();
     obj.get();
//    getline(obj,name);
    getline(obj,name);
    cout<<name<<endl;
   // cout<<name.size()<<endl;
 //   fflush(obj);
    obj>>password;
    if(password!=p)
    {
        cout<<endl<<"Wrong Username Password "<<endl;
        system("pause");
        return 0;
    }
    string cop = alpha.substr(alpha.size()-14,14);
    BigInt e = Integer(cop.substr(0,2)),pq = Integer(cop.substr(2,6)),qn = Integer(cop.substr(8,6));
//    Print(e);
//    Print(pq);
//    Print(qn);
    RSA R1(pq,qn,e);
    Beta = R1.Decrypt(Beta);
    cout<<endl<<"Login Succesful "<<endl;
    system("pause");
    system("cls");
    string k1="",k2="";
    int l = name.size();
    k1=name.substr(0,l/2);
    k2=name.substr(l/2,l/2);
//    cout<<k1<<endl<<k2<<endl;
    string message ="",key = "";
    for(int i=0;i<l/2;++i)
    {
        string b = "";
        b=binary(k1[i]);
        b=makeit(b,8);
        message=message+b;
        b=binary(k2[i]);
        b=makeit(b,8);
        key=key+b;
    }
    name="";
    name=vxor(message,key);
 //   name =vxor(message,key);
    name=doit(l/2,name);
    for(int i=0;i<l/2;++i)
        if(name[i]=='_') name[i] = ' ';
    cout<<"Hello "<<name<<endl;
    cout<<endl<<"Your Balance == ";
    Print(Beta);
 //  cout<<cop<<endl;
    system("pause");
    obj.close();
    return 1;
}
string User::Vencrypt()
{
    string message = "";
    string key = "";
    int n=name.size();
    int *arr = new int[n];
    for(int i =0;i<n;++i)
    {
        string b="";
        b=binary(name[i]);
        b=makeit(b,8);
        message=message+b;
        arr[i]=rand()%100;
        char c=arr[i];
        if(c==' ') c='$';
        arr[i]=c;
        b=binary(arr[i]);
        b=makeit(b,8);
        key=key+b;
    }
    string cipher=vxor(message,key);
    cipher=doit(n,cipher);
    cout<<cipher<<endl;
    key=doit(n,key);
    cout<<key<<endl;
    cipher=cipher+key;
    return cipher;
}
int User::Register()
{
 //   fstream obj;
    cout<<"\nEnter Username "<<endl;
    cin>>username;
    SHA1 obj1(username);
    obj1.compute();
    username = obj1.retvalue();
    username = username + ".txt";
    fstream obj(username.c_str());
    if(obj)
    {
        cout<<"\nUsername already exists use a unique one ";
        system("pause");
        obj.close();
        return 0;
    }
    obj.open(username.c_str(),ios::out);
    int check = getpass();
    if(!check)
    {
        cout<<"\nSomething went wrong "<<endl;
        obj.close();
        remove(username.c_str());
        system("pause");
        return check;
    }
    cout<<endl<<"Enter your name "<<endl;
    fflush(stdin);
    getline(cin,name);
    fflush(stdin);
    cout<<"Enter your Balance "<<endl;
    cin>>balance;
    RSA R1;
    R1.getPrimes();
    BigInt qwerty =  R1.Encrypt(Integer(balance));
    Print(qwerty);
    BigInt e1 = R1.returne1();
//    obj<<name<<endl;
    Print(e1);
    for(int i = e1.size();i>=0;--i)
        obj<<e1[i];
//    obj<<endl;
    BigInt e=R1.returne(),n=R1.returnn(),qn=R1.returnqn();
    Print(n);
    Print(qn);
    int ae=e[0],an=n[0],aqn=qn[0];
    obj<<e[0];
    int count=0;
    while(n!=Integer("0"))
    {
        n=n/10;
        count++;
    }
    if(count==5)
        obj<<"0"<<an;
    else obj<<an;
    count = 0;
    while(qn!=Integer("0"))
    {
        qn=qn/10;
        count++;
    }
    if(count==5)
        obj<<"0"<<aqn;
    else
        obj<<qn;
    obj<<endl;
    for(int i = qwerty.size()-1;i>=0;--i)
        obj<<qwerty[i];
    name=Vencrypt();
    cout<<name<<endl;
    obj<<endl;
    obj<<name<<endl;

    obj<<password<<endl;
    cout<<"Registration Succesful "<<endl;
    obj.close();
    system("pause");
    return 1;
}
int User::getpass()
{

    string ps = "";
    try
    {
          password = getpassword( "Enter a password> " );
          cout<<endl;
          ps = getpassword("Re-Enter password>");

    }
  catch (exception& e)
    {
    cerr << e.what();
    return 0;
    }
    if(ps==password)
        return 1;
    else return 0;

}
User::User()
{
    password = "";
    username = "";
    name = "";
    balance = 0.0;
}


#endif // USER_H_INCLUDED
