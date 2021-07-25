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
	
	lli N = 1e3;

    lli ans = -1, n = 2;
    for(; true; n++)
    {
        auto divs = get_divs(n);
        lli ans_n = 0;
        for(int i = 0; i<SZ(divs); i++)
            for(int j = i+1; j<SZ(divs); j++)
                if(__gcd(divs[i], divs[j]) == 1)
                    ans_n++;
        

        ans = max(ans, ans_n);
        if(ans > N) break;
    }

    cout << n << " " << ans << endl;

	return 0;
}