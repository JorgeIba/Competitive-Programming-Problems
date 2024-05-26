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
	int t;
	cin >> t;
	while(t--){
		lli py, pl, vy, vl;
		cin >> py >> pl >> vy >> vl;
		if(py <= pl)
			cout << min(py * vy, pl * vl) << endl;
		else
			cout << min({py * vy, (py - pl) * vy + pl * vl, (py - pl) * vl + py * vl}) << endl;
	}
	return 0;
}

