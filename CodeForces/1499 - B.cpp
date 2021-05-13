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

const int INF = 1e7;

bool solve()
{
	string s; cin>>s;
	int n = s.length();

	lli last = INF;
	lli diff = INF;

	vector<lli> diffs(n+1, INF);
	for(int i = n-1; i>=0; i--)
	{
		if(s[i] == '0') 
		{
			diff = last - i;
			last = i;
		}
		diffs[i] = min(diffs[i+1], diff);
	}


	for(int i = 0; i<n; i++)
	{
		if(s[i] == '1')
		{
			if(diffs[i] > 1) return true;
			if(i > 0 && s[i-1] == '1') return false;
		}
	}

	//for(auto x: diffs) cout << x << " ";

	return true;
}

int main () {
	fastIO();	
	lli t; cin>>t;
	while(t--)
	{
		if(solve()) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}