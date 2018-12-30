#include<bits/stdc++.h>
using namespace std;

int getinverse(int a, int m)
{
    int r1 = m, r2 = a, t1 = 0, t2 = 1;
    while(r2>0)
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

void getcofactors(int N, int M[100][100], int temp[100][100], int r, int c)
{
    int cr = 0, cc = 0;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(i==r)
                continue;
            else if(j==c)
                continue;
            temp[cr][cc] = M[i][j];
            cc++;
            if(cc==N-1)
            {
                cr++;
                cc = 0;
            }
        }
}

int getdeterminant(int N, int M[100][100])
{
    if(N==1)
        return M[0][0];
    int temp[100][100];
    int D = 0;
    for(int j=0;j<N;j++)
    {
        getcofactors(N, M, temp, 0, j);
        int sign = 1;
        if((0+j)%2==0)
            sign = 1;
        else
            sign = -1;
        D = (D+(sign*((M[0][j]*getdeterminant(N-1, temp))%26) + 26)%26)%26;
    }
    return D;
}

void getadjoint(int N, int M[100][100], int adjM[][100])
{
    int temp[100][100];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            getcofactors(N, M, temp, i, j);
            int sign;
            if((i+j)%2==0)
                sign = 1;
            else
                sign = -1;
            adjM[j][i] = (sign*getdeterminant(N-1, temp) + 26)%26;
        }
}

int getgcd(int a, int b)
{
    if(b==0)
        return a;
    return getgcd(b, a%b);
}

void getmatrixinverse(int N, int M[100][100], int invM[100][100])
{
    int temp[100][100];
    int D = getdeterminant(N, M);
    if(D==0 || getgcd(D,26)!=1)
    {
        cout<<"Inverse does not exits."<<endl;
        exit(1);
    }
    int invD = getinverse(D, 26);
    getadjoint(N, M, invM);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            invM[i][j] = (invD*invM[i][j])%26;
}

int main()
{
    int m = 4;
    int K[100][100] = {9,7,11,13,4,7,5,6,2,21,14,9,3,23,21,8};
    string p;
    cout<<"Enter Plain Text: ";
    cin>>p;
    cout<<"ENCRYPTION"<<endl;
    int row = (int)ceil(double(p.length())/m);
    int P[row][m];
    int ctr = 0;
    for(int i = 0;i<row;i++)
        for(int j = 0;j<m;j++)
        {
            if(ctr<p.length())
                P[i][j] = p[ctr++] - 'A';
            else
            {
                P[i][j] = 'Z' - 'A';
            }
        }
    int C[row][m];
    for(int i = 0;i<row;i++)
        for(int j = 0;j<m;j++)
        {
            C[i][j] = 0;
            for(int k = 0;k<m;k++)
                C[i][j] = (C[i][j] + (P[i][k] * K[k][j])%26)%26;
        }
    string c;
    for(int i = 0;i<row;i++)
        for(int j = 0;j<m;j++)
            c += (char)(C[i][j] + 'A');
    cout<<"Cipher Text: "<<c<<endl;
    //Decryption only work for square matrix;
    cout<<"DECRYPTION"<<endl;
    int Kinv[100][100];
    getmatrixinverse(m, K, Kinv);
    int RC[row][m];
    for(int i = 0;i<row;i++)
        for(int j = 0;j<m;j++)
        {
            RC[i][j] = 0;
            for(int k = 0;k<m;k++)
                RC[i][j] = (RC[i][j] + (C[i][k] * K[k][j])%26)%26;
        }
    string rc;
    for(int i = 0;i<row;i++)
        for(int j = 0;j<m;j++)
            rc += (char)(RC[i][j] + 'A');
    cout<<"Plain Text: "<<rc<<endl;
}
