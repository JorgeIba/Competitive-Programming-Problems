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

/*
Parametric Self-Dual Simplex method
Solve a canonical LP:
	min or max: to_min 

	s.t: 
	A_i <= restr_i
	**A_i = a x_0 + b x_1 + ...
	x >= 0

*/

typedef vector<ld> Vec;
typedef vector<Vec> Mat;

const double eps = 1e-9, oo = numeric_limits<double>::infinity();

 
pair<Vec, ld> simplexMethodPD(Mat &A, Vec &restr, Vec &to_min, bool mini = true){
	int n = to_min.size(), m = restr.size();
	Mat T(m + 1, Vec(n + m + 1));
	vector<int> base(n + m), row(m);
 
	for(int j = 0; j < m; ++j){
		for(int i = 0; i < n; ++i)
			T[j][i] = A[j][i];
		row[j] = n + j;
		T[j][n + j] = 1;
		base[n + j] = 1;
		T[j][n + m] = restr[j];
	}
 
	for(int i = 0; i < n; ++i)
		T[m][i] = to_min[i] * (mini ? 1 : -1);
 
	while(true){
		int p = 0, q = 0;
		for(int i = 0; i < n + m; ++i)
			if(T[m][i] <= T[m][p])
				p = i;
 
		for(int j = 0; j < m; ++j)
			if(T[j][n + m] <= T[q][n + m])
				q = j;
 
		long double t = min(T[m][p], T[q][n + m]);
 
		if(t >= -eps){
			Vec x(n);
			for(int i = 0; i < m; ++i)
				if(row[i] < n) x[row[i]] = T[i][n + m];
			return {x, T[m][n + m] * (mini ? -1 : 1)}; // optimal
		}
 
		if(t < T[q][n + m]){
			// tight on to_min -> primal update
			for(int j = 0; j < m; ++j)
				if(T[j][p] >= eps)
					if(T[j][p] * (T[q][n + m] - t) >= T[q][p] * (T[j][n + m] - t))
						q = j;
 
			if(T[q][p] <= eps)
				return {Vec(n), oo * (mini ? 1 : -1)}; // primal infeasible
		}else{
			// tight on restr -> dual update
			for(int i = 0; i < n + m + 1; ++i)
				T[q][i] = -T[q][i];
 
			for(int i = 0; i < n + m; ++i)
				if(T[q][i] >= eps)
					if(T[q][i] * (T[m][p] - t) >= T[q][p] * (T[m][i] - t))
						p = i;
 
			if(T[q][p] <= eps)
				return {Vec(n), oo * (mini ? -1 : 1)}; // dual infeasible
		}
 
		for(int i = 0; i < m + n + 1; ++i)
			if(i != p) T[q][i] /= T[q][p];
 
		T[q][p] = 1; // pivot(q, p)
		base[p] = 1;
		base[row[q]] = 0;
		row[q] = p;
 
		for(int j = 0; j < m + 1; ++j){
			if(j != q){
				long double alpha = T[j][p];
				for(int i = 0; i < n + m + 1; ++i)
					T[j][i] -= T[q][i] * alpha;
			}
		}
	}
 
	return {Vec(n), oo};
}

int main () {
	//fastIO(); 
    lli n, p, q; cin>>n>>p>>q;

    Vec restr = {(ld)-p, (ld)-q};

    Mat functions(2, Vec(n));

    for(int i = 0; i<n; i++)
    {
        cin>>functions[0][i]>>functions[1][i];
        functions[0][i] *= -1;
        functions[1][i] *= -1;
    }

    Vec to_mini(n, 1);

    auto ans = simplexMethodPD(functions, restr, to_mini);

    /*
    for(auto x: ans.first) cout << x << " ";
    cout << endl;
    */

    cout << fixed << setprecision(10) << ans.second << endl;
    
	return 0;
}