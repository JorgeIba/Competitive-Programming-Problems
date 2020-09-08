#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<lli> BIT;
vector<lli> nums;

void update(lli index, lli value)
{
    while(index < BIT.size())
    {
        BIT[index] += value;
        index += index&(-index);
    }
}

lli sum(lli index)
{
    lli res = 0;
    while(index)
    {
        res += BIT[index];
        index -= index&(-index);
    }
    return res;
}

void change()
{
    lli a, b; cin>>a>>b;
    lli diff = b-nums[a-1];
    nums[a-1] = b;
    //cout<<a<<" "<<diff<<endl;
    update(a, diff);
}

void check()
{
    lli target; cin>>target;
    lli total = sum(BIT.size()-1);
    lli l = 0, r = BIT.size()-1;
    //cout<<total<<endl;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        lli aux = sum(mid);
        if( total-aux == target  )
        {
            cout<<"YES\n";
            return;
        }
        else if (total - aux > target)
        {
            /*
            cout<<"L\n";
            cout<<total-aux<<endl;
            cout<<l<<" "<<mid<<" "<<r<<endl;
            */
            l = mid+1LL;
        }
        else
        {
            /*
            cout<<"R\n";
            cout<<total-aux<<endl;
            cout<<l<<" "<<mid<<" "<<r<<endl;
            */
            r = mid-1LL;
        }
        
    }
    cout<<"NO\n";
    return;
}

int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    lli n; cin>>n;
    nums.resize(n,0);
    BIT.resize(n+1, 0);
    for(auto &x: nums)
    {
        cin>>x;
    }
    for(lli i=0; i<n; i++)
    {
        update(i+1, nums[i]);
    }

    lli q; cin>>q;
    while(q--)
    {
        lli t; cin>>t;
        if(t == 1)
        {
            change();
        }
        else
        {
            check();
        }
    }

    

    return 0;
}