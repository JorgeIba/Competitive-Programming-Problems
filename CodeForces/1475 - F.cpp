#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;


struct TwoSAT{
	int n;
	vector<vector<int>> imp;

	TwoSAT(int n) : n(n), imp(2 * n) {}

	void add_edge(int u, int v){imp[u].push_back(v);}

	int neg(int u){return (n << 1) - u - 1;}

	void implication(int u, int v){
		add_edge(u, v);
		add_edge(neg(v), neg(u));
	}

    void disjunction(int u, int v) {
        add_edge(neg(u), v);
        add_edge(neg(v), u);
    }

    // xor
    void distinct(int u, int v) {
        disjunction(u, v);
        disjunction(neg(u), neg(v));
    }

    void same(int u, int v) {
        disjunction(u, neg(v));
        disjunction(neg(u), v);
    }


	vector<bool> solve(){
		int size = 2 * n;
		vector<int> S, B, I(size);

		function<void(int)> dfs = [&](int u){
			B.push_back(I[u] = S.size());
			S.push_back(u);

			for(int v : imp[u])
				if(!I[v]) dfs(v);
				else while (I[v] < B.back()) B.pop_back();

			if(I[u] == B.back())
				for(B.pop_back(), ++size; I[u] < SZ(S); S.pop_back())
					I[S.back()] = size;
		};

		for(int u = 0; u < 2 * n; ++u)
			if(!I[u]) dfs(u);

		vector<bool> values(n);

		for(int u = 0; u < n; ++u)
			if(I[u] == I[neg(u)]) return {};
			else values[u] = I[u] < I[neg(u)];

		return values;
	}
};




void main_(){
	int n; cin>>n;

    vector<string> mat1(n), mat2(n);

    for(auto &s: mat1) cin>>s;
    for(auto &s: mat2) cin>>s;

    TwoSAT *SAT = new TwoSAT(2*n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat1[i][j] == mat2[i][j]) {
                SAT->same(i, j + n);
            } else {
                SAT->distinct(i, j + n);
            }
        }
    }

    auto sol = SAT->solve();

    cout << (SZ(sol) ? "YES" : "NO") << endl;
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

