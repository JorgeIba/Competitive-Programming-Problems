#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli calMEX(set<lli> MEX)
{
    for(int i = 1; ; i++)
    {
        if(MEX.find(i) == MEX.end())
        {
            return i;
        }
    }
}


int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    vector< vector<lli> > adj(n);

    for(int i = 0 ; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector< pair<lli,lli> > desire(n);
    for(int i = 0; i < n; i++)
    {
        lli x; cin>>x;
        desire[i] = {x,i};
    }
    sort(all(desire));
    vector<lli> res;
    vector<lli> value(n,0);
    for(int i = 0; i<n; i++)
    {
        pair<lli,lli> curr = desire[i];
        set<lli> MEX;
        for(auto v: adj[curr.second])
        {
            if(value[v] < curr.first)
            {
                MEX.insert(value[v]);
            }
            else
            {
                cout<<-1<<endl;
                return 0;
            }
        }
        res.push_back(curr.second+1);
        value[curr.second] = calMEX(MEX);
        if(value[curr.second] != curr.first)
        {
            //cout<< value[curr.second] <<" "<<curr.second<<" "<<curr.first<<endl;
            cout<<-1<<endl;
            return 0;
        }
    }
    for(auto x: res)
    {
        cout<<x<<" ";
    }
    cout<<endl;



    return 0;
}