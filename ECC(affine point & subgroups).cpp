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
            if(LHS(j) == RHS(i))
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

int main()
{

    cout<<"Enter [ p a b ] of the Elliptic Curve Ep(a,b): ";
    cin>>p>>a>>b;

    auto aff = gen_affine_point();

    cout<<"Number of Affine Points: "<<aff.size()<<endl;
    for(int i=0; i<aff.size(); i++)
    {
        cout<<aff[i].x<<" "<<aff[i].y<<endl;
    }
    cout<<"\nEnter [ x y ] of the Generation Point: ";
    cin>>G.x>>G.y;

    auto sub_G = gen_subgroup(G);
    cout<<"Sub groups: "<<endl;
    for(int i=0; i<sub_G.size(); i++)
    {
        cout<<sub_G[i].x<<" "<<sub_G[i].y<<endl;
    }
}





