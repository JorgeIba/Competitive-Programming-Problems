#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


lli pi_0(lli N)
{
    lli m = sqrt(N);
    vector<lli> lo(m+1), hi(m+1), values;
    auto pi = [&](lli idx) -> lli&{ //Mapping index
        if(idx <= m) return lo[idx];
        else return hi[N/idx];
    };
    for(lli i = 1; i<=m; i++)
    {
        values.push_back(i); //Values that dp can reach
        if(N/i != i)
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




int main()
{
    //fastIO();
    lli n; cin>>n;
    clock_t start = clock();
    lli res = pi_0(n);
    clock_t end = clock();
    cout<<res<<" "<<(double)(end-start) / CLOCKS_PER_SEC << endl;
    return 0;
}