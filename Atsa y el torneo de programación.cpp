#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    vector<lli> sums(n);

    for(auto &x: nums)
    {
        cin>>x;
    }
    lli suma = 0;
    for(int i = 0; i< n; i++)
    {
        suma+=nums[i];
    }
    lli res = 0;
    for(int i = 0; i<n; i++)
    {
        suma= suma - nums[i];
        res += suma*nums[i];
    }
    cout<<res<<endl;
    


    return 0;
}