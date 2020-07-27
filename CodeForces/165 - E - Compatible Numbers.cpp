#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
const lli maxN = 23, maxMask = (1<<maxN);
lli dp[maxMask];

int main()
{
    fastIO();
    lli n; cin>>n;
    vector< lli > nums(n);
    for(auto &x: nums) cin>>x;

    lli sz = log2(*max_element(all(nums))) + 1;


    for(int i = 0; i<n; i++)
    {
        dp[nums[i]] = nums[i];
    }

    for(int i = 0; i<sz; i++)
    {
        for(int mask = 0; mask < (1<<sz) ; mask++)
        {
            if(  mask & (1<<i) &&  dp[mask] == 0)
            {
                dp[mask] = dp[mask^(1<<i)];
            }
        }
    }

    for(int i = 0; i<n; i++)
    {
        lli num = nums[i];
        lli mask = (~num) & (  (1 << sz) - 1 );
        //bitset<10> aux = num; cout << aux.to_string() << endl;
        //aux = mask; cout << aux.to_string() << endl;
        if( dp[mask] != 0 )
        {
            cout<< dp[mask] << " ";
        }
        else
        {
            cout<<(-1)<<" ";
        }
        
    }

    return 0;
}