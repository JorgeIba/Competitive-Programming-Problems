#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

map<lli,lli> mapping;
vector<lli> ST;
lli n;
lli MAX = 100010;

bool compare( pair<lli,lli> a, pair<lli,lli> b )
{
    if (a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second < b.second;
}

void update(lli index)
{
    ST[ index += MAX ] += 1;
    while(index>>1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
        index >>= 1;
        
    }
}

lli query(lli l, lli r)
{
    lli res = 0;
    for(l += MAX, r += MAX; l<=r; l>>=1, r>>=1)
    {
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
    lli k; cin>>n>>k;
    ST.clear();
    mapping.clear();
    ST.resize(2*MAX, 0);
    vector< pair<lli, lli> > nums(n);
    for(auto &x: nums)
    {
        cin>>x.first>>x.second;
    }
    sort(nums.begin(), nums.end(), compare);
    lli cont = 1;
    for(auto &x: nums)
    {
        if( mapping.find(x.second) == mapping.end()  )
        {
            mapping[x.second] = cont++;
        }
        x.second = mapping[x.second];
    }
    sort(nums.begin(), nums.end());
    lli res = 0;
    for(auto x: nums)
    {
        lli aux = query(0, x.second);
        aux = abs(aux - (n-1-aux));
        //cout<<x.second<<" "<<query(0, x.second)<<endl;
        
        if(aux >= k)
        {
            res ++;
        }
        //cout<<x.second<<" ";
        update(x.second);
        /*
        for(auto y: ST)
        {
            cout<<y<<" ";
        }
        cout<<"asdasdasdasd\n";
        */
    }
    cout<<res<<endl;

}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}