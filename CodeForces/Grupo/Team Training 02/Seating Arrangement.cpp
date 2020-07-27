#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
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
    if(n<=4)
    {
        cout<<-1<<endl;
        return 0;
    }
    if(n==5)
    {
        cout<<nums[0]<<" "<<nums[2]<<" "<<nums[4]<<" "<<nums[1]<<" "<<nums[3]<<endl;
        return 0;
    }
    else
    {
        vector<lli> pares;
        vector<lli> impares;
        for(int i = 0; i<n; i++)
        {
            if(i&1)
            {
                impares.push_back(nums[i]);
            }
            else
            {
                pares.push_back(nums[i]);
            }
        }
        lli t = impares.size();
        swap(impares[t-1], impares[t-2]);
        lli j=0, k=0;
        for(auto x: pares)
        {
            cout<<x<<" ";
        }
        for(auto x: impares)
        {
            cout<<x<<" ";
        }
    }
    


    return 0;
}

