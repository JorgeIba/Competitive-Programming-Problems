#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{
    //fastIO();
    lli n; cin>>n;
    vector< lli > nums(n);
    for(auto &x: nums) cin>>x;

    lli total = 0;
    for(int i = 0; i<n; i++)
    {
        total += (i+1)*nums[i];
    }
    cerr << total << endl;
    
    
    return 0;
}