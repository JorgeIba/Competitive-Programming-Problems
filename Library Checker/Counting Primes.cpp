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

lli pi_0(lli N)
{
    lli m = sqrt(N);
    vector<lli> lo(m+1), hi(m+1), values;
    auto pi = [&](lli idx) -> lli&{ //Mapping index
        if(idx <= m) return lo[idx];
        return hi[N/idx];
    };
    for(lli i = 1; i<=m; i++)
    {
        values.push_back(i); //Values that dp can reach
        if(i != N/i)
        {
            values.push_back(N/i);
        }
    }
    sort(all(values), greater<lli>());
    for(lli v: values)
    {
        pi(v) = v-1; //Initializing
    }
    for(lli p = 2; p<=m; p++)
    {
        if(pi(p) == pi(p-1)) continue; //Only primes changes of pi(p) and pi(p-1)
        for(auto v: values)
        {
            if(p*p > v) break;
            pi(v) = pi(v) - ( pi(v/p) - pi(p-1)  );
        }
    }
    return pi(N);
}


int main () {
	//fastIO();
    lli n; cin>>n;
    cout << pi_0(n) << endl;

	return 0;
}