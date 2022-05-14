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



pair<lli, lli> decompose(lli n){
    lli pot = 0;
    while(n % 2 == 0) {
        pot++;
        n /= 2;
    }
    return {n, pot};
}



void solve(){
    int n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<pair<lli,lli>> decomposed;
    for(auto x: nums) decomposed.push_back(decompose(x));

    
    lli acumulated = 0;
    for(auto x: decomposed) acumulated += x.second;

    sort(all(decomposed));
    lli biggest = decomposed.back().first; decomposed.pop_back();


    lli ans = biggest * (1LL << acumulated);
    for(auto x: decomposed) ans += x.first;


    cout << ans << endl;
}


int main () {
	//fastIO();
    int t; cin>>t;

    while(t--) solve();



	return 0;
}

