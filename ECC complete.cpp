#include <bits/stdc++.h>
using namespace std;

using ll=long long;

#define RHS(x) (x*x*x + a*x + b)%p
#define LHS(x) (x*x)%p


struct Point
{
    ll x;
    ll y;
};


long long a,b,p;
Point G;
map<char,Point> c2p;



vector<ll> ex_gcd(ll a, ll b)
{
    if(b==0)
    {
        return {1,0,a};
    }
    auto ret = ex_gcd(b,a%b);
    ll x1 = ret[0];
    ll y1 = ret[1];

    return {y1,x1-(a/b)*y1, ret[2]};
}


vector<Point> gen_affine_point()
{
    vector<Point> ret;
    for(ll i=0; i<p; i++)
    {
        for(ll j=0; j<p; j++)
        {
            if(LHS(j) ==RHS(i))
            {
                ret.push_back({i,j});
            }
        }
    }
    return ret;
}

Point doubling(Point x)
{
    if(x.y==0) return {-1,-1};
    long long s = ((((3*x.x*x.x + a) * ex_gcd(2*x.y,p)[0]) % p)+p)%p;

    long long x2 = (((s*s)%p) -((2*x.x)%p) + p)%p;
    long long y2 = (((s*(x.x-x2))%p - (x.y%p))%p+p)%p;
    return {x2,y2};
}
Point addition(Point x, Point y)
{
    if(x.x==y.x && x.y==y.y) return doubling(x);
    if(y.x-x.x==0) return {-1,-1};
    long long s = ((((y.y - x.y)*ex_gcd(((y.x-x.x)%p +p)%p,p)[0])%p)+p)%p;

    long long x2 = ((((s*s)-x.x-y.x)%p)+p)%p;
    long long y2 = (((s*(x.x-x2)-x.y)%p)+p)%p;


    return {x2,y2};
}

vector<Point> gen_subgroup(Point G, int n=INT_MAX)
{
    vector<Point> ret;
    ret.push_back(G);
    int i=0;
    while(i++<n)
    {
        auto g2 = addition(G,ret.back());
        ret.push_back(g2);

        if(g2.x==-1 && g2.y==-1)
        {
            return ret;
        }
    }
    return ret;
}


vector<pair<Point,Point>> encrypt(string& source, Point PUb)
{
    transform(source.begin(),source.end(),source.begin(),::toupper);

    ll k = 2;
    auto sub_G = gen_subgroup(G,k);
    auto sub_PUb = gen_subgroup(PUb,k);
    vector<pair<Point,Point>> ret;

    for(auto ch: source)
    {
        auto Pm = c2p[ch];
        ret.push_back({sub_G[k-1],addition(Pm,sub_PUb[k-1])});
    }

    return ret;
}

string decrypt(vector<pair<Point,Point>> chifer, ll PRb)
{
    string decrypted_text;

    for(auto Pcc : chifer)
    {
        Point kG = Pcc.first;
        Point Pc = Pcc.second;
        auto sub_kG = gen_subgroup(kG,PRb);

        Point sk = sub_kG[PRb-1];
        sk.y=p-sk.y;

        Point Pm = addition(Pc,sk);
        for(char i='A' ; i<='U' ; i++)
        {
            if(c2p[i].x==Pm.x && c2p[i].y == Pm.y)
            {
                decrypted_text+=i;
                break;
            }
        }
    }

    return decrypted_text;
}

int main()
{

    cout<<"Enter [ p a b ] of the Elliptic Curve Ep(a,b): ";
    cin>>p>>a>>b;
    cout<<"Enter [ x y ] of the Generation Point: ";
    cin>>G.x>>G.y;

    auto sub_G = gen_subgroup(G);

//    if(sub_G.size()<26)
//    {
//        cout<<"Subgroup does not have 26 point\n";
//        return 0;
//    }

    string source,decrypted_source;
    vector<pair<Point,Point>> chifer;


    ll PRa = 3, PRb = 10;
//    cout<<"Enter Private Key of \'A\': ";
//    cin>>PRa;
//    cout<<"Enter Private Key of \'B\': ";
//    cin>>PRb;

    Point PUa = sub_G[PRa-1], PUb = sub_G[PRb-1];

    for(char i = 'A' ; i<='U' ; i++)
    {
        c2p[i] = sub_G[i-'A'];
    }

    cout<<"\nEnter the massage: " ;
    cin>>source;


    chifer= encrypt(source,PUb);

    cout<<"\n"<<"Massage: "<<source<<"\n";

    cout<<"\nEncrypted Massage in pair of Point:\n";
    for(auto x: chifer)
    {
        cout<<"{"<<x.first.x<<", "<<x.first.y<<"}, {"<<x.second.x<<", "<<x.second.y<<"}\n";
    }

    decrypted_source = decrypt(chifer,PRb);

    cout<<"\n"<<"Decrypted Massage: "<<decrypted_source<<"\n\n";


    return 0;

}

