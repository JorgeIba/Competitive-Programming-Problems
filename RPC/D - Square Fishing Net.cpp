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

const int MAXN = 105;

int M[MAXN][MAXN];
int rows[MAXN][MAXN];

int main () {
	fastIO();
	int s, n;
	cin >> s >> n;
	s++;
	forn(i, n){
		int x, y;
		cin >> x >> y;
		M[x][y]++;
	}
	forr(i, 1, 104){
		forr(j, 1, 104)
			rows[i][j] = M[i][j] + rows[i][j - 1];
	}
	int ans = 0;
	forr(j, 1, 104){
		if(j + s - 1 > 104) break;
		int aux = 0;
		forr(i, 1, 104){
			aux += rows[i][j + s - 1] - rows[i][j - 1];
			if(i - s > 0)
				aux -= rows[i - s][j + s - 1] - rows[i - s][j - 1];
			ans = max(ans, aux);
		}
	}
	cout << ans << endl;
	return 0;
}
