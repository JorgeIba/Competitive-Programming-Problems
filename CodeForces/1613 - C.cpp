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

vector<lli> secs;
lli n, h; 

bool check(lli k)
{
    lli damage = 0;
    for(int i = n-1; i>= 0; i--)
    {
        lli add = 0;
        if(i == n-1)
        {
            add += k;
        }
        else 
        {
            add += min(k, secs[i+1] - secs[i]);
        }
        damage += add;

        // cout << "Starting from: " << i << "-" << secs[i] << " I can deal " << add << " damage\n";

    }
    // cout << damage << endl;
    return damage >= h;
}



void solve()
{
    cin>>n>>h;
    secs.resize(n);
    for(auto &x: secs) cin>>x;

    // check(5);


    
    lli l = 1, r = 1e18+1, ans = -1;

    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }

    cout << ans << endl;
    
}




int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();

	


	return 0;
}

