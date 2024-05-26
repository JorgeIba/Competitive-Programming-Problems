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

bool is_sum(lli a, lli b, lli c){
	if(a == (b + c)) return true;
	if(b == (a + c)) return true;
	if(c == (a + b)) return true;
	return false;
}

bool is_prod(lli a, lli b, lli c){
	if(a == (b * c)) return true;
	if(b == (a * c)) return true;
	if(c == (a * b)) return true;
	return false;
}

int main () {
	fastIO();
	lli a,b,c;
	cin >> a >> b >> c;
	if(is_sum(a, b, c)) cout << 1 << endl;
	else if(is_prod(a, b, c)) cout << 2 << endl;
	else cout << 3 << endl;
	return 0;
}
