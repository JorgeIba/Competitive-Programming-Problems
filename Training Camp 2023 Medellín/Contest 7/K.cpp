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


const int MOD = 7901;
const int MAXN = 1e3 + 100;
lli fact[MAXN];

void main_(){
	
    int n; cin>>n;
    map<int,int> fr;

    forn(i, n){
        int x; cin>>x;
        fr[x]++;
    }

    lli ans = 1;
    for(auto [x, frq]: fr) {
        ans = ans * fact[frq] % MOD;
    }

    cout << ans << endl;
}


int main () {
	fastIO();

    fact[0] = 1;
    forr(i, 1, MAXN-1) fact[i] = fact[i-1] * i % MOD;
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

