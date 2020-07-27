#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MAXN = 1e5+10;
int fr[MAXN];
lli root;

vector<lli> BIT(MAXN+1);

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
    lli l, r, limitL, limitR, idx;
};

bool compare(query a, query b)
{
    lli aux = a.l/root;
    if(aux != b.l/root) return a.l < b.l;
    if(aux & 1) return a.r < b.r;
    return a.r > b.r;
}

int main()
{
    fastIO();
    lli n, q; cin>>n>>q;
    root = sqrt(n + .0) + 1;
    vector<lli> nums(n);
    vector<query> que(q);
    for(auto &x: nums)
    {
        cin>>x;
    }

    forn(i,0,q)
    {
        cin>>que[i].l>>que[i].r>>que[i].limitL>>que[i].limitR;
        que[i].idx = i;
        que[i].l--;
        que[i].r--;
    }
    sort(all(que), compare);
    vector<lli> res(q);
    lli L = 0, R = -1, ans = 0;
    forn(i,0,q)
    {
        lli l = que[i].l, r = que[i].r, id = que[i].idx, limitL = que[i].limitL, limitR = que[i].limitR;
        while(R < r)
        {
            R++;
            fr[ nums[R] ]++;
            if(fr[ nums[R] ] == 1)
            {
                update(nums[R], 1);
            }

            //ans += (sum(limitR) - sum(limitL - 1));
        }
        while(L > l)
        {
            L--;
            fr[nums[L]]++;
            if(fr[nums[L]] == 1)
            {
                update(nums[L], 1);
            }            
            //ans += (sum(limitR) - sum(limitL - 1));
        }
        while(R > r)
        {
            //remove(nums[R--]);
            fr[nums[R]]--;
            if(fr[nums[R]] == 0)
            {
                update(nums[R], -1);
            }
            R--;
            //ans -= (sum(limitR) - sum(limitL - 1));
        }
        while(L < l)
        {
            fr[nums[L]]--;
            if(fr[nums[L]] == 0)
            {
                update(nums[L], -1);
            }
            L++;
            //ans -= (sum(limitR) - sum(limitL - 1));
        }
        res[id] = (sum(limitR) - sum(limitL - 1));
    }

    for(auto x: res)
    {
        cout<<x<<endl;
    }
    
    
    
    return 0;
}