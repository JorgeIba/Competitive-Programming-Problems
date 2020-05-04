#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli best = nums[0] ^ nums[1];
    for(int i = 0; i<n; i++)
    {
        lli aux = nums[i];
        for(int j= i+1; j<n; j++)
        {
            aux^= nums[j];
            best = max(best, aux);
        }
    }
    cout<<best<<endl;
    

    return 0;
}