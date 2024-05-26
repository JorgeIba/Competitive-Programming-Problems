#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


template<typename T>
pair<T, vector<int>> hungarian(const vector<vector<T>> & a){
	int n = a.size(), m = a[0].size();
	assert(n <= m);
	vector<int> ans(n), pa(n+1, -1), pb(m+1, -1), way(m, -1);
	vector<T> minv(m), u(n+1), v(m+1);
	vector<bool> used(m+1);
	T inf = numeric_limits<T>::max();
	for(int i = 0; i < n; ++i){
		fill(minv.begin(), minv.end(), inf);
		fill(used.begin(), used.end(), false);
		pb[m] = i;
		pa[i] = m;
		int j0 = m;
		do{
			used[j0] = true;
			int i0 = pb[j0];
			T delta = inf;
			int j1 = -1;
			for(int j = 0; j < m; ++j){
				if(used[j]) continue;
				T cur = a[i0][j] - u[i0] - v[j];
				if(cur < minv[j]){
					minv[j] = cur;
					way[j] = j0;
				}
				if(minv[j] < delta){
					delta = minv[j];
					j1 = j;
				}
			}
			for(int j = 0; j <= m; ++j){
				if(used[j]){
					u[pb[j]] += delta;
					v[j] -= delta;
				}else{
					minv[j] -= delta;
				}
			}
			j0 = j1;
		}while(pb[j0] != -1);
		do{
			int j1 = way[j0];
			pb[j0] = pb[j1];
			pa[pb[j0]] = j0;
			j0 = j1;
		}while(j0 != m);
	}
	for(int i = 0; i < n; ++i)
		ans[pb[i]] = i;
	return {-v[m], ans};
}


void solve(){
    int n, k; cin>>n>>k;

    vector< pair<int,int> > minions(n);
    for(auto &[a, b]: minions) cin>>a>>b;


    vector< vector<int> > costs(n, vector<int>(n));

    // k = 5

    // 0 1 2 3 4 5 6 7 8 9

    for(int i = 0; i < n; i++) {
        auto [a, b] = minions[i];
        for(int j = 0; j < k; j++) {
            costs[i][j] = -(a + j*b);
        }
        for(int j = k; j < n; j++) {
            costs[i][j] = -((k-1)*b);
        }
    }

    auto [cost, assigns] = hungarian(costs);


    int left = n - k;
    cout << k + 2*left << endl;

    vector<int> ans = assigns;
    for(int i = 0; i < n; i++) {
        int where = assigns[i];
        ans[where] = i;
    }

    for(int i = 0; i < k-1; i++){
        cout << ans[i] + 1 << " ";
    }

    for(int i = k; i < n; i++) {
        cout << ans[i] + 1 << " " << -(ans[i] + 1) << " ";
    }
    for(int i = k-1; i < k; i++) {
        cout << ans[i]+1;
    }
    cout << endl;

}


int main () {
	fastIO();
	
	int t; cin>>t;

    while(t--) solve();


	return 0;
}
