#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adjList;
vector< lli > work;
vector< ld >  ST;
const lli maxN = 3*(1e5) + 10;
lli reach[maxN][2];
lli n;
lli cnt = 1;


void update(lli idx, lli x)
{
    idx += n;
    ST[idx] = log10(x);
    for(;idx>>1; idx>>=1)
    {
        ST[idx>>1] = ST[idx] + ST[idx^1];
    }
}

ld query(lli l, lli r)
{
    ld res = 0;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1) res = res+ST[l++];
        if(~r&1) res = res+ST[r--];
    }
    return res;
}


void dfs(lli u, lli p)
{
    reach[u][0] = cnt;
    work[cnt++] = u;
    for(auto v: adjList[u])
    {
        if(v!=p)
        {
            dfs(v, u);
        }
    }
    reach[u][1] = cnt-1;
}

void prep()
{
    adjList.resize(n+1);
    work.resize(n+1);
    ST.resize(2*(n+1), 0);
}

int main () {
	//fastIO();
    cin>>n;
    prep();
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs(1, -1);

    const ld eps = 1e-11;
    const lli maxAns = 1e9;
    cout << fixed << setprecision(12);
    lli q; cin>>q;
    while(q--)
    {
        lli t, x, y; cin>>t>>x>>y;
        if(t==1)
        {
            update(reach[x][0], y);
        }
        else
        {
            ld mul1 = query(reach[x][0], reach[x][1]);
            ld mul2 = query(reach[y][0], reach[y][1]);
            //cerr << (double)mul1 << " " << (double)mul2 << endl;
            ld ans = mul1 - mul2;
            if(ans >= 9)
            {
                cout << maxAns << endl;
            }
            else
            {
                cout << (long double)(pow(10, (long double)ans)) << endl;
            }
        }

    }


	return 0;
}