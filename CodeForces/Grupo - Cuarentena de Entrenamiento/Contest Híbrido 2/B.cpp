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


const lli MOD = 998244353;

int main () {
	//fastIO();

    vector<lli> ans(1e3+1);
    ans[2] = 1;

    lli mult = 2;
    for(int i = 4; i < SZ(ans); i+=2) {
        ans[i] = ans[i-2] * mult % MOD;
        (mult += i) %= MOD;
    }


    lli t; cin>>t;

    while(t--) {
        lli n; cin>>n;
        cout << ans[n] * (n / 2) % MOD << endl;

    }

    


    /*
    vector<lli> perm(n);
    iota(all(perm), 1);

    vector<vector<lli>> yes, no;

    do {
        lli gcd = 0;
        int i = 1;
        for(auto x: perm) gcd = __gcd(gcd, (i++)*x);

        if(gcd > 1) yes.push_back(perm);
        else no.push_back(perm);

    }while(next_permutation(all(perm)));


    vector<lli> num(n+1);
    for(auto v: yes) {
        num[v[0]]++;
        // for(auto x: v) cout << x << " ";
        
    }

    for(auto x: num) cout << x << " ";
    */

	return 0;
}

