#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    lli best = 10000000000000000LL;
    lli res1 = 1, res2 = n;
    for(lli i=1; i * i <= n; i++)
    {
        if ( n%i == 0)
        {
            lli div = n/i;
            if(__gcd(i, div) == 1)
            {
                lli aux = max(i,div);
                if( aux < best)
                {
                    best = aux;
                    res1 = i;
                    res2 = div;
                }
            }
        }
    }
    cout<<res1<<" "<<res2<<endl;
    
    return 0;
}
