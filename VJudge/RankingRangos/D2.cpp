#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<lli> nums;
vector<lli> ST;
lli n; 

void build()
{
    for(int i = n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(int i = n-1; i>0; i--)
    {
        ST[i] = ST[i<<1] + ST[i<<1|1];
    }
}

lli query(lli l)
{
    lli res = 0;
    l+=n;
    for(lli r=2*n-1; l<=r; l>>=1, r>>=1)
    {
        if(l&1)
        {
            res += ST[l++];
        }
        if(~r&1)
        {
            res += ST[r--];
        }
    }
    return res;
}

void update(lli index, lli value)
{
    for(ST[index+=n] = value; index; index>>=1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
    }
}


bool binaria(lli num)
{
    lli l = 0, r = n-1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        lli aux = query(mid);
        if(  aux == num ) return true;
        else if(aux > num)
        {
            l = mid + 1;
        }
        else
        {
            r = mid -1 ;
        }
    }
    return false;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    nums.resize(n);
    ST.resize(2*n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    build();
    

    lli q; cin>>q;
    while(q--)
    {
        lli t; cin>>t;
        if(t == 1)
        {
            lli i, v; cin>>i>>v;
            update(i-1,v);
        }
        else
        {
            lli num; cin>>num;
            if(binaria(num)) cout<<"YES\n";
            else cout<<"NO\n";
        }
        

    }
    

    

    return 0;
}