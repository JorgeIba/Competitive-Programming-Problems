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
    lli b = 15, n = 21;
    const lli maxN = 1e12;
    while(n<maxN)
    {
        lli new_b = 3*b+2*n-2;
        lli new_n = 4*b+3*n-3;
        b = new_b;
        n = new_n;
    }
    cout << b << endl;
    
	return 0;
}