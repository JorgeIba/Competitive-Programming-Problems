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


int triangle(int n){ return n*(n+1) / 2; }
int square(int n){   return n*n;         }
int penta(int n){    return n*(3*n-1)/2; }
int hexa(int n){     return n*(2*n-1);   }
int hepta(int n){    return n*(5*n-3)/2; }
int octa(int n){     return n*(3*n-2);   }

const int K = 6;

map< string, vector<string> > prefixes[K];
vector< function<int(int)> > funs = {triangle, square, penta, hexa, hepta, octa};

int main () {
	//fastIO();
    
    for(int n = 1; n <= 150; n++){
        forn(j, K){
            auto x = funs[j](n);
            string xs = to_string(x);
            if(SZ(xs) == 4) {
                string pref = xs.substr(0, 2);
                prefixes[j][pref].push_back(xs);
            }
        }
    }

    vector<string> ans_v;
    auto dfs = [&](const auto &dfs, string curr, string start, int checked){
        auto pref = curr.substr(0, 2);
        auto suff = curr.substr(2, 2);
        auto pref_start = start.substr(0, 2);

        if(__builtin_popcount(checked) == K){
            return suff == pref_start;
        }

        for(int idx_fun = 0; idx_fun < K; idx_fun++){
            if(checked & (1 << idx_fun)) continue;

            for(auto xs: prefixes[idx_fun][suff]){
                if(dfs(dfs, xs, start, checked | (1 << idx_fun))){
                    ans_v.push_back(xs);
                    return true;
                }
            }
        }
        return false;
    };


    for(auto [pref_x, v_xs]: prefixes[0]){
        for(auto xs: v_xs){
            if(dfs(dfs, xs, xs, 1)){
                ans_v.push_back(xs);
            }
        }
    }
    reverse(all(ans_v));

    lli ans = 0;
    for(auto x: ans_v)
        ans += stoi(x);

    cout << ans << endl;




	return 0;
}

