#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.rbegin(), v.rend()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n, k; cin>>n>>k;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    sort(all(nums));
    lli suma = 0;
    for(int i = 0; i<k; i++)
    {
        suma+=nums[i];
    }
    cout<<suma<<endl;


    return 0;
}