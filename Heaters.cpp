#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{
    fastIO();
    lli n, r; cin>>n>>r;
    vector< lli > nums(n+1);
    //vector< bool > lleno(n+1);
    for(int i = 1; i<=n; i++)
    {
         cin>>nums[i];
         //lleno[i] = true;
    }
    lli i = 1, ans = 0;
    while(i<=n)
    {
        bool flag = false;
        //cout << i << " " << (i+r-1) << " " << (i-r+1) << endl;
        //cout << i << " ";
        for(int j = min(n, i + r -1); j>=max(0LL,i-r+1); j--)
        {
            if(nums[j])
            {
                cout << j << " ";
                ans++;
                i = min(n+1, j+r);
                cout << i << endl;
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            break;
        }
    }
    if(i == n+1) cout << ans << endl;
    else cout << -1 << endl;
    
    return 0;
}