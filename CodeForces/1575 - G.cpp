#pragma GCC optimize("O3,unroll-loops")

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

const int MAXN = 1e5 + 10;
const int MOD = 1e9+7;

vector<int> divs[MAXN];

inline void divsSieve(){
    for(int d = 1; d < MAXN; d++){
        for(int j = d; j < MAXN; j += d){
            divs[j].push_back(d);
        }
    }
}

int Phi[MAXN];
inline void phiSieve(){
	for(int i = 1; i < MAXN; ++i) Phi[i] = i;
	for(int i = 2; i < MAXN; ++i)
		if(Phi[i] == i)
			for(int j = i; j < MAXN; j += i)
				Phi[j] -= Phi[j] / i;
}


int frq[MAXN];
int a[MAXN];

int main () {
	fastIO();

    phiSieve();
    divsSieve();

    int n; cin>>n;
    forr(i, 1, n) cin>>a[i];

    lli ans = 0;
    for(int d = 1; d <= n; d++){
        vector<int> diffs;
        for(int j = d; j <= n; j += d){
            for(auto g: divs[a[j]]){
                if(!frq[g]) diffs.push_back(g);
                frq[g]++;
            }
        }

        lli sum = 0;
        for(auto g: diffs){
            sum += 1LL * Phi[ g ] * frq[ g ] * frq[ g ];
            frq[ g ] = 0;
        }

        ans += sum * Phi[d];
    }

    cout << ans % MOD << endl;

	return 0;
}

