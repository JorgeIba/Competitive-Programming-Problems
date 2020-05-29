#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#define int int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
using namespace __gnu_pbds;
typedef tree< int , null_type, less< int >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

vector<int> nums;
vector<ordered_set> blocks;

int n, S;



void update(int value, int idx)
{
    int k = idx / S;
    blocks[k].erase( nums[idx] );
    nums[idx] = value;
    blocks[k].insert( value );
}

int query(int l, int r, int c)
{
    int L = l/S, R = r/S, res = 0;
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
            int low = blocks[i].order_of_key(c);
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
    //fastIO();
    cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
    cin>>n;
    S = sqrt(n) + 1;

    nums.resize(n);
    blocks.resize(S);
    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
        blocks[i/S].insert(nums[i]);
    }
    int q; cin>>q;
    while(q--)
    {
        int t; cin>>t;
        if(!t)
        {
            int l, r, v; cin>>l>>r>>v;
            cout<<query(l-1,r-1,v)<<endl;
        }
        else
        {
            int idx, value; cin>>idx>>value;
            update(value, idx-1);
        }
    }
    
    return 0;
}
