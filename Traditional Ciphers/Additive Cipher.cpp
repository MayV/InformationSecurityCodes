#include<bits/stdc++.h>
using namespace std;

int main()
{
    string p;
    cout<<"Enter Plain text: ";
    cin>>p;
    int k;
    cout<<"Enter Key: ";
    cin>>k;

    cout<<"ENCRYPTION"<<endl;
    string c = p;
    for(int i=0;i<p.length();i++)
        c[i] = (char)((((p[i]-'A')+k)%26)+'A');
    cout<<"Cipher text is: "<<c<<endl;

    cout<<"DECRYPTION"<<endl;
    string rc = c;
    for(int i=0;i<c.length();i++)
        rc[i] = (char)((((c[i]-'A')-k+26)%26)+'A');
    cout<<"Plain text is: "<<rc<<endl;

    return 0;
}
