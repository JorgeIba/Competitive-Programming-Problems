
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


vector<int> primes;
vector<bool> isPrime;
vector<int> toSquareFree;
void primesSieve(int n){
    toSquareFree.resize(n+1, 1);
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;

	for(int i = 2; i <= n; i++){
		if(isPrime[i]){
			primes.push_back(i);
            for(int j = i; j <= n; j += i){
                isPrime[j] = false;
                toSquareFree[j] *= i;
            }	
		}
	}
}

const int MAXN = 1e3 + 100;
const int MAXP = 610;
const int MOD = 998244353;

int adjList[MAXP][MAXP];

int dp[MAXN][MAXP];
int fr[MAXN];
int fr2[MAXP];
int pt[MAXP];

int main () {
	fastIO();
	
    primesSieve(MAXN);

    int n, m; cin>>n>>m;

    vector<int> squareFrees;
    forr(i, 1, m)
        squareFrees.push_back(toSquareFree[i]);

    sort(all(squareFrees));
    squareFrees.erase(unique(all(squareFrees)), squareFrees.end());


    forr(i, 1, m)
        fr[toSquareFree[i]]++;

    int l = SZ(squareFrees);
    forn(i, l)
        fr2[i] = fr[squareFrees[i]];
    

    forn(i, l){
        forn(j, l)
            if(gcd( squareFrees[i], squareFrees[j] ) == 1)
                adjList[i][pt[i]++] = j;
    }


    for(int i = 0; i < l; i++){
        dp[n][i] = 1;
    }

    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < l; j++){
            for(int k = 0; k < pt[j]; k++) {
                int v = adjList[j][k];
                dp[i][j] += 1LL * fr2[v] * dp[i+1][v] % MOD;
                if(dp[i][j] >= MOD) dp[i][j] -= MOD;
            }
        }
    }

    cout << dp[0][0] << endl;


	return 0;
}

