#include<bits/stdc++.h>
using namespace std;

long long getpower(long long b, long long e, long long M)
{
    if(e==0)
        return 1;
    else if(e%2==0)
        return getexp((b*b)%M, e/2, M);
    else
        return (b*getexp(b, e-1, M))%M;
}

long long ext_euclid(long long r1, long long r2, long long t1, long long t2, long long M)
{
    while(r2 > 0)
    {
        long long q = r1/r2;
        long long r = (r1 - (q*r2)%M + M)%M;
        r1 = r2;
        r2 = r;
        long long t = (t1 - (q*t2)%M + M)%M;
        t1 = t2;
        t2 = t;
    }
    return t1%M;
}

long long chineserem(long long a1, long long a2, long long m1, long long m2)
{
    long long M = m1*m2;
    long long M1 = M/m1;
    long long M2 = M/m2;
    long long m1inv = ext_euclid(m1,M1%m1,0,1,m1);
    long long m2inv = ext_euclid(m2,M2%m2,0,1,m2);
    long long x = ((a1*m1inv*M1)%M + (a2*m2inv*M2)%M)%M;
    return x;
}

int main()
{
    long long p = 23; ///p is large prime, must be of the form 4k+3.
    long long q = 7;  ///q is large prime, must be of the form 4k+3.
    long long n = p*q;

    long long P;
    cout<<"Enter Plain Text: ";
    cin>>P;

    cout<<"Public Key: n = "<<n<<endl;
    cout<<"Private Key: p = "<<p<<"q = "<<q<<endl;

    cout<<"ENCRYPTION"<<endl;
    long long C;
    C = ((P%n)*(P%n))%n;
    cout<<"Cipher Text: "<<C<<endl;

    cout<<"DECRYPTION";
    long long val1 = getpower(C,(p+1)/4, p);
    long long val2 = getpower(C,(q+1)/4, q);
    long long rc[4];
    rc[0] = chineserem(val1, val2, p, q);
    rc[1] = chineserem(val1, (q-val2)%q, p, q);
    rc[2] = chineserem((p-val1)%p, val2, p, q);
    rc[3] = chineserem((p-val1)%p, (q-val2)%q, p, q);
    cout<<"Expected plain texts are: "<<rc[0]<<", "<<rc[1]<<", "<<rc[2]<<", "<<rc[3]<<".";
}
