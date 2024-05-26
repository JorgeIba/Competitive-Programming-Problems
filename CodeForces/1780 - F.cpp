#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector<int> muSieve(int n){
	vector<int> Mu(n+1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
	return Mu;
}

int main () {
	//fastIO();

    const int maxN = 3e5+1000;

    auto mu = muSieve(maxN);

    int n; cin>>n;
    vector<int> fr(maxN);
    for(int i = 0; i < n; i++){
        int x; cin>>x; 
        fr[x]++;
    }

    vector<int> prefix = fr;
    partial_sum(all(prefix), prefix.begin());

    lli ans = 0;
    for(int d = 1; d < maxN; d++) {
        lli sum = 0;
        lli cnt_non_zero = 0;
        lli acum_rest = 0;

        for(lli i = 1; i * d < maxN; i++) {
            if(!fr[i*d]) continue;

            sum += (prefix[i*d]*cnt_non_zero - (acum_rest)) - 2*cnt_non_zero;
            cnt_non_zero++;
            acum_rest += (prefix[i*d-1]);
        }
        
        ans += mu[d] * sum;
    }
    cout << ans << endl;

	return 0;
}

