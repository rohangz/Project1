#ifndef SHA1_H_INCLUDED
#define SHA1_H_INCLUDED
#include"Verman.h"

using namespace std;

class SHA1
{
  private: string message;
           string value;
  public:  SHA1();
           SHA1(string s1);
           void compute();
           string retvalue();
};
string SHA1::retvalue()
{
    return value ;
}
int makeEqualLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1; // If len1 >= len2
}

// The main function that adds two bit sequences and returns the addition
string addBitStrings( string first, string second )
{
    string result;  // To store the sum bits

    // make the lengths same before adding
    int length = makeEqualLength(first, second);

    int carry = 0;  // Initialize carry

    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';

        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';

        result = (char)sum + result;

        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }

    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;

    return result;
}

string xorr(string a,string b)
{
    string x = "00000000000000000000000000000000";
    for(int i = 0;i<32;++i)
       if(a[i]!=b[i]) x[i] = '1';
    return x;
}

string orr(string a,string b)
{
    string x = "00000000000000000000000000000000";
    for(int i = 0;i<32;++i)
        if(a[i]=='1' || b[i] =='1') x[i] = '1';
    return x;
}
string andd(string a,string b)
{
    string x = "00000000000000000000000000000000";
    for(int i = 0;i<32;++i)
        if(a[i]=='1' && b[i] =='1') x[i] = '1';
    return x;
}
string nott(string a)
{
    string x = "00000000000000000000000000000000";
    for(int i = 0;i<32;++i)
    {
        if(a[i]=='0')x[i] = '1';
        else x[i] ='0';
    }
    return x;
}

string lrot(string s,int y)
{
    int i;
    while(y--)
    {
        char temp = s[0];
        for(i = 0;i<31;++i)
            s[i] = s[i+1];
        s[i] = temp;
    }
    return s;
}
string xorr(string a,string b,string c,string d)
{
        string x = "00000000000000000000000000000000";
        for(int i = 0;i<32;++i)
        {
            if(a[i] == b[i]) x[i] = '0';
            else x[i] = '1';
        }
        for(int i = 0;i<32;++i)
        {
            if(x[i] == c[i]) x[i] = '0';
            else x[i] = '1';
        }
        for(int i = 0;i<32;++i)
        {
            if(x[i] == d[i]) x[i] = '0';
            else x[i] = '1';
        }
        return x;
}
string chunkit(int a,int l)
{
    string a1 = "";
    for(int i =0;i<l;++i)
        a1 = a1 + "0";
    int i = l-1;
    while(a!=0)
    {
        a1[i--] = 48 + a%2;
        a = a/2;
    }
    while(i>0)
        a1[i--] = '0';
    return a1;
}

string function1(string B,string C,string D)
{
//f' equal to: (B AND C) or (!B AND D)
    string F1 = andd(B,C);
    string F2 = andd(nott(B),D);
    string F = orr(F1,F2);
    return F;
}
string function2(string B,string C,string D)
{
//'f' equal to: B XOR C XOR D
  string F = xorr(B,C);
  F = xorr(F,D);
  return F;
}
string function3(string B,string C,string D)
{
//(B AND C) OR (B AND D) OR (C AND D)
    string F1 = andd(B,C);
    string F2 = andd(B,D);
    string F3 = andd(C,D);
    string F4 = orr(F1,F2);
    string F  = orr(F4,F3);
    return F;
}
string convert(string s1)
{
    string s2 = "00000000000000000000000000000000";
    int l = s1.length()-1;
    int i = 31;
    while(i>=0)
    {
        s2[i--] = s1[l--];
    }

    return s2;
}
string tohex(string s1)
{
    string x="";
    string hex="";
    for(int i = 0;i<10;++i)
        hex = hex + (char)(i + 48);
    for(int i = 10;i<16;++i)
        hex = hex + (char)(i-10 + 65);
    for(int i = 0;i<29;i = i+4)
    {
          string alpha = s1.substr(i,4);
          int k = (alpha[0] - 48)*8 + (alpha[1] - 48)*4 + (alpha[2] - 48)*2 + (alpha[3] - 48);
          x = x + hex[k];
    }
    return x;
}

SHA1::SHA1()
{
   // key = "";
    message = "";
    value = "";
}
SHA1::SHA1(string s1)
{
    message = s1;
}
void SHA1::compute()
{
    string    h0 = "01100111010001010010001100000001",
              h1 = "11101111110011011010101110001001",
              h2 = "10011000101110101101110011111110",
              h3 = "00010000001100100101010001110110",
              h4 = "11000011110100101110000111110000";

    int l = message.length();
    int *a = new int [l];
    for(int i = 0; i<l ;++i)
    {
        a[i] = message[i];
     //   cout<<a[i]<<" ";
    }
    string alpha="";
    for(int i = 0;i<l;++i)
        alpha = alpha + chunkit(a[i],8);
    alpha = alpha +"1";
    int lalpha = alpha.length();
    int k = 448 - lalpha;
    for(int i = 0;i<k;++i)
        alpha = alpha + "0";
    alpha = alpha + chunkit(lalpha-1,64);
    string words[80];
   // cout<<"\nWORDS"<<endl;
    for(int i = 0,j = 0;i<16;++i)
    {
        words[i] = alpha.substr(j,32);
        j = j + 32;
  //      cout<<words[i]<<endl;
    }
    for(int i = 16;i<80;++i)
    {
        words[i] = xorr(words[i-16],words[i-14],words[i-8],words[i-3]);
        words[i] = lrot(words[i],1);
  //      cout<<words[i]<<endl;
    }
    //======Main Loop===================================
    int i = 0;
    string A = h0, B = h1,C = h2,D = h3,E = h4;
    string F,K,temp;
    while(i<80)
    {
        if(i>=0 && i<20)
        {
            F = function1(B,C,D);
            K = "01011010100000100111100110011001";
        }
        else if(i>=20 && i<40)
        {
            F = function2(B,C,D);
            K = "01101110110110011110101110100001";
        }
        else if(i>=40 && i<60)
        {
            F = function3(B,C,D);
            K = "10001111000110111011110011011100";
        }
        else if(i>=60 && i<80)
        {
            F = function2(B,C,D);
            K = "11001010011000101100000111010110";
        }
        //(A left rotate 5) + F + E + K + (the current word)

        temp = lrot(A,5);
        temp = addBitStrings(temp,F);
        temp = addBitStrings(temp,E);
        temp = addBitStrings(temp,K);
        temp = addBitStrings(temp,words[i]);
        temp = convert(temp);
        E = D;
        D = C;
        C = lrot(B,30);// 30
        B = A;
        A = temp;

        i++;

    }
    h0 = addBitStrings(h0,A);
    h1 = addBitStrings(h1,B);
    h2 = addBitStrings(h2,C);
    h3 = addBitStrings(h3,D);
    h4 = addBitStrings(h4,E);
    h0 = convert(h0);
    h1 = convert(h1);
    h2 = convert(h2);
    h3 = convert(h3);
    h4 = convert(h4);
//    cout<<"\n\n Final H's values "<<endl;
    string hex = tohex(h0) + tohex(h1) +  tohex(h2) + tohex(h3) + tohex(h4);
//    cout<<endl<<hex;
    value = hex;
}


#endif // SHA1_H_INCLUDED
