#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


lli root;

struct query
{
    lli l, r, idx;
};

bool compare(query a, query b)
{
    lli aux = a.l / root;
    if(aux != b.l / root) return a.l < b.l;
    if(aux & 1) return a.r < b.r;
    return a.r > b.r;
}

lli MAX = 10e5 + 10;


vector<lli> frequency(MAX);
lli contador = 0;

void add(lli n)
{
    if(n > MAX-1) return;
    if(frequency[n] + 1 == n)
    {
        //res.insert(n);
        contador++;
    }
    else if(frequency[n] == n)
    {
        //res.erase(n);
        contador--;
    }
    frequency[n]++;
}

void remove(lli n)
{
    if(n > MAX-1) return;
    if(frequency[n] - 1 == n)
    {
        //res.insert(n);
        contador++;
    }
    else if(frequency[n] == n)
    {
        //res.erase(n);
        contador--;
    }
    frequency[n]--;
}




int main()
{
    //fastIO();
    lli n, q; cin>>n>>q;
    root = sqrt(n + .0)+1;
    vector<lli> nums(n);
    for(auto &x: nums)
        cin>>x;

    vector< query > queries(q);
    for(int i = 0; i<q; i++)
    {
        cin>>queries[i].l>>queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].idx = i;
    }

    sort(all(queries), compare);
    lli L = 0, R = -1;
    vector<lli> ans(q);
    for(int i = 0; i<q; i++)
    {
        lli l = queries[i].l, r = queries[i].r, id = queries[i].idx;
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
            remove( nums[R--] );
        }
        while(L < l)
        {
            remove( nums[L++] );
        }
        ans[id] = contador;
        //cout<<res.size()<<endl;
    }
    for(auto x: ans)
    {
        cout<<x<<endl;
    }

    return 0;
}