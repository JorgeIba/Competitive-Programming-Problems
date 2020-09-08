#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> nums;
lli n; 
lli dp[100010][2];

lli funcion(lli index, lli estado) //estado que busco 0 -> pos, 1 ->neg
{
    if(index>=n)
    {
        return 0;
    }
    if(dp[index][estado] != -1)
    {
        return dp[index][estado];
    }
    switch(estado)
    {
        case 0:
            if(nums[index] > 0)
            {
                return dp[index][estado] = max( funcion(index+1, 1) + nums[index],   funcion(index+1, 0)    );
            }
            else
            {
                return dp[index][estado] = funcion(index+1, 0);
            }
        case 1:
            if(nums[index] < 0)
            {
                return dp[index][estado] =  max( funcion(index+1, 0) + nums[index], funcion(index+1, 1)    );
            }
            else
            {
                return dp[index][estado] = funcion(index+1, 1);
            }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin>>n;
    nums.resize(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli res = max(funcion(0,0), funcion(0,1));
    cout<<res<<endl;

    return 0;
}  