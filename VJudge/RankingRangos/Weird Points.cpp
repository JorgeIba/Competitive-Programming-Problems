#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

const lli MAX = 100010;

vector< pair<lli,lli> > points;
vector<lli> ST(2*MAX, 0);
map<lli,lli> mappeo;

bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    if(a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second < b.second;
}

void update(lli index)
{
    ST[index+=MAX] += 1;
    while(index>>1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
        index>>=1;
    }
}

lli query(lli r)
{
    r += MAX;
    lli res = 0;
    for(lli l = MAX; l<=r; l>>=1, r>>=1)
    {
        //cout<<l<<" "<<r<<endl;
        if(l&1)
        {
            res += ST[l++];
        }
        if(~r&1)
        {
            res += ST[r--];
        }
    }
    return res;
}


void solve()
{
    lli n, k; cin>>n>>k;
    mappeo.clear();
    ST.clear();
    ST.resize(2*MAX, 0);
    points.clear();
    points.resize(n);

    for(auto &x:points)
    {
        cin>>x.first>>x.second;
    }
    sort(points.begin(), points.end(), compare);
    lli contador = 1;
    for(auto &x:points)
    {
        if( mappeo.find( x.second  ) == mappeo.end() )
        {
            mappeo[x.second] = contador++;
        }
        x.second = mappeo[x.second];
    }
    sort(points.begin(), points.end());
    lli res = 0;
    for(auto x: points)
    {
        lli si = query(x.second);
        lli no = n-1 - si;
        lli diff = abs( si - no );
        if(diff >= k) res++;
        update(x.second);
    }
    cout<<res<<endl;
    

}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}