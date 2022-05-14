#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#define lli long long int

using namespace std;
using namespace __gnu_pbds;
typedef tree< lli , null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update > ordered_set;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    //BIT.resize(n+1, 0);
    vector< pair<lli,lli> > nums(n);
    vector< lli > numsNot(n);
    for(int i = 0; i < n; i++)
    {
        cin>>nums[i].first;
        numsNot[i] = nums[i].first;
        nums[i].second = i;
    }
    sort(nums.begin(), nums.end(), compare);


    vector<lli> sums(n);
    sums[0] = nums[0].first;
    for(int i = 1; i < n; i++)
    {
        sums[i] = sums[i-1] + nums[i].first;
    }
    
    lli m; cin>>m;

    vector< tuple<lli,lli,lli> > requests(m); //get0 -> k, get1 -> pos, get2 -> i
    for(int i = 0; i < m; i++)
    {
        lli k, pos; cin>>k>>pos;
        get<0> (requests[i]) = k-1;
        get<1> (requests[i]) = pos;
        get<2> (requests[i]) = i;
    }
    sort(requests.begin(), requests.end());

    ordered_set check;
    vector< tuple<lli,lli,lli> > ans(m); //0 -> index Original, 1 -> suma, 2 -> numero
    lli k = 0;
    for(int i = 0; i< m; i++)
    {
        lli kj = get<0>(requests[i]);
        lli posj = get<1>(requests[i]);
        lli index = get<2>(requests[i]);
        while(k<=kj)
        {
            check.insert(nums[k].second);
            k++;
        }
        get<0> (ans[i]) = index;
        get<1> (ans[i]) = sums[kj];
        lli indexCheck = *check.find_by_order(posj-1);
        get<2> (ans[i]) = numsNot[indexCheck];
        
    }
    sort(ans.begin(), ans.end());
    
    for(auto x: ans)
    {
        cout<< get<2> (x) <<"\n";
    }
    return 0;
}   