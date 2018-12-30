#include<bits/stdc++.h>
using namespace std;

int getgcd(int a, int b)
{
    if(b==0)
        return a;
    return getgcd(b, a%b);
}

int getinverse(int a, int m)
{
    int r1 = m, r2 = a, t1 = 0, t2 = 1;
    while(r2 > 0)
    {
        int q = r1/r2;
        int r = (r1 - (q*r2)%m + m)%m;
        r1 = r2;
        r2 = r;
        int t = (t1 - (q*t2)%m + m)%m;
        t1 = t2;
        t2 = t;
    }
    return t1;
}

int getpower(int b, int e, int n)
{
    if(e==0)
        return 1;
    else if(e%2==0)
        return getpower((b*b)%n, e/2, n);
    else
        return (b*getpower(b, e-1, n))%n;
}

int main()
{
    int M;
    cout<<"Enter Message: ";
    cin>>M;

    ///Two large primes.
    int p = 7, q = 11;
    int n = p*q;
    int phi = (p-1)*(q-1);

    /// 1 < e < phi and e is coprime to phi.
    int e = 2;
    while(getgcd(e, phi)!=1)
        e++;
    int d = getinverse(e, phi);

    cout<<"Public Key: n = "<<n<<", e = "<<e<<endl;
    cout<<"Private Key: d = "<<d<<endl;

    cout<<"SIGNING"<<endl;
    int S = getpower(M, d, n);
    cout<<"Signature: "<<S<<endl;

    cout<<"VERIFICATION"<<endl;
    int V = getpower(S, e, n);
    cout<<"Message: "<<V<<endl;

    return 0;
}
