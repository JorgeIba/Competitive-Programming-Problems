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


int main () {
	//fastIO();
    lli n, s; cin>>n>>s;
    n = n*s;
    for(lli i = 1; i<=9; i++)
    {
        if((n*i) % 10 == 0) cout << (n*i) / 10 << " ";
        else cout << ((n*i) / 10) + 1 << " ";
    } cout << endl;


    
	return 0;
}