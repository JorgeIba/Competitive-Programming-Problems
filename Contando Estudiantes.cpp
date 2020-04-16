#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> BIT(1000010);

void update(lli num)
{
    //BIT[num]++;
    while(num < BIT.size())
    {
        BIT[num] += 1;
        num += num&(-num);
    }
}

lli sum(lli index)
{
    lli res = 0 ;
    while(index)
    {
        res += BIT[index];
        index -= index&(-index);
    }
    return res;
}



int main()
{   
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    while(n--)
    {
        lli t, x; cin>>t>>x;
        if(t==1)
        {
            update(x);
        }
        else
        {
            cout<<sum(x)<<endl;
        }
    }

    return 0;   
}