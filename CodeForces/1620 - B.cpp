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
    lli w, h; cin>>w>>h;

    vector<lli> down, up, left, right;

    lli m; cin>>m;
    down.resize(m);
    for(auto &x: down) cin>>x;


    cin>>m;
    up.resize(m);
    for(auto &x: up) cin>>x;


    cin>>m;
    left.resize(m);
    for(auto &x: left) cin>>x;


    cin>>m;
    right.resize(m);
    for(auto &x: right) cin>>x;

    lli ans = 0;

    lli ans_down = (down.back() - down[0]) * h;
    lli ans_up =   (up.back() - up[0]) * h;
    lli ans_left = (left.back() - left[0]) * w;
    lli ans_right = (right.back() - right[0]) * w;

    ans = max({ans_down, ans_up, ans_left, ans_right});

    cout << ans << endl;



}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

