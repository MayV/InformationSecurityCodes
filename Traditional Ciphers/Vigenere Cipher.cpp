#include<bits/stdc++.h>
using namespace std;

int main()
{
    string p;
    cout<<"Enter Plain text: ";
    cin>>p;
    string k;
    cout<<"Enter Key: ";
    cin>>k;

    cout<<"ENCRYPTION"<<endl;
    string c = p;
    int j = 0;
    for(int i=0;i<p.length();i++,j++)
    {
        if(j==k.length())
            j = 0;
        c[i] = (char)((((p[i]-'A')+(k[j]-'A'))%26)+'A');
    }
    cout<<"Cipher text: "<<c<<endl;

    cout<<"DECRYPTION"<<endl;;
    string rc = c;
    j = 0;
    for(int i=0;i<c.length();i++,j++)
    {
        if(j==k.length())
            j = 0;
        rc[i] = (char)((((c[i]-'A')-(k[j]-'A')+26)%26)+'A');
    }
    cout<<"Plain text: "<<rc<<endl;

    return 0;
}
