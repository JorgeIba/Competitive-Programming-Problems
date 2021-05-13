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

const int MAXN = 1e5 + 5;

int n;
lli b;
int A[MAXN];
lli ans[MAXN];
vpii v;

int main () {
	fastIO();
	cin >> n >> b;
	v.resize(n);
	forn(i,n){
		cin >> A[i];
		v[i] = {A[i],i};
	}
	sort(all(v));
	forn(i,n){
		int x,j;
		lli mx = 0;
		tie(x,j) = v[i];
		if(x == 0) continue;
		int l = (j-1+n) % n;
		int r = (j+1) % n;
		if(A[l] < A[j]) mx = max(mx,ans[l]);
		if(A[r] < A[j]) mx = max(mx,ans[r]);
		ans[j] = mx + 1;
	}
	forn(i,n){
		cout << ans[i] * b;
		if(i+1 < n)
			cout << ' ';
	}
	cout << endl;
	return 0;
}
