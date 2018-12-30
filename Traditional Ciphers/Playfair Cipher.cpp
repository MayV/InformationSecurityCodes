#include<bits/stdc++.h>
using namespace std;

int main()
{
    string p;
    cout<<"Enter Plain Text: ";
    cin>>p;
    string k[5] = {"LGDBA","QMHEC","URNJF","XVSOK","ZYWTP"};
    /*
    cout<<"Enter Key Matrix-"<<endl;
    for(int i=0;i<5;i++)
        cin>>k[i];
    */
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(k[i][j]=='I')
                k[i][j] = 'J';

    int ri[26];
    int ci[26];
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        {
            ri[k[i][j]-'A'] = i;
            ci[k[i][j]-'A'] = j;
        }

    cout<<"ENCRYPTION"<<endl;
    string newp = "";
    for(int i=0;i<p.length()-1;i++)
    {
        if(p[i]==p[i+1])
        {
            newp += p[i];
            newp += 'X';
        }
        else
        {
            newp += p[i];
            i++;
            newp += p[i];
        }
    }
    if(newp.length()%2!=0)
        newp += 'X';
    string c = newp;
    for(int i=0;i<newp.length();i+=2)
    {
        int j1 = newp[i]-'A';
        int j2 = newp[i+1]-'A';
        if(ri[j1]==ri[j2])
        {
            if(ci[j1]+1==5)
                c[i] = k[ri[j1]][0];
            else
                c[i] = k[ri[j1]][ci[j1]+1];
            if(ci[j2]+1==5)
                c[i+1] = k[ri[j2]][0];
            else
                c[i+1] = k[ri[j2]][ci[j2]+1];
        }
        else if(ci[j1]==ci[j2])
        {
            if(ri[j1]+1==5)
                c[i] = k[0][ci[j1]];
            else
                c[i] = k[ri[j1]+1][ci[j1]];
            if(ri[j2]+1==5)
                c[i+1] = k[0][ci[j2]];
            else
                c[i+1] = k[ri[j2]+1][ci[j2]];
        }
        else
        {
            c[i] = k[ri[j1]][ci[j2]];
            c[i+1] = k[ri[j2]][ci[j1]];
        }
    }
    cout<<"Cipher Text: "<<c<<endl;
}
