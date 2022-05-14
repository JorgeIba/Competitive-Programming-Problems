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

vector<int> phiSieve(int n){
	vector<int> Phi(n+1);
	iota(Phi.begin(), Phi.end(), 0);
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
	return Phi;
}


int main () {
	//fastIO();

    const int N = 5 * 1e8;
    auto phi = phiSieve(N);

    lli sum = 0;
    for(int i = 1; i <= N; i++) {
        int mult = (i % 2 == 0 ? 0 : 1);

        sum += 1LL * phi[i] * mult % (i+1);
    }

    cout << sum << endl;

	return 0;
}

