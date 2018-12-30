#include<bits/stdc++.h>
using namespace std;

int main()
{
    string p;
    cout<<"Enter Plain Text: ";
    cin>>p;
    int k;
    cout<<"Enter Key: ";
    cin>>k;

    cout<<"ENCRYPTION"<<endl;
    string c = p;
    c[0] = (char)((((p[0]-'A')+k)%26)+'A');
    for(int i=1;i<p.length();i++)
        c[i] = (char)((((p[i]-'A')+(p[i-1]-'A'))%26)+'A');
    cout<<"Cipher text is: "<<c<<endl;

    cout<<"DECRYPTION"<<endl;
    string rc = c;
    rc[0] = (char)((((c[0]-'A')-k+26)%26)+'A');
    for(int i=1;i<c.length();i++)
        rc[i] = (char)((((c[i]-'A')-(rc[i-1]-'A')+26)%26)+'A');
    cout<<"Plain text is: "<<rc<<endl;

    return 0;
}
