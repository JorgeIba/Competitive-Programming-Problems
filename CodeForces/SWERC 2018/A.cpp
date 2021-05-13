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

const int MAXN = 1e6 + 5;

int n,k,sum,ans,x;
bool A[MAXN];

int main () {
	fastIO();
	cin >> n >> k;
	fill(A,A+n+1,true);
	while(k--){
		cin >> x;
		for(int i=x; i<=n; i += x){
			if(A[i]) sum++;
			else sum--;
			A[i] = !A[i];
		}
		ans = max(ans,sum);
	}
	cout << ans << endl;
	return 0;
}
