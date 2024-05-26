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


void main_(){
    int n, k, a, b; cin>>n>>k>>a>>b; a--, b--;

    vector< pair<lli,lli> > points(n);

    for(auto &[x, y]: points) cin>>x>>y;


    auto get_cost = [&](int idx_i, int idx_j){
        if(idx_i < k && idx_j < k) return 0LL;
        auto [x_1, y_1] = points[idx_i];
        auto [x_2, y_2] = points[idx_j];
        return abs(x_1 - x_2) + abs(y_1 - y_2);
    };

    lli ans = get_cost(a, b);

    lli min_cost_i = 0;
    for(int i = 0; i < k; i++){
        if(get_cost(a, min_cost_i) > get_cost(a, i))
            min_cost_i = i;
    }

    lli min_cost_j = 0;
    for(int i = 0; i < k; i++){
        if(get_cost(min_cost_j, b) > get_cost(b, i))
            min_cost_j = i;
    }

    ans = min(ans, get_cost(a, min_cost_i) + get_cost(min_cost_j, b));

    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

