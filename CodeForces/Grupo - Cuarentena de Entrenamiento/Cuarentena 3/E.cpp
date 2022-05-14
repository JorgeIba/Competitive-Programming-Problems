#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    lli n; cin>>n;
    vector< pair<lli,bool> > nums(n);
    
    for(auto &x: nums)
    {
        cin>>x.first;
        x.second = false;
    }

    sort(nums.begin(), nums.end());
    vector<lli> res(n);
    lli cont = 0;
    lli x = 0;
    for(int i = 0; i<n; i++)
    {
        if(nums[i].second == false)
        {
            res[x++] = nums[i].first;
            nums[i].second = true;
            for(int j = i+1; j<n; j++)
            {
                if(nums[j].second == false)
                {
                    if(res[x-1]< nums[j].first)
                    {
                        res[x++] = nums[j].first;
                        nums[j].second = true;
                    }
                }
            }
        }
    }
   
    lli ant = 100000000LL;
    for(auto x: res)
    {
        if(x > ant)
        {
            cont++;
        }
        ant = x;
    }
    cout<<cont;

    return 0;
}