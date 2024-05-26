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
#define var(x) #x << " = " << x

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

int main () {
	fastIO();
	string a, b;
	cin >> a >> b;
	reverse(all(a));
	reverse(all(b));
	while(SZ(a) < SZ(b)) a.pb('0');
	while(SZ(b) < SZ(a)) b.pb('0');
	string ans;
	forn(i, SZ(a)){
		if((a[i] <= '2' && b[i] <= '2') || (a[i] >= '7' && b[i] >= '7'))
			ans.pb('0');
		else
			ans.pb('9');
	}
	reverse(all(ans));
	cout << ans << endl;
	return 0;
}
