#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli factorial[10];
vector< vector<lli> > respuestas;

void prec()
{
    factorial[0] = factorial[1] = 1;
    for(int i = 2; i<=9; i++)
    {
        factorial[i] = i * factorial[i-1];
    }
}

vector<lli> descompN(lli n)
{
    vector<lli> ans;
    while(n)
    {
        lli res = n%10;
        n/=10;
        ans.push_back(res);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

bool eq(vector<lli> nums, vector<lli> suma)
{
    lli n = nums.size(), t = suma.size();
    if(n!=t) return false;
    for(int i = 0; i<n; i++)
    {
        if(nums[i]!=suma[i]) return false;
    }
    return true;
}

void solve(vector<lli> nums, lli suma, bool flag, int add, int index)
{
    if(flag)
    {
        nums.push_back(add);
        suma += factorial[add];
    }
    if(suma > 2200000 or index > 6) return;
    if(eq(nums,descompN(suma)))
    {
        cout<<suma<<endl;
        respuestas.push_back(nums);
    }

    for(int i = 0; i<=10; i++)    
    {
        if(i==0)
        {
            //solve(nums, suma, false, 0);
            continue;
        }
        solve( nums, suma, true, i - 1 , index + 1 );
    }

}


int main()
{
    prec();
    vector<lli> ans;
    for(int i = 0; i<=10; i++)    
    {
        if(i==0)
        {
            //solve(ans, 0, false, 0);
            continue;
        }
        solve( ans, 0, true, i - 1, 2 );
    }

    return 0;
}