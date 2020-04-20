#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n; cin>>n;
    vector<lli> nums(n);
    lli sum = 0, mini = 1000000000LL;
    for(auto &x: nums)
    {
        cin>>x;
        if(x>0) sum+=x;
        if(x&1) mini = min(abs(x), mini);
    }
    if(sum&1)
    {
        cout<<sum<<endl;
    }
    else
    {
        cout<<(sum-mini)<<endl;
    }
    

}