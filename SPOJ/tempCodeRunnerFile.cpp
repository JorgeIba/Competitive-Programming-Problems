#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
using namespace __gnu_pbds;
typedef tree< lli , null_type, less< lli >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

vector<lli> nums;
vector<ordered_set> blocks;

lli n, S;


void build()
{
    for(int i = 0; i<n; i++)
    {
        blocks[ (int) i/S ].insert(nums[i]) ;
    } 
}

void update( lli idx, lli value)
{
    lli k = idx / S;
    blocks[k].erase( nums[idx] );
    nums[idx] = value;
    blocks[k].insert( value );
}


lli query(lli l, lli r, lli c)
{
    lli L = l/S, R = r/S, res = 0;
    if(L==R)
    {
        for(int i = l; i <= r; i++)
        {
            if(nums[i] >= c)
            {
                res++;
            }
        }
    }
    else
    {
        for(int i = l, end = (L+1)*S - 1; i<=end; i++)
        {
            if(nums[i] >= c)
            {
                res++;
            }
        }
        for(int i = L + 1; i<=R-1; i++)
        {
            lli low = blocks[i].order_of_key(c);
            res += (blocks[i].size() - low);
        }
        for(int i = R*S; i<=r ; i++)
        {
            if(nums[i] >= c)
            {
                res++;
            }
        }
    }
    return res;
}


int main()
{
    fastIO();
    lli n; cin>>n;
    nums.resize(n);
    S = sqrt(n) + 1;
    blocks.resize(S);
    for(auto &x: nums)
        cin>>x;
    build();
    lli q; cin>>q;
    while(q--)
    {
        lli t; cin>>t;
        if(t==0)
        {
            lli l, r, v; cin>>l>>r>>v;
            cout<<query(l-1,r-1,v)<<endl;
        }
        else
        {
            lli idx, value; cin>>idx>>value;
            update(idx-1, value);
        }
    }
    
    return 0;
}