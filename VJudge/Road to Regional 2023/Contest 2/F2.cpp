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


const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b


int main () {
	//fastIO();
	
    ld p;
    int n; cin>>n>>p;

    vector<lli> nums(n+1);
    forn(i, n) cin>>nums[i];

    vector< lli > prefix_diffs(n);
    vector< lli > prefix_diffs_sq(n);


    for(int i = 0; i < n-1; i++) {
        if(i) {
            prefix_diffs[i] = prefix_diffs[i-1];
            prefix_diffs_sq[i] = prefix_diffs_sq[i-1];
        }

        lli diff = (nums[i+1] - nums[i]);
        // debugg(diff);
        prefix_diffs[i] += diff;
        prefix_diffs_sq[i] += (diff * diff);
    }

    auto get_diffs = [&](int l, int r){
        return prefix_diffs[r] - (l?prefix_diffs[l-1]:0);
    };
    auto get_sq = [&](int l, int r){
        return prefix_diffs_sq[r] - (l?prefix_diffs_sq[l-1]:0);
    };

    int pos = 0, neg = 0;

    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n-1; j++){
            
            int l = i, r = j+1;

            int n = r - l + 1;
            n--;

            lli S = get_diffs(i, j);
            lli T = get_sq(i, j);

            // A = S / n
            // D = sqrt(T / n - S^2 / n^2)

            if(S == 0) continue;

            if(n*T - S*S == 0) {
                if(S > 0) pos++;
                else neg++;
                continue;
            }

            assert(n*T - S*S >= 0);

            // A/D = S / sqrt(n*T - S^2)
            
            ld Q = sqrtl(n*T - S*S);
            // if(S*S >= Q*p) {
            if(geq(S, Q*p)){
                pos++;
            }

            if(geq(-S, Q*p)){
                neg++;
            }

            // cout << get_diffs(i, j) << " --> " << l << " -- " << r << " ,,, " <<  n << endl;
        }
    }

    cout << pos << " " << neg << endl;




	return 0;
}

