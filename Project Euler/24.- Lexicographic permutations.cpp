#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define lli long long int

using namespace std;
using namespace __gnu_pbds;

typedef tree<lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

vector<lli> ans;
vector<lli> fact;

void factorial(lli n)
{
    fact.resize(n+1);
    fact[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        fact[i] = fact[i-1] * i;
    }
}

void foundPerm(ordered_set nums, lli target)
{
    if(nums.size()==0) return;

    lli sizze = nums.size();
    lli lowerBound = 0;
    for(int i = 0; i<sizze; i++)
    {
        if(i * ( fact[sizze-1] ) <= target)
            lowerBound = i;
        else
            break;
    }

    lli num = *nums.find_by_order(lowerBound);
    ans.push_back(num);
    nums.erase( nums.find_by_order(lowerBound) );
    foundPerm(  nums, target - lowerBound*fact[sizze-1]  ) ;
}


int main()
{
    lli n;
    ordered_set nums;
    cout<<"Enter the size of the set: ";
    cin>>n;
    cout<<"Enter the "<<n<<" "<<"numbers:\n";
    for(int i = 0; i < n; i++)
    {
        lli num; cin>>num;
        nums.insert(num);
    }
    factorial(n);
    lli perm;
    cout<<"What is the i-th permutation that you wanna get? ";
    cin>>perm;
    foundPerm(nums, perm - 1);

    for(auto x: ans)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    
    return 0;
}