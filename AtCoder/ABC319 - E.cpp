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

tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}


pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < (int)a.size(); ++i){
		auto[d, s, t] = extendedGcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
		lli k = s * (((a[i] - x) / d) % step) % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}



const int MOD = 840;

int main () {
	fastIO();

    int n, x, y; cin>>n>>x>>y;
    vector< pair<int,int> > stops(n-1);

    for(auto &[p, t]: stops) cin>>p>>t;


    vector<lli> ans_for_i(MOD);
    for(int start = 0; start < MOD; start++){

        lli a = start + x;
        lli time_a = x;
        for(int i = 0; i < n-1; i++){
            auto [p, t] = stops[i];

            // debugg(a);
            time_a += (p - (a%p))%p + t;
            a = a + (p - (a%p))%p;
            // debugg(a);
            a = a + t;

            
            // debugg(a);
            // cout << endl;
        }

        ans_for_i[start] = time_a + y;
    }

    int q; cin>>q;
    while(q--){
        lli x; cin>>x;
        cout << x + ans_for_i[x % MOD] << endl;
    }


	return 0;
}

