#include<bits/stdc++.h>
using namespace std;

long long getinverse(long long a, long long m)
{
    long long r1 = m, r2 = a, t1 = 0, t2 = 1;
    while(r2>0)
    {
        long long q = r1/r2;
        long long r = (r1 - (q*r2)%m + m)%m;
        long long t = (t1 - (q*t2)%m +m)%m;
        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
    }
    return (t1+m)%m;
}

pair<long long, long long> addcoordinates(long long x1, long long y1, long long x2, long long y2, long long p)
{
    long long dy = (y2-y1+p)%p;
    long long dx = (x2-x1+p)%p;
    long long slope = (dy*getinverse(dx,p))%p;

    long long x3 = ((slope*slope)%p - x1 + p - x2 + p)%p;
    long long y3 = ((slope*((x1 - x3 + p)%p))%p - y1 + p)%p;

    pair<long long, long long> pr(x3, y3);
    return pr;
}

pair<long long, long long> addcoordinates(long long x1, long long y1, long long p, long long a)
{
    long long num = ((3*((x1*x1)%p))%p + a)%p;
    long long dem = getinverse((2*y1)%p, p);
    long long slope = (num*dem)%p;

    long long x3 = ((slope*slope)%p - x1 + p - x1 + p)%p;
    long long y3 = ((slope*((x1 - x3 + p)%p))%p - y1 + p)%p;

    pair<long long, long long> pr(x3, y3);
    return pr;
}

int main()
{
    long long p;
    cout<<"Enter prime number:";
    cin>>p;
    long long a, b;
    cout<<"Enter curve constants, a and b: ";
    cin>>a>>b;

    pair<long long, long long> pr;

    long long x1, y1;
    cout<<"Enter point on curve(e1): ";
    cin>>x1>>y1;

    long long d;
    cout<<"Enter d: ";
    cin>>d;
    ///Calculate e2
    long long x2, y2;
    pr = addcoordinates(x1, y1, p, a);
    x2 = pr.first;
    y2 = pr.second;
    for(int i=0;i<d-2;i++)
    {
        if(x2==x1 && y2==y1)
            pr = addcoordinates(x1, y1, p, a);
        else
            pr = addcoordinates(x2, y2, x1, y1, p);
        x2 = pr.first;
        y2 = pr.second;
    }
    cout<<"e2 = ("<<x2<<","<<y2<<")"<<endl;

    cout<<"Public Key: p = "<<p<<", e1 = ("<<x1<<","<<y1<<"), "<<"e2 = ("<<x2<<","<<y2<<")"<<endl;
    cout<<"Private Key: d = "<<d<<endl;


    cout<<"Encryption"<<endl;
    long Px, Py;
    cout<<"Enter Plain Text coordinates(should lie on the curve): ";
    cin>>Px>>Py;

    long long r;
    cout<<"Enter r: ";
    cin>>r;

    long long C1x, C1y, C2x, C2y;
    pr = addcoordinates(x1, y1, p, a);
    C1x = pr.first;
    C1y = pr.second;
    for(int i=0;i<r-2;i++)
    {
        if(C1x==x1 && C1y==y1)
            pr = addcoordinates(x1, y1, p, a);
        else
            pr = addcoordinates(C1x, C1y, x1, y1, p);
        C1x = pr.first;
        C1y = pr.second;
    }

    C2x = Px;
    C2y = Py;
    for(int i=0;i<r;i++)
    {
        if(C2x==x2 && C2y==y2)
            pr = addcoordinates(x2, y2, p, a);
        else
            pr = addcoordinates(C2x, C2y, x2, y2, p);
        C2x = pr.first;
        C2y = pr.second;
    }
    cout<<"C1 = ("<<C1x<<","<<C1y<<")"<<endl;
    cout<<"C2 = ("<<C2x<<","<<C2y<<")"<<endl;

    cout<<"DECRYPTION"<<endl;
    long long RCx, RCy;
    pr = addcoordinates(C1x, C1y, p, a);
    RCx = pr.first;
    RCy = pr.second;
    for(int i=0;i<d-2;i++)
    {
        if(RCx==C1x && RCy==C1y)
            pr = addcoordinates(C1x, C1y, p, a);
        else
            pr = addcoordinates(RCx, RCy, C1x, C1y, p);
        RCx = pr.first;
        RCy = pr.second;
    }
    RCy = p - RCy;
    if(RCx==C2x && RCy==C2y)
        pr = addcoordinates(C2x, C2y, p, a);
    else
        pr = addcoordinates(RCx, RCy, C2x, C2y, p);
    RCx = pr.first;
    RCy = pr.second;
    cout<<"Coordinates of Plain Text: ("<<RCx<<","<<RCy<<")"<<endl;
    return 0;
}
