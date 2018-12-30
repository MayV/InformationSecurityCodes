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
    long long P;
    cout<<"Enter Plain Text :";
    cin>>P;

    long long p = 11;             ///Choose a prime
    long long e1 = 2;             ///Primitive root of Zp*
    while(e1 < p)
    {
        bool visit[p];
        memset(visit,0,sizeof(visit));
        visit[e1] = 1;
        long long cur = e1;
        for(long long i = 1;i<p;i++){
            cur = (cur*e1)%p;
            visit[cur] = 1;
        }
        bool flag = true;
        for(long long i = 1;i<p;i++)
            if(!visit[i])
            {
                flag = false;
                break;
            }
        if(flag)
            break;
        e1++;
    }
    long long d = 3;              /// Choose 1 <= d <= p-2
    long long  e2 = getpower(e1,d,p);

    cout<<"Public Key: p = "<<p<<", e1 = "<<e1<<", e2 = "<<e2<<endl;
    cout<<"Private Key: d = "<<d<<endl;

    cout<<"ENCRYPTION"<<endl;
    long long r = 4;              ///Choose a random number r
    long long C1 = getpower(e1,r,p);
    long long C2 = (P * getpower(e2,r,p))%p;
    cout<<"Cipher Text: "<<C1<<" and "<<C2<<endl;

    cout<<"DECRYPTION"<<endl;
    P = (C2 * getinverse(getpower(C1,d,p),p))%p;
    cout<<"Plain Text: "<<P<<endl;
}
