#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli root, cnt = 0;

vector<lli> num(1000010);

struct query
{
    lli l, r, idx;
};

bool cmp(query a, query b)
{
    if( (int) a.l / root  ==  (int)b.l / root)
    {
        return a.r < b.r;
    }
    return a.l < b.l;
}

void add(lli i)
{
    num[i]++;
    if(num[i]==1)
    {
        cnt++;
    }
}

void del(lli i)
{
    num[i]--;
    if(num[i]==0)
    {
        cnt--;
    }
}


int main()
{
    fastIO();
    lli n; cin>>n;
    vector< lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli t; cin>>t;
    root = sqrt(n);
    vector< query > que(t);
    forn(i,0,t)
    {
        cin>>que[i].l>>que[i].r;
        que[i].idx = i;
    }
    sort(all(que), cmp);
    lli L = 0, R = -1;
    vector<lli> ans(t);
    forn(i,0,t)
    {
        lli l = que[i].l, r = que[i].r, id = que[i].idx;
        l--, r--;
        while(R < r)
        {
            add( nums[++R] );
        }
        while(L > l)
        {
            add( nums[--L] );
        }
        while(R > r)
        {
            del(nums[R--]);
        }
        while(L < l)
        {
            del(nums[L++]);
        }
        ans[id] = cnt;
    }

    for(auto x: ans)
    {
        cout<<x<<endl;
    }


    return 0;
}