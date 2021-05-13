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
    lli n; cin>>n;
    vector<lli> costs(n);
    for(auto &x: costs) cin>>x;


    lli poss_ans = INF, acum = 0, res_e = n, res_o = n, ans = INF;
    for(int i = 0; i<n; i++)
    {
        if(i % 2 == 0)
        {
            poss_ans = acum + res_e*costs[i]; //Usar todos los que me queda en ese wey
            acum += costs[i]; //Usar nomas uno alv
            res_e--;
        }
        else
        {
            poss_ans = acum + res_o*costs[i]; //Usar todos los que me queda en ese wey
            acum += costs[i]; //Usar nomas uno alv
            res_o--;
        }

        ans = min(poss_ans, ans);
    }
    cout << ans <<  endl;
} 


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();

	return 0;
}