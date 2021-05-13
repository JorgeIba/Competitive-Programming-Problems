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

VLL get_divs(lli n)
{
    VLL divs;
    for(lli i = 1; i*i <= n; i++)
    {
        if( n % i == 0)
        {
            divs.push_back(i);
            if(i*i != n) divs.push_back(n/i);
        }
    }
    return divs;
}


int main () {
	//fastIO();
    lli b; cin>>b;

    auto divs = get_divs(b);

    cout << SZ(divs) << endl;

	return 0;
}