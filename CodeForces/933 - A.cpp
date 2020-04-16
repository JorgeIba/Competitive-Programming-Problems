#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli n;
vector<lli> nums; 

lli contrario(lli n)
{
    if(n==1) return 2;
    else return 1;
}

lli funcion(lli index, lli estado, lli anterior)
{
    if(index>=n)
    {
        return 0;
    }
    lli act = nums[index];
    if(act < anterior)
    {
        if(estado == 0)
        {
            return funcion(index+1, 1, 2) + 1;
        }
        else
        {
            if(act == 1)
            {
                return funcion(index+1, 1, 2) + 1;
            }
        }
        
        return 0;
    }
    else
    {
        lli si = funcion(index+1, 1, contrario(act)) + 1;
        lli no = funcion(index+1, 0, act) + 1;
        
        return max( si, no );
    }
}


int main()
{
    cin>>n;
    nums.resize(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    
    return 0;
}