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


const lli maxD = 12'000;


lli F(lli a, lli b)
{
    lli ans = 0;
    for(lli d = 1; d <= maxD; d++)
    {
        for(lli c = 0; c <= d; c++)
        {
            if(__gcd(c, d) == 1){
                ans += (  c*b < a*d  );
            }
        }
    }
    return ans;
}


int main () {
	//fastIO();

    cout << F(1, 2) - F(1, 3) - 1 << endl;


	return 0;
}

