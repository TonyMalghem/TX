#include "RSA.h"


int rsa::calc_phi_n(const int p, const int q)
{
    return (p-1)*(q-1);
}

int rsa::calc_e(const int phi_n)
{
    int i=2;
    while(i<phi_n)
    {
        if(phi_n%i!=0)
            return i;
        i++;
    }
    return 0;
}

int rsa::calc_d(const int phi_n, const int e)
{
    int a1, a2, a3, b1, b2, b3, t1, t2, t3, q;

    a1=1;
    a2=0;
    a3=phi_n;

    b1=0;
    b2=1;
    b3=e;

    while(b3!=1)
    {
        q=a3/b3;

        t1=a1-(q*b1);
        t2=a2-(q*b2);
        t3=a3-(q*b3);

        a1=b1;
        a2=b2;
        a3=b3;

        b1=t1;
        b2=t2;
        b3=t3;
    }
    if(b2<0)
        b2+=phi_n;
    return b2;
}

bool rsa::isPrime(int in)
{
    int i=2;
    if(in<2)
        return false;
    while(i<in/2)
    {
        if(i%in==0)
            return false;
        i++;
    }
    return true;
}

unsigned long long rsa::M_to_m(const std::string message)
{
    unsigned long long m=0;
    if(message.length()==1)
        return message.at(0);
    for(unsigned long int i=message.length()-1;i>0;i--)
    {
        unsigned int ascii = message.at(i);
        m+=ascii*pow(256,i);
    }
    return m;
}

int rsa::cipher(int plaintext, int n, int e)
{
    int i=1, t=1;
    while(i<=e)
    {
        t=t*plaintext;
        t=t%n;
        i++;
    }
    return t%n;
}
