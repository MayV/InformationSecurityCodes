#include<bits/stdc++.h>
using namespace std;

int ext_euclid(int r1, int r2, int t1, int t2, int M)
{
    while(r2!=0)
    {
        int q = r1/r2;
        int r = r1-q*r2;
        r1 = r2;
        r2 = r;
        int t = t1-q*t2;
        t1 = t2;
        t2 = t;
    }
    return (t1+t2+26)%M;
}

int main()
{
    string p;
    cout<<"Enter Plain text: ";
    cin>>p;
    int k1;
    cout<<"Enter Multiplicative Key: ";
    cin>>k1;
    int k2;
    cout<<"Enter Additive Key: ";
    cin>>k2;

    cout<<"ENCRYPTION"<<endl;
    string c = p;
    for(int i=0;i<p.length();i++)
        c[i] = (char)((((p[i]-'A')*k1)%26)+'A');
    for(int i=0;i<c.length();i++)
        c[i] = (char)((((c[i]-'A')+k2)%26)+'A');
    cout<<"Cipher text generated is: "<<c<<endl;

    cout<<"DECRYPTION"<<endl;
    string rc = c;
    for(int i=0;i<c.length();i++)
        rc[i] = (char)((((c[i]-'A')-k2+26)%26)+'A');
    int invk1 = ext_euclid(26, k1, 0, 1, 26);
    for(int i=0;i<rc.length();i++)
        rc[i] = (char)((((rc[i]-'A')*invk1)%26)+'A');
    cout<<"Plain Text is: "<<rc<<endl;


    return 0;
}
