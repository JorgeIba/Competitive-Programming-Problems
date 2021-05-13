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

bool is_valid(lli n)
{
    set<lli> facts;
    for(lli i = 2; i*i<=n; i++)
    {
        while(n % i == 0)
        {
            n /= i;
            facts.insert(i);
        }
    }
    if(n > 1) facts.insert(n);
    return facts.size() == 1;
}


int main () {
	//fastIO();
    lli q; cin>>q;

    if(is_valid(q))
        cout << "yes\n";
    else
        cout << "no\n";

	return 0;
}