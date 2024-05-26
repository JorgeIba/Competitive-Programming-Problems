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

const lli MOD = 998'244'353;

const int MAXN = 1e5+100;

vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}


lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


vector<pair<int,int>> factorize(int n){
    vector<pair<int,int>> facts;

    while(n > 1){
        int lp = lowestPrime[n];
        int pot = 0;

        while(n % lp == 0){
            pot++;
            n /= lp;
        }
        
        facts.push_back({lp, pot});
    }
    return facts;
}



int main () {
	//fastIO();
	
    lowestPrimeSieve(MAXN);

    int n; cin>>n;
    vector<int> perm(n+1);
    forr(i, 1, n) cin>>perm[i];

    vector<bool> visited(n+1);
    vector<pair<int,int>> sz_cycles;

    map<int,int> primes;


    lli ans = 0;
    forr(i, 1, n){
        auto x = perm[i];
        if(visited[x]) continue;

        int p = x;
        int sz = 0;
        do {
            sz++;
            visited[x] = true;
            x = perm[x];
        }while(x != p);

        int pot2 = 0, aux = sz;
        while(~aux & 1) {
            pot2++;
            aux >>= 1;
        }
    
        ans = max(ans, 1ll*pot2);

        lli l = 1;
        while(aux != 1 && powerMod(2, l, aux) != 1) l++;

        auto facts = factorize(l);
        for(auto [p, a]: facts)
            primes[p] = max(primes[p], a);

    }

    lli lcm = 1;

    for(auto [p, a]: primes)
        lcm = lcm * powerMod(p, a, MOD) % MOD;

    ans += lcm;

    if(ans >= MOD) ans -= MOD;

    cout << ans << endl;


	return 0;
}

