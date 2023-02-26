#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(ll a,ll b,ll *x,ll *y )
{
    if(b==0){
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1,y1;
    ll gc = gcd(b,a%b,&x1,&y1);
    *x = y1;
    *y = x1 - (a/b)*y1;
    return gc;
}

ll modPower(ll x,ll y,ll p){
    ll res=1;
    x=x%p;
    while(y>0){
        if(y&1)res=(res*x)%p;
        y=y>>1;x=(x*x)%p;
    }
    return res;
}
void encryption(ll e,ll n)
{
    ifstream in("message.txt");
    ofstream of("ciphertext.txt");
    string ss;
    while(getline(in,ss)){
            for(char m:ss){
                ll mm = m;
                ll val = modPower(mm,e,n);
                of<<val<<" ";
            }
    }
    cout<<"Encryption successfull"<<endl;
}

void decryption(ll d,ll n)
{
    ifstream in("ciphertext.txt");
    ofstream of("decrypted.txt");
    ll c;
    while(in>>c){
        ll plain = modPower(c,d,n);
        char plallext = char(plain);
        of<<plallext;
    }
    cout<<"Decryption successfully"<<endl;
}

int main()
{
    while(1){
        ll x,y,phi,e,p,q,d;
        cout<<"Enter p and q: "<<endl;
        cin>>p>>q;
        ll n = p*q;
        phi = (p-1)*(q-1);
        cout<<"PHI value "<<phi<<endl;
        cout<<"Enter the value of e:"<<endl;
        ll gc = 0;
        while(gc!=1){
            cin>>e;
            gc = gcd(e,phi,&x,&y);
            if(gc!=1)cout<<"e and phi are not co prime"<<endl;
        }
        d = ((x%phi)+phi)%phi;
        cout<<"Modular Inverse "<<d<<endl;
        cout<<"Private Key "<<e<<" "<<n<<endl;
        encryption(e,n);
        cout<<"Public key "<<d<<" "<<n<<endl;
        decryption(d,n);
        break;
    //    ll plallext = modPower(cipertext,d,n);
    //    cout<<plallext<<endl;
    }


    return 0;
}
