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
    int n; cin>>n;

    string wildcard = "aabb";
    string ss;
    
    while(SZ(ss) <= n) ss += wildcard;

    for(int i = 0; i < n; i++) cout << ss[i] ;

	return 0;
}

