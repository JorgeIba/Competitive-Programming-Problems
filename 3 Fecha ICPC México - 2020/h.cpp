#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;
 
typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

int n,g;
ld tot;
int P[25];

int get(int mask){
	ld sum = 0;
	forn(i,20){
		if((mask >> i) & 1)
			sum += P[i];
	}
	return floor((sum / tot) * 100);
}

int main () {
	fastIO();
	cin >> n >> g;
	forn(i,n){
		cin >> P[i];
		tot += P[i];
	}
	int mx = n;
	vi ans;
	forn(mask,1 << n){
		int bits = __builtin_popcount(mask);
		int aux = get(mask);
//		cout << aux << endl;
		if(aux >= g){
			if(bits < mx){
				mx = bits;
				ans.clear();
				ans.pb(mask);
			}
			else if(bits == mx)
				ans.pb(mask);
		}
	}
	cout << mx << ' ' << ans.size() << endl;
	forn(i,ans.size()){
		int mask = ans[i];
		cout << get(mask) << ' ';
		vi v;
		forn(j,20){
			if((mask >> j) & 1)
				v.pb(j+1);
		}
		forn(j,v.size()){
			cout << v[j];
			if(j+1 < v.size())
				cout << ' ';
		}
		cout << endl;
	}
	return 0;
}
