#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n, root;
vector<lli> BIT;

void update(lli idx, lli value)
{
    while(idx < BIT.size())
    {
        BIT[idx] += value;
        idx += idx&(-idx);
    }
}

lli sum(lli idx)
{
    lli res = 0;
    while(idx)
    {
        res += BIT[idx];
        idx -= idx&(-idx);
    }
    return res;
}

struct query
{
    lli l, r, idx;
};

bool compare(query a, query b)
{
    lli aux = a.l/root;
    if(aux != b.l/root) return a.l < b.l;
    if(aux&1) return a.r < b.r;
    return a.r > b.r;
}


map<lli,lli> mp;
lli cont=1;


int main()
{
    fastIO();
    cin>>n;
    root = sqrt(n + .0) + 1;
    BIT.resize(n+1);
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    //Mappeo
    vector<lli> aux = nums;
    sort(all(aux));
    for(auto x: aux)
    {
        if(mp[x]==0)
        {  
            mp[x] = cont++;
        }
    }
    for(auto &x: nums)
    {
        x = mp[x];
    }
    //Mamó el mappeo
    lli q; cin>>q;
    vector< query > que(q);
    for(int i = 0; i<q; i++)
    {
        cin>>que[i].l>>que[i].r;
        que[i].l--, que[i].r--;
        que[i].idx = i;
    }
    sort(all(que), compare);

    vector<lli> res(q);
    lli L = 0, R = -1, ans = 0;
    forn(i,0,q)
    {
        lli l = que[i].l, r = que[i].r, id = que[i].idx;
        while(R < r)
        {
            R++;
            update(nums[R], 1);
            ans += (sum(n) - sum(nums[R]));
        }
        while(L > l)
        {
            L--;
            update(nums[L], 1);
            ans += sum(nums[L]-1);
        }
        while(R > r)
        {
            update(nums[R], -1);
            ans -= (sum(n) - sum(nums[R]));
            R--;
        }
        while(L < l)
        {
            update(nums[L], -1);
            ans-= sum(nums[L]-1);
            L++;
        }
        res[id] = ans;
    }

    for(auto x: res)
    {
        cout<<x<<endl;
    }

    return 0;
}