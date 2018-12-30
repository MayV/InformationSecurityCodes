#include<bits/stdc++.h>
using namespace std;

string initialPermutation(string s){

    int p[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
	string temp;
	for(int i=0;i<64;i++)
		temp+=s[p[i]-1];
	return temp;

}

string finalPermutation(string s){

    int p[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
	int invp[64];
	for(int i=0;i<64;i++)
		invp[p[i]-1]=i+1;

	string temp;
	for(int i=0;i<64;i++)
		temp+=s[invp[i]-1];
	return temp;
}


string keyGeneration(string Ckey, int x)
{
    ///Parity Drop
    string key;
    for(int i=0;i<64;i++)
        if(!(i==7 || i==15 || i==23 || i==31 || i==39 || i==47 || i==55 || i==63))
            key += Ckey[i];
    Ckey = key;
    int numberofShift[16];
	for(int i=0;i<16;i++)
    {
        if(i==0 || i==1 || i==8 || i==15)
			numberofShift[i]=1;
		else
			numberofShift[i]=2;
    }
    string L,R;
    for(int i = 0;i<56;i++)
    {
        if(i < 28)
            L += Ckey[i];
        else
            R += Ckey[i];
    }
    int actualShift = 0;
    for(int i=0;i<=x;i++)
        actualShift += numberofShift[i];
    for(int i = 0;i<actualShift;i++)
    {
        char temp = L[0];
        for(int i = 1;i<28;i++)
            L[i-1] = L[i];
        L[27] = temp;
        temp = R[0];
        for(int i = 1;i<28;i++)
            R[i-1] = R[i];
        R[27] = temp;
    }
    string temp1 = L+R;
    /// COMPRESSION P BOX
    int p[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    string temp2;
    for(int i = 0;i<48;i++){
        temp2 += temp1[p[i]-1];
    }
    return temp2;
}

string fiestelRound(string R,string K)
{
    ///EXPANSION
    string temp1;
    for(int i = 0;i<32;i+=4)
    {
        temp1 += R[(i-1+32)%32];
        for(int j = i;j<i+4;j++)
            temp1 += R[j];
        temp1 += R[(i+4)%32];
    }
    ///MIXER
    for(int i = 0;i<48;i++)
    {
        if(temp1[i] == K[i])
            temp1[i] = '0';
        else
            temp1[i] = '1';
    }
    ///8 S-BOX  (6*4)
    int sbox[4][16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,10,3,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};
    string temp2;
    for(int i = 0;i<48;i+=6)
    {
        int row = (temp1[i] - '0')*2 + (temp1[i+5] - '0');
        int col = (temp1[i+1] - '0')*8 + (temp1[i+2] - '0')*4 + (temp1[i+3] - '0')*2 + (temp1[i+4] - '0');
        int ans = sbox[row][col];
        string x;
        while(ans > 0)
        {
            x = (char)(ans%2 + '0') + x;
            ans /=2;
        }
        while(x.size() < 4)
        {
            x = '0' + x;
        }
        temp2 += x;
    }
    /// STRAIGHT P-BOX
    int p[32]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
    string temp3;
    for(int i = 0;i<32;i++)
        temp3 += temp2[p[i] - 1];
    return temp3;
}

void desFunc(string P, string Ckey)
{
    cout<<"\n \n";

    cout<<"ENCRYPTION"<<endl;
    P = initialPermutation(P);
    cout<<"After Initial Permutation: "<<P<<endl;
    for(int i = 0;i<16;i++)
    {
        string key = keyGeneration(Ckey,i);
        string L,R;
        for(int i = 0;i<64;i++){
            if(i < 32)
                L += P[i];
            else
                R += P[i];
        }
        string temp = fiestelRound(R,key);
        for(int i = 0;i<32;i++)
        {
            if(L[i] == temp[i])
                L[i] = '0';
            else
                L[i] = '1';
        }
        if(i != 15)
            swap(L,R);
        P = L + R;
        cout<<"After Round "<<i+1<<" "<<P<<endl;
    }
    P = finalPermutation(P);
    cout<<"After Final Permutation : "<<P<<endl;

    cout<<"\n\n";

    cout<<"DECRYPTION"<<endl;
    P = initialPermutation(P);
    cout<<"After Initial Permutation: "<<P<<endl;
    for(int i = 0;i<16;i++){
        string key = keyGeneration(Ckey,15-i);
        string L,R;
        for(int i = 0;i<64;i++){
            if(i < 32)
                L += P[i];
            else
                R += P[i];
        }
        string temp = fiestelRound(R,key);
        for(int i = 0;i<32;i++)
        {
            if(L[i] == temp[i])
                L[i] = '0';
            else
                L[i] = '1';
        }
        P = L + R;
        cout<<"After Round "<<i+1<<" "<<P<<endl;
        if(i != 15)
            swap(L,R);
        P = L + R;
    }
    P = finalPermutation(P);
    cout<<"After Final Permutation : "<<P<<endl;
}

int main()
{
    string P;
    cout<<"ENTER PLAIN TEXT (64 bits) : ";
    cin>>P;
    string Ckey;
    cout<<"Enter Cipher Key (64 bits) : ";
    cin>>Ckey;
    desFunc(P,Ckey);
}

/*
1111010101001101110101010010101101010100010101010111110101110000
1010000101001001011110000111110000110101111110000000000001111001
*/
