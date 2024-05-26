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



void add_equal(int x, int y, int c, TwoSAT *SAT) {
    int neg_x = SAT->neg(x), neg_y = SAT->neg(y);
    switch(c){
        case 0:
            SAT->disjunction(neg_x, neg_x);
            SAT->disjunction(neg_y, neg_y);
        break;

        case 1:
            SAT->disjunction(x, y);
            SAT->disjunction(neg_x, neg_y);
        break;

        case 2:
            SAT->disjunction(x, x);
            SAT->disjunction(y, y);
        break;
    }
}


void add_not_equal(int x, int y, int c, TwoSAT *SAT) {
    int neg_x = SAT->neg(x), neg_y = SAT->neg(y);
    switch(c){
        case 0:
            SAT->disjunction(x, y);
        break;

        case 1:
            SAT->disjunction(x, neg_y);
            SAT->disjunction(neg_x, y);
        break;

        case 2:
            SAT->disjunction(neg_x, neg_y);
        break;
    }
}




int main () {
	fastIO();
    lli n, m; cin>>n>>m;


    TwoSAT *SAT = new TwoSAT(n);

    bool flag_error = false;
    while(m--) {
        int x, y, c;
        string op;
        cin>>x>>y>>op>>c;

        if(op == "=") add_equal(x, y, c, SAT);
        else if(op == "!=") add_not_equal(x, y, c, SAT);
        else if(op == "<") {
            if(c == 0) flag_error = true;
            else if(c == 1) {
                add_equal(x, y, 0, SAT);
            } else {
                add_not_equal(x, y, 2, SAT);
            }
        } else if(op == ">") {
            if(c == 2) flag_error = true;
            else if(c == 1) {
                add_equal(x, y, 2, SAT);
            } else {
                add_not_equal(x, y, 0, SAT);
            }
        } else if(op == "<=") {
            if(c == 0) {
                add_equal(x, y, 0, SAT);
            }
            else if(c == 1) {
                add_not_equal(x, y, 2, SAT);
            } else {
                // add_not_equal(x, y, 2, SAT);
            }
        } else {
            if(c == 0) {

            }
            else if(c == 1) {
                add_not_equal(x, y, 0, SAT);
            } else {
                add_equal(x, y, 2, SAT);
            }
        }
    }

    auto sol = SAT->solve();
    // cout << SZ(sol) << " " << flag_error << endl;
    cout << (SZ(sol) && !flag_error ? "Yes" : "No") << endl;




	return 0;
}

