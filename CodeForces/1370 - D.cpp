#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > nums;
lli n, k; 


bool isPossible(lli x)
{
    bool juntos = false;
    lli meSobran = n - k, noPasa = 0;
    for(int i = 0; i<n; i++)
    {
        if(!juntos)
        {
            if(nums[i] > x)
            {
                noPasa++;
            }
            else
            {
                juntos = true;
            }
        }
        else
        {
            juntos = false;
        }
    }
    if(meSobran >= noPasa) return true;

    juntos = false;
    noPasa = 0;
    for(int i = 1; i<n; i++)
    {
        if(!juntos)
        {
            if(nums[i] > x)
            {
                noPasa++;
            }
            else
            {
                juntos = true;
            }
            
        }
        else
        {
            juntos = false;
        }
    }
    if(meSobran >= noPasa) return true;
    return false;
}


int main()
{
    fastIO();
    cin>>n>>k;
    nums.resize(n);
    lli mayor = -1;
    for(auto &x: nums)
    {
        cin>>x;
        mayor = max(mayor, x);
    }
    

    lli l = 1, r = mayor, res = mayor;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(isPossible(mid))
        {
            res = mid;
            r = mid-1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << res << endl;
    


    return 0;
}