#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    map<lli,lli> last;
    lli count = 0;
    last[0] = 0;
    lli current = 0;
    bool flag = false;
    lli sum = 0;
    for(int i = 0; i<n; i++)
    {
        current += nums[i];
        if(current == 0)
        {
            count += (n-i);
            if(flag == false) flag = true;
            else sum++;
            continue;
        }
        if( last.find(current) != last.end())
        {
            lli l = last[current];
            count += (n-i) + (l+1);        
            if(flag == false) flag = true;
            else sum++;
        }
        else
        {
            last[current] = i;
        }
    }
    lli res = n*(n+1)/2;
    res-=count;
    res+=sum;
    cout<<res<<endl;

    return 0;
}