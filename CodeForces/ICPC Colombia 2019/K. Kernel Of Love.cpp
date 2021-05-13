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
	fastIO();
    int n; cin>>n;

    for(int i = 0; i < n; i++)
    {
        lli x; cin>>x;
        if(x <= 2) cout << 0 << endl;
        else if(x == 3) cout << 2 << endl;
        else   
        {
            lli cabe = (x-1) / 3;
            lli total = cabe * 2;
            if( x % 3 == 0 ) total+=2;
            else total++;
            cout << (total) << endl;
        }
    }
    
    

	return 0;
}