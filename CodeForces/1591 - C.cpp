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
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    lli quitar = -1;
    vector<lli> pos, neg;
    for(auto x: nums)
    {
        if(x >= 0) pos.push_back(x);
        else neg.push_back(-x);
        quitar = max(quitar, abs(x));
    }

    sort(all(pos));
    sort(all(neg));

    lli ans = 0;
    for(int i = SZ(pos) - 1; i>=0; i -= k) 
        ans += pos[i];

    for(int i = SZ(neg) - 1; i>=0; i -= k) 
        ans += neg[i];

    cout << 2*ans - quitar << endl;
    return;
}


int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

