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

const lli MOD = 1e9+7;

lli binPow(lli a, lli b)
{
	lli res = 1;
	while(b)
	{
		if(b&1) res = res * a % MOD;
		b>>=1;
		a = a*a %MOD;
	}
	return res;
}


int main () {
	//fastIO();
	int n, m, c; cin>>n>>m>>c;
	lli suma = 0;
	for(int i = 0; i<m; i++)
	{
		suma += binPow(c, 1LL*n*n*__gcd(i,m));
		if(suma >= MOD) suma -= MOD;
	}
	suma = suma*binPow(m, MOD-2) % MOD;
	cout << suma << endl;


    
	return 0;
}