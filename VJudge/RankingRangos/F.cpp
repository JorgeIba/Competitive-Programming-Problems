#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<lli> ST;
vector<lli> Lazy;
lli n;

void apply(lli index, lli value)
{
    ST[index] += value;
    if(index < n)
    {
        Lazy[index] += value;
    }
}

void push(lli p)
{
    int h = sizeof(int) * 8 - __builtin_clz(n);
    for(int s = h, k = 1<<(s-1))

}




void update(lli l, lli r, lli value)
{
    l += n;
    r += n;
    
}

lli query(lli l, lli r)
{
    push(l+=n);
    push(r+=n);
    lli res = 0;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1 )
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
}


void solve()
{
    lli c; cin>>n>>c;
    ST.resize(2*n,0);
    Lazy.resize(n,0);
    while(c--)
    {
        lli t; cin>>t;
        if(t==1)
        {
            lli l, r; cin>>l>>r;
            //cout<< query(l,r)<<endl;
        }
        else
        {
            lli l, r, value; cin>>l>>r>>value;
            update(l,r,value);
        }
    }


}



int main()
{
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}