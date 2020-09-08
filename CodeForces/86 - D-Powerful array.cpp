#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli root, cnt=0;

vector<lli> num(1000010);

struct query
{
    lli l, r, idx;
};

bool cmp(query a, query b)
{
    if( (int)a.l/root == (int)b.l/root)
    {
        return a.r < b.r;
    }
    return a.l < b.l;
}

int main()
{
    fastIO();
    lli n, t; cin>>n>>t;
    root = sqrt(n);
    vector<lli> nums(n);
    for(auto &x: nums)
        cin>>x;
    vector<query> q(t);
    forn(i,0,t)
    {
        cin>>q[i].l>>q[i].r;
        q[i].idx = i;
    }
    sort(all(q), cmp);
    vector<lli> ans(t);
    lli L = 0, R=-1;
    forn(i,0,t)
    {
        lli l = q[i].l, r = q[i].r, id = q[i].idx;
        l--, r--;
        while(R < r)
        {
            lli n = nums[++R];
            cnt += n*(2*num[n] + 1);
            num[n]++;
        }
        while(L > l)
        {
            lli n = nums[--L];
            cnt += n*(2*num[n] + 1);
            num[n]++;
        }
        while(R > r)
        {
            lli n = nums[R--];
            cnt -= n*(2*num[n]-1);
            num[n]--;
        }
        while(L < l)
        {
            lli n = nums[L++];
            cnt -= n*(2*num[n]-1);
            num[n]--;
        }
        ans[id] = cnt;
    }

    for(auto x: ans)
    {
        cout<<x<<endl;
    }

    return 0;
}