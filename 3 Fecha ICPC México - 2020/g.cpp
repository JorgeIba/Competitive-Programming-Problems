#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;
const int mxn = (int)1e5+10;
lli val[mxn], mem[mxn];
int n;
pii cam[mxn];
template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;
	//build from an array in O(n)
	SegmentTree(int N, vector<T> & arr): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];
		for(int i = N - 1; i > 0; --i)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
	}
	void update(int i, T value){
		ST[i += N] = value; //update the element accordingly
		while(i >>= 1)
			ST[i] = max(ST[i << 1], ST[i << 1 | 1]);
	}
	T query(int l, int r){
		T res = -1;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) {
				res = max(ST[l], res);
				l++;
			}
			if(!(r & 1)) {
				res = max(res, ST[r]);
				r--;
			}
		}
		//cout << "RES: " << res << '\n';
		return res;
	}
};
int main(){
	fastIO();
	cin >> n;
	forn(i,n) cin >> val[i] >> cam[i].fi >> cam[i].se;
	vi tr(2*n, 0);
	SegmentTree<int> st(2*n, tr);
	int aux;
	for(int i = n-1; ~i; i--){
		//cout << "L: " << i+cam[i].fi << ' ' << "R: " << i+cam[i].se << '\n';
		int maxi = st.query(i+cam[i].fi, i+cam[i].se);
		//cout << "Maxi: " << maxi << '\n';
		//cout << "val[i]: " << val[i] << '\n';
		aux = maxi + val[i];
		st.update(i, aux);
		//forn(j,2*n) cout << st.query(j,j) << ' '; cout << '\n';
	}
	int ans = -1;
	forn(i,n){
		ans = max(st.query(i,i), ans);
	}
	cout << ans << '\n';
	return 0;
}

