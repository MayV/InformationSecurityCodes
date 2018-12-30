#include<bits/stdc++.h>
using namespace std;

long long getpower(long long b, long long e, long long p)
{
    if(e==0)
        return 1;
    else if(e%2==0)
        return getpower((b*b)%p, e/2, p);
    else
        return (b*getpower(b, e-1, p))%p;
}

long long getinverse(long long a, long long m)
{
    long long r1 = m, r2 = a, t1 = 0, t2 = 1;
    while(r2 > 0)
    {
        long long q = r1/r2;
        long long r = (r1 - (q*r2)%m + m)%m;
        r1 = r2;
        r2 = r;
        long long t = (t1 - (q*t2)%m + m)%m;
        t1 = t2;
        t2 = t;
    }
    return t1%m;
}

int main()
{
    long long M;
    cout<<"Enter message: ";
    cin>>M;

    long long p = 3119;             ///Select Large prime.
    long long e1 = 7;               ///Primitive root of set Zp*
    long long d = 127;              ///Random number s.t. 1 <= d <= p-2.
    long long e2 = getpower(e1, d, p);

    cout<<"Public Key: p = "<<p<<", e1 = "<<e1<<", e2 = "<<e2<<endl;
    cout<<"Private Key: d = "<<d<<endl;

    cout<<"SIGNING"<<endl;
    long long r = 307;              ///Select Random number, select different r each time.
    long long S1 = getpower(e1, r, p);
    long long S2 = ((M%(p-1) - (d * S1%(p-1))%(p-1) + (p-1))%(p-1) * getinverse(r, p-1))%(p-1);
    cout<<"Signatures are: "<<S1<<", "<<S2<<endl;

    cout<<"VERIFICATION"<<endl;
    long long V1 = getpower(e1, M, p);
    long long V2 = (getpower(e2, S1, p) * getpower(S1, S2, p))%p;
    cout<<"V1 = "<<V1<<", "<<"V2 = "<<V2<<endl;
    if(V1 == V2)
        cout<<"Accept"<<endl;
    else
        cout<<"Reject"<<endl;
    return 0;
}
