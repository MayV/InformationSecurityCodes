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

void matrixMultiply(int N, int M[100][100], int invM[100][100])
{
    int temp[100][100];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            temp[i][j] = 0;
            for(int k=0;k<N;k++)
                temp[i][j] = (temp[i][j] + (M[i][k]*invM[k][j])%26)%26;
        }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<temp[i][j]<<" ";
        cout<<endl;
    }
}

int main()
{
    int N;
    cout<<"Enter N(less than 100): ";
    cin>>N;
    cout<<"Enter Matrix:"<<endl;
    int M[100][100];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            cin>>M[i][j];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            while(M[i][j]<0)
                M[i][j] = (M[i][j] + 26)%26;
    int invM[100][100];
    getmatrixinverse(N, M, invM);
    cout<<"Inverse of Matrix:"<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<invM[i][j]<<" ";
        cout<<endl;
    }
    //matrixMultiply(N, M, invM);
    return 0;
}

/*
3 5 7 2
1 4 7 2
6 3 9 17
13 5 4 16
*/
