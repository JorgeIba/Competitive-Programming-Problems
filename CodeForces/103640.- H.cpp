#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

//Given a n*m cost matrix (n<=m), it finds a minimum cost assignment.
//The actual assignment is in the vector returned.
//To find the maximum, negate the values and the answer.
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

const lli maxN = 505;
lli mat[maxN][maxN];



int main () {
	fastIO();
    lli n; cin>>n;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin>>mat[i][j];
        }
    }
    
    
    vector< vector<lli> > cost((n+1)/2, vector<lli>((n+1)/2));

    for(int i = 0, j = 0; i < n; i+=2, j++) {
        for(int k = 1, l = 0; k <= n; k+=2, l++) {
            lli before = k - 2 >= 1 ? mat[i][k-2] : 0;
            lli after = k < n ? mat[i][k] : 0;
            cost[j][l] = before + after; 
        }
    }


    auto ans = hungarian(cost);

    cout << ans.first << endl;




	return 0;
}

