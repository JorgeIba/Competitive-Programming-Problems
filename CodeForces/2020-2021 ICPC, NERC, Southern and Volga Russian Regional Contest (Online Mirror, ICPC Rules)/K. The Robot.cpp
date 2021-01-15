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
typedef pair<lli,lli> PLL;

PLL move(PLL a, char dir)
{
    if(dir == 'R') return {a.first + 1, a.second};
    else if(dir == 'L') return {a.first - 1, a.second};
    else if(dir == 'U') return {a.first, a.second + 1};
    else return {a.first, a.second - 1};
}


void solve()
{
    string s; cin>>s;
    vector< PLL > pasa;
    PLL curr = {0,0};
    for(auto x: s)
    {
        curr = move(curr, x);
        pasa.push_back(curr);
    }

    for(auto block: pasa)
    {
        curr = {0,0};
        for(auto x: s)
        {
            PLL aux = move(curr, x);
            if(aux != block)
            {
                curr = aux;
            }
        }
        if(curr.first == 0 && curr.second == 0)
        {
            cout << block.first << " " << block.second << endl;
            return;
        }
    }
    cout << 0 << " " << 0 << endl;

}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();
    
	return 0;
}