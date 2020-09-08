#include <bits/stdc++.h>
#define lli long long int 

using namespace std;

int main()
{   
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    map<lli,lli> nums;
    
    for(lli i=0; i<n; i++)
    {
        nums[i] = -1;
    }
    for(lli i=0; i<n; i++)
    {
        nums[ (i*i)%n ] = i;
    }
    for(lli i = 0; i<n; i++)
    {
        cout<<nums[i]<<" ";
    }

    return 0;
}