#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;
using namespace __gnu_pbds;

typedef vector<lli> VLL;
typedef vector<int> VI;


template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


struct query{
    lli l, k, idx;
    query() {}
    query(lli l, lli k, lli idx): l(l), k(k), idx(idx) {}
};


vector<vector<query>> queries;
vector<vector<lli>> adjList;
vector<lli> colors;

ordered_set<pair<lli,lli>> st;


vector<lli> ans;

const lli maxA = 1e6+10;
lli fr[maxA];

const lli INF = 1e9;
void add(lli color)
{
    if(fr[color])
        st.erase({fr[color], color});

    fr[color]++;
    st.insert({fr[color], color});
}

void decrease(lli color)
{
    
    st.erase({fr[color], color});

    fr[color]--;
    if(fr[color])
        st.insert({fr[color], color});
}

void dfs(lli u)
{
    lli color = colors[u];
    add(color);


    for(auto q: queries[u])
    {
        lli l = q.l, k = q.k, i = q.idx;

        lli new_idx = st.order_of_key({l, -INF});
        if(new_idx + k >= SZ(st))
        {
            ans[i] = -1;
        }
        else
        {
            ans[i] = (*st.find_by_order(new_idx+k)).second;
        }    
    }


    for(auto v: adjList[u])
        dfs(v);

    decrease(color);
}


void solve()
{
    lli n, q; cin>>n>>q;
    colors.resize(n);
    for(auto &x: colors) cin>>x;

    adjList.clear();
    adjList.resize(n);
    for(int i = 1; i<n; i++)
    {
        lli p; cin>>p; p--;
        adjList[p].push_back(i); 
    }

    queries.clear();
    queries.resize(n);
    ans.resize(q);

    for(int i = 0; i<q; i++)
    {
        lli v, l, k; cin>>v>>l>>k; v--; k--;
        queries[v].push_back({l, k, i});
    }
    

    dfs(0);

    for(auto x: ans) cout << x << " ";
    cout << endl;
}



int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

