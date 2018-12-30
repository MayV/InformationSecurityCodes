#include<bits/stdc++.h>
using namespace std;

long long ext_euclid(long long r1, long long r2, long long t1, long long t2, long long M)
{
    while(r2!=0)
    {
        long long q = r1/r2;
        long long r = r1-q*r2;
        r1 = r2;
        r2 = r;
        long long t = (t1-(q*t2)%M+M)%M;
        t1 = t2;
        t2 = t;
    }
    return t1%M;
}

long long chinese_remainder(vector<long long> a, vector<long long> m)
{
    long long M = 1;
    for(int i=0;i<m.size();i++)
        M *= m[i];
    vector<long long> newm;
    for(int i=0;i<m.size();i++)
        newm.push_back(M/m[i]);
    vector<long long> newminv;
    for(int i=0;i<m.size();i++)
        newminv.push_back(ext_euclid(m[i], newm[i]%m[i], 0, 1, m[i]));
    long long x = 0;
    for(int i=0;i<m.size();i++)
        x = (x+(a[i]*newm[i]*newminv[i])%M)%M;
    return x;
}

long long getgcd(long long a, long long b)
{
    if(b==0)
        return a;
    return getgcd(b,a%b);
}

int main()
{
    cout<<"This is the program of chinese remainder theorem.\n\n\n";

    vector<long long> a;
    vector<long long> m;

    long long inpa, inpm;
    cout<<"Enter input a: ";
    cin>>inpa;
    cout<<"Enter input M: ";
    cin>>inpm;
    a.push_back(inpa);
    m.push_back(inpm);
    while(1)
    {
        char c;
        cout<<"Enter an equation(y/n): ";
        cin>>c;
        if(c=='n')
            break;
        cout<<"Enter input a: ";
        cin>>inpa;
        cout<<"Enter input M: ";
        cin>>inpm;
        a.push_back(inpa);
        m.push_back(inpm);
    }
    long long ans;
    if(m.size()==1)
        ans = a[0]%m[0];
    else
    {
        bool flag = true;
        for(int i=0;i<m.size();i++)
            for(int j=i+1;j<m.size();j++)
            {
                int val = getgcd(m[i],m[j]);
                if(val!=1)
                    flag = false;
            }
        if(!flag)
        {
            cout<<"Chinese remainder is not applicable because all m pairs are not co-prime to each other.";
            return 0;
        }
        ans = chinese_remainder(a,m);
    }
    cout<<"Value of x which satisfy all the conditions is: "<<ans<<endl;
    return 0;
}
