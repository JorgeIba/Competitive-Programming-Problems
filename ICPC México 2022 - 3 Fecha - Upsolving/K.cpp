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


typedef vector<lli> poly;

lli n, m, k;

const lli MOD = 1e9;



poly multiply(poly a, poly b) {

    poly c(SZ(a) + SZ(b) - 1);

    for(int i = 0; i < SZ(a); i++) {
        for(int j = 0; j < SZ(b); j++) {
            (c[i+j] += a[i]*b[j] % MOD) %= MOD;
        }
    }
    c.resize(k+1);
    return c;
}

poly add(poly a, poly b){
    poly c( max(SZ(a), SZ(b)) );
    
    for(int i = 0; i < SZ(c); i++) {
        lli sum_a = (i < SZ(a) ? a[i] : 0);
        lli sum_b = (i < SZ(b) ? b[i] : 0);
        c[i] = (sum_a + sum_b) % MOD;
    }

    c.resize(k+1);

    return c;
}


poly kthTermLinearRecurrence(const vector<poly> & P, const vector<poly> & init, lli n){
	int deg = P.size();
	vector<poly> ans(deg, poly(1, 0)), R(2*deg, poly(1,0));
	ans[0] = poly(1,1);
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), poly(1,0));
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				R[i + j + d] = add(R[i + j + d], multiply(ans[i] , ans[j]));
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				R[i + j] = add(R[i + j], multiply(R[i + deg], P[j]));
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	poly nValue(1,0);


	for(int i = 0; i < deg; i++) {
        nValue = add(nValue, multiply(ans[i], init[i]));
    }
    		
	return nValue;
}
 



int main () {
	//fastIO();

    cin>>n>>m>>k;
    
    vector<pair<lli,lli>> options(m);

    vector<poly> recurrence(11, poly(k+1));

    for(auto &op: options) {
        cin>>op.first>>op.second;

        lli d = op.first, c = op.second;
        recurrence[d][c]++;
    }

    vector<poly> initial_values(11);
    initial_values[1] = poly(k+1, 1);

    for(int i = 2; i <= 10; i++) {
        poly ans(1);
        for(int j = 1; j < i; j++) {
            poly product = multiply(initial_values[i-j],  recurrence[j]);
            
            ans = add(ans, product);
        }
        initial_values[i] = ans;
    }
    
    recurrence.erase(recurrence.begin());
    initial_values.erase(initial_values.begin());

    reverse(all(recurrence));

    auto ans = kthTermLinearRecurrence(recurrence, initial_values, n-1);
    cout << ans[k] << endl;
    
    
	return 0;
}

