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

map< pair<int, vector<int> > , lli > dp;
const int n = 18;


lli fun(int idx, vector<int> fr)
{
    if(idx == n) return 1;

    pair<int, vector<int>> look = {idx, fr};
    
    if(dp.find(look) != dp.end()) return dp[look];    

    lli ans = 0;
    for(int d = 0; d<=9; d++)
    {
        if(d == 0 && idx == 0) continue;
        if(fr[d] == 3) continue;
        auto frNew = fr;
        frNew[d]++;
        ans += fun(idx+1, frNew);
    }

    return dp[look] = ans;;
}




int main () {
	//fastIO();
    vector<int> fr(10);
    for(int d = 0; d<=9; d++) fr[d] = 0;
    cout << fun(0, fr) << endl;

	return 0;
}