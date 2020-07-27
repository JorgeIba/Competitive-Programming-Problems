#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
using namespace std;
 
typedef long long unsigned ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvll;
typedef vector<ll> vll;
typedef vector<pii> vpii;

ll binPow(ll b, ll e, ll m){
	ll ans = 1;
	while(e){
		if(e & 1) ans = (ans*b) % m;
		b = (b*b) % m;
		e >>= 1;
	}
	return ans;
}


int main () {
	fastIO();
	ll a,b; cin >> a >> b;
	if(((a % 9)%9 == 0) || ((a%3)==0 && b > 1))
		cout << "9\n";
	else
    {
        ll res = binPow(a%9, b, 9);
        assert(res > 0);
        cout << binPow(a%9,b,9) << endl;
    }
		
	return 0;
}
