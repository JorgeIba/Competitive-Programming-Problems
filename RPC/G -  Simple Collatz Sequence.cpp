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


const lli mod = 1000007;

void modula(lli & n){
	while(n >= mod) n -= mod;
}

lli fibo(lli n){
	array<lli, 2> F = {1, 0};
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	array<lli, 4> C;
	do{
		int d = (n & p) != 0;
		C[0] = C[3] = 0;
		C[d] = F[0] * F[0] % mod;
		C[d+1] = (F[0] * F[1] << 1) % mod;
		C[d+2] = F[1] * F[1] % mod;
		F[0] = C[0] + C[2] + C[3];
		F[1] = C[1] + C[2] + (C[3] << 1);
		modula(F[0]);
        modula(F[1]);
	}while(p >>= 1);
	return F[1];
}



int main () {
	//fastIO();

    lli n; cin>>n;

    cout << fibo(n) << endl;

    /*

    queue<pair<lli,lli>> q;

    q.push({1, 0});

    vector< vector<lli> > distV(n+5);

    lli ans = 0;
    while(!q.empty()) {
        auto [u, dist] = q.front(); q.pop();

        distV[dist].push_back(u);

        if(dist > n) continue;
        if(dist == n) {
            ans += (dist == n);
        }

        if(u & 1) {
            q.push({2*u, dist+1});
        } else {
            q.push({2*u, dist+1});
            if(u > 2)
                q.push({u-1, dist+1});
        }
    }

    for(int i = 0; i <= n; i++) {
        cout << i << ": ";
        cout << SZ(distV[i]) << endl;
        // for(auto x: distV[i]){
        //     cout << x << " ";
        // }
        
    }
    */

	return 0;
}

