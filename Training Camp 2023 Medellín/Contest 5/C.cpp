#pragma GCC optimize("O3")

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

const int MAXN = 1e7+10;
int mu[MAXN + 10];

int main () {
	//fastIO();
	
    memset(mu, -1, sizeof(mu));
    mu[0] = 0, mu[1] = 1;
    for(int i = 2; i <= MAXN; ++i)
        if(mu[i])
            for(int j = 2*i; j <= MAXN; j += i)
                mu[j] -= mu[i];

    int a, b, c, d; cin>>a>>b>>c>>d;

    lli ans = 0;
    for(int l = 1; l <= MAXN; l++){
        int ab = (b/l) - (a-1)/l;
        int cd = (d/l) - (c-1)/l;
        ans += 1LL * mu[l] * ab * cd;
    }

    cout << ans << endl;

	return 0;
}

