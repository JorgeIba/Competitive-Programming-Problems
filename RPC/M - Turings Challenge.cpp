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


pair<lli,lli> sum_odd(lli n){
    if(n <= 1) return {n+1, n+1};

    lli last_level = 1LL << (lli)(log2(n));
    auto [total_sum, sum_idx] = sum_odd(n-last_level);

    return {2*total_sum, total_sum*(n+2)};
}


const lli INF = 1e9;
lli first_idx(lli n){
    if(n == 2) return 2;
    if(n == 4) return 3;
    if(__builtin_popcount(n+1) == 1 ) return INF;

    lli last_level = 1LL << (lli)(log2(n));
    lli equiv = n - last_level;
    auto last_idx = first_idx(equiv);

    // cout << n << " " << equiv << endl;

    if(last_idx == INF){

        return last_level/2 + 1;
    } else {
        // cout << n << " ->2 " << last_idx << endl;
        return last_idx;
    }
}



int main () {
	fastIO();
    
    lli q; cin>>q;


    while(q--) {

        lli N, X; cin>>X>>N;


        if(X % 4 == 0) cout << 0 << endl;
        else if (X % 2 == 0){
            if(N % 4 == 1 || N % 4 == 3) {
                assert(N * X % 4 == 2);
                cout << 3 << endl;
            } else {
                cout << 0 << endl;
            }
        } else {

            if(first_idx(N) == INF) cout << 0 << endl;
            else {
                lli last_index = N + 2 - first_idx(N);

                // cerr << sum_odd(N).second << " " << last_index << endl;
                lli ans = sum_odd(N).second + last_index;
                cout << ans << endl;
            }
        }
        
    }


	return 0;
}

