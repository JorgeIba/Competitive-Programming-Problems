#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MAXN = 1e5 + 100;
vector<pair<int,lli>> adjList[MAXN];
vector<int> divs[MAXN];


lli power(lli a, lli b){
    lli res = 1;
    while(b){
        if(b & 1) res = res * a;
        b >>= 1;
        a = a * a;
    }
    return res;
}

int lp[MAXN];

void prec() {
    for(int d = 1; d < MAXN; d++) {
        for(int j = d; j < MAXN; j += d) {
            divs[j].push_back(d);
        }
    }
    
    iota(lp, lp + MAXN, 0);
    for(int i = 2; i < MAXN; i++) {
        if(lp[i] == i) {
            for(int j = 2*i; j < MAXN; j += i) {
                if(lp[j] == j)
                    lp[j] = i;
            }
        }
    }
}


map<int,int> get_factors(int n){
    map<int,int> facts;
    while(n > 1) {
        int pot = 0;
        int prime = lp[n];
        while(n % prime == 0) {
            n /= prime;
            pot++;
        }

        facts[prime] = pot;
    }
    return facts;
};  


int main () {
	// fastIO();

    prec();


    int n; cin>>n;
    vector<lli> w(n+1);
    lli W = 0;
    forr(i, 1, n) {
        cin>>w[i];
        W += w[i];
    }

    vector<lli> sum_w_divs(n+1);

    for(int x = 1; x <= n; x++) {
        for(int z = x; z <= n; z += x) {
            auto fact_z = get_factors(z);
            auto fact_x = get_factors(x);
            int t = 1;
            int fix = 1;
            for(auto [p, e]: fact_z){
                if(fact_x[p] == e) {
                    t *= power(p, e);
                } else {
                    fix *= power(p, e);
                }
            }

            lli sum = 0;
            for(auto d: divs[t]) {
                int y = d * fix;
                sum += w[y];
            }
            if(z == x) {
                sum_w_divs[x] = sum;
            } else {
                adjList[x].push_back({z, sum});
            }
        }
    }


    vector<ld> dp(n+1);

    for(int i = n; i >= 1; i--) {
        ld &ans = dp[i];
        ans = (ld) sum_w_divs[i] / W;
        for(auto [z, w_sum]: adjList[i]) {
            assert(z % i == 0);
            ans += ((ld) w_sum / W) * (1 + dp[z]);
        }
        ans = ans * W / (W - sum_w_divs[i]);
    }

    cout << fixed << setprecision(14) << (dp[1]) << endl;



	return 0;
}

