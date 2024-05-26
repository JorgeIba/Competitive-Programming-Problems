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

typedef __int128 lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int MAXN = 5e5 + 5;

int n;
int nxt[MAXN][2];
/* long long int A[MAXN]; */

bool check(lli x, vector<long long int> A){
	forn(i, n){
		nxt[i][0] = (i - 1 + n) % n;
		nxt[i][1] = (i + 1) % n;
	}
	vi vis(n, 0);
	auto erase = [&](int i){
		int l = nxt[i][0];
		int r = nxt[i][1];
		nxt[l][1] = r;
		nxt[r][0] = l;
		vis[i] = true;
	};
	forn(i, n){
		if(vis[i]) continue;
		if(x < A[i]) continue;
		lli sum = x + A[i];
		int l, r;
		l = nxt[i][0];
		r = nxt[i][1];
		while(l != i){
			bool flg = false;
			if(A[l] <= sum){
				sum += A[l];
				erase(l);
				flg = true;
			}
			if(l != r && A[r] <= sum){
				sum += A[r];
				erase(r);
				flg = true;
			}
			if(!flg) break;
			l = nxt[i][0];
			r = nxt[i][1];
		}
		A[i] = sum - x;
	}
	int cnt = 0;
	forn(i, n)
		if(!vis[i])
			cnt++;
	return cnt == 1;
}

int main () {
	fastIO();
	cin >> n;
	vector<long long int> A(n);
	forn(i, n) cin >> A[i];
	long long l, r;
	l = 0, r = 1e13;
	while(l < r){
		lli m = (l + r) / 2;
		if(check(m, A))
			r = m;
		else
			l = m + 1;
	}
	cout << r << endl;
	return 0;
}

