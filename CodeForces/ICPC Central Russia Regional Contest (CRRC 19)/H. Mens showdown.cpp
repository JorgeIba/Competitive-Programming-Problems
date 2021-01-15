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
    lli n; cin>>n;
    vector<lli> MEX(n+1);
    vector<lli> moves = {1, 5, 13};
    MEX[1] = 0;
    for(int i = 2; i<=n; i++)
    {
        bool win = false;
        for(auto j: moves)
        {
            if(i-j <= 0) break;
            if(!MEX[i-j]) win = true;
        }
        if(win) MEX[i] = 1;
    }
    cout << (MEX[n] ? "1" : "2") << endl;

    
	return 0;
}