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


const int MOD = 1e9+7;


void add(lli &a, lli b)
{
	a += b;
	if(a >= MOD) a -= MOD;
}

lli binPow(lli a, lli b)
{
	if(b < 0)
		return 0;

	lli res = 1;
	while(b)
	{
		if(b&1) res = res * a % MOD;
		b >>= 1;
		a = a*a % MOD;
	}
	return res;
}


int main () {
	//fastIO();
	lli n; cin>>n;
	string s; cin>>s;
	
	vector<lli> ask_infront(n+1), c_infront(n+1);
	for(int i = n-1; i >= 0; i--)
	{
		ask_infront[i] = ask_infront[i+1] + (s[i+1] == '?');
		c_infront[i] = c_infront[i+1] + (s[i+1] == 'c');
	}

	lli k = count(all(s), '?');
	

	lli a_before = 0, ask_before = 0, ans = 0;
	for(int i = 0; i<n; i++)
	{
		char curr = s[i];
	

		if(curr == 'b')
		{
			add(ans, a_before * 1 * c_infront[i] * binPow(3, k) % MOD);
			add(ans, a_before * 1 * ask_infront[i] * binPow(3, k-1) % MOD);
			
			add(ans, ask_before * 1 * c_infront[i] * binPow(3, k-1) % MOD);
			add(ans, ask_before * 1 * ask_infront[i] * binPow(3, k-2) % MOD);
		}
		else if(curr == '?')
		{
			add(ans, a_before * 1 * c_infront[i] * binPow(3, k-1) % MOD);
			add(ans, a_before * 1 * ask_infront[i] * binPow(3, k-2) % MOD);
			
			add(ans, ask_before * 1 * c_infront[i] * binPow(3, k-2) % MOD);
			add(ans, ask_before * 1 * ask_infront[i] * binPow(3, k-3) % MOD);
		}

		if(curr == 'a') a_before++;
		if(curr == '?') ask_before++;
	}

	cout << ans << endl;

	

	return 0;
}

