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

const int n = 30;

vector<char> possibilites = {'O', 'A', 'L'};

lli dp[31][3][4];

lli fun(int idx, int lates, int absents)
{
    if(lates > 1 || absents >= 3) return 0;

    if(idx == n)
    {
        return (lates <= 1) && (absents <= 2);
    }

    lli &ans = dp[idx][lates][absents];
    if(ans != -1) return ans;

    ans = 0;

    for(char poss: possibilites) //poss == O
    {
        if(poss == 'O')
            ans += fun(idx+1, lates, 0);
        else if(poss == 'L')
            ans += fun(idx+1, lates+1, 0);
        else 
            ans += fun(idx+1, lates, absents+1);
    }
    return ans;
}


int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));

    cout << fun(0, 0, 0) << endl;
    
	return 0;
}