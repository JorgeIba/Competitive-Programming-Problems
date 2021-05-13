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

const lli INF = 1e18;


void solve()
{
    int n; cin>>n;
    map<lli,lli> fr;
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        fr[x]++;
    }

    map<lli,lli> fr2;

    for(auto x: fr) fr2[x.second]++;

    vector<pair<lli,lli>> frs;
    for(auto x: fr2) frs.push_back({x.first, x.second});

    
    sort(all(frs));
    int m = SZ(frs);

    vector<pair<lli,lli>> prefix_sum(m);
    for(int i = 0; i<m; i++)
    {
        prefix_sum[i].first = (i?prefix_sum[i-1].first:0) + frs[i].first * frs[i].second;
        prefix_sum[i].second = frs[i].first;
        //cout << frs[i].second << " " << frs[i].first << endl;
    }

    vector<lli> cuantos_mayores(m);
    for(int i = m-1; i>=0; i--)
    {
        cuantos_mayores[i] = (i<m-1?cuantos_mayores[i+1]:0) + frs[i].second;
    }

    lli ans = n;
    for(int i = 0; i<m; i++)
    {
        lli left = (i? prefix_sum[i-1].first: 0);
        lli right = prefix_sum[m-1].first - prefix_sum[i].first;
        lli sobra = (i<m-1? right - 1LL*prefix_sum[i].second*(cuantos_mayores[i+1]) : 0);
        //cout << prefix_sum[i].second << " " << left << " " << sobra << endl;
        ans = min(ans, left + sobra);
    }

    cout << ans << endl;
}


int main () {
	fastIO();
    int t; cin>>t;
    while(t--) solve();

	return 0;
}