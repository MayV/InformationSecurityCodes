#include <bits/stdc++.h>
using namespace std;

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

long long knapsacksum(long long *A,long long *x,long long N)
{
	long long S=0;
	for(long long i=0;i<N;i++)
	{
		if(x[i])
			S+=A[i];
	}
	return S;
}

void inverseknapsack(long long S,long long *A,long long *x,long long N)
{
	for(long long i=N-1;i>=0;i--)
    {
        if(S>=A[i])
		{
			x[i]=1;
			S-=A[i];
		}
		else
			x[i]=0;
    }
}

int main()
{
	int P;
	cout<<"Enter Plain Text: ";
	cin>>P;

	long long len=7;
	long long temp[len];
	long long B[len]={7,11,23,43,87,173,357};
	long long n=1001;
	long long r=41;
	long long d=getinverse(r,n);
	for(long long i=0;i<len;i++)
		temp[i]=(B[i]*r)%n;
	long long A[len];
	long long permut[len]={4,2,5,3,1,7,6};
	for(long long i=0;i<len;i++)
		A[i]=temp[permut[i]-1];

    cout<<"Public Key: A = ";
    for(int i=0;i<len;i++)
        cout<<A[i]<<", ";
    cout<<endl;
    cout<<"Private key: d = "<<d<<", "<<"B = ";
    for(int i=0;i<len;i++)
        cout<<B[i]<<" ";
    cout<<endl;

    cout<<"ENCRYPTION"<<endl;
	long long num=P;
	long long x[len];
	for(long long i=0;i<len;i++,num/=2)
		x[i]=num%2;
	long long C=knapsacksum(A,x,len);
	cout<<"Cipher Text: "<<C<<endl;

    cout<<"DECRYPTION"<<endl;
	long long S=(C*d)%n;
	inverseknapsack(S,B,temp,len);
	long long y[len];
	for(long long i=0;i<len;i++)
		y[i]=temp[permut[i]-1];
	long long RC=0;
	long long mult=1;
	for(long long i=0;i<len;i++,mult*=2)
		if(y[i])
			RC+=mult;
	cout<<"Plain Text: "<<RC<<endl;
	return 0;
}
