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


string invert(string a, int idx)
{
    for(int i = 0; i<(int)a.length(); i++)
    {
        if(i == idx) continue;
        if(a[i] == '1') a[i] = '0';
        else a[i] = '1';
    }
    return a;
}

const lli INF = 1e18;


void solve()
{
    lli n; cin>>n;
    string a, b; cin>>a>>b;

    lli up = 0, down = 0;
    for(int i = 0; i<n; i++)
    {
        if(a[i] != b[i])
        {
            if(a[i] == '1') up++;
            else down++;
        }
    }
    lli sol_1 = INF;
    if(up == down) sol_1 = up+down;


    string other_a;
    for(int i = 0; i<n; i++)
    {
        if(a[i] == '1' && b[i] == '1')
        {
            other_a = invert(a, i);
            break;
        }
    }



    up = 0, down = 0;
    for(int i = 0; i<n; i++)
    {
        if(other_a[i] != b[i])
        {
            if(other_a[i] == '1') up++;
            else down++;
        }
    }


    lli sol_2 = INF;
    if(up == down && other_a.length() > 0) sol_2 = 1 + up + down;

    lli ans = min(sol_1, sol_2);
    if(ans >= n+2) cout << -1 << endl;
    else cout << ans << endl;

}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

