#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


void solve()
{
    lli n, k; cin>>n>>k;
    vector<vector<lli>> adjList(n);
    vector<lli> incoming(n);
    vector<lli> ans_in_time(n, n);

    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        incoming[u]++, incoming[v]++;
    }

    ans_in_time[0] = n;


    vector<lli> time_is_deleted(n);
    queue<lli> q;
    for(int i = 0; i<n; i++)
    {
        if(incoming[i] == 1)
        {
            q.push(i);
            time_is_deleted[i] = 1;
        }
    }



    while(!q.empty())
    {
        lli u = q.front(); q.pop();
        for(auto v: adjList[u])
        {
            incoming[v]--;
            if(incoming[v] == 1)
            {
                time_is_deleted[v] = time_is_deleted[u] + 1;
                q.push(v);
            }
        }
    }

    vector<lli> prefix_sum(n);    
    for(auto x: time_is_deleted) prefix_sum[x]++;

    partial_sum(all(prefix_sum), prefix_sum.begin() );

    for(int i = 0; i<n; i++) ans_in_time[i] -= prefix_sum[i];

    if(k >= n) cout << 0 << endl;
    else cout << ans_in_time[k] << endl;
    return;
}



int main () {
	fastIO();
    lli t; cin>>t;
    
    while(t--) solve();

	return 0;
}

