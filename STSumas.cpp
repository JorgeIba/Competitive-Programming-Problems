#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli N;
vector<lli> ST;
vector<lli> arr;


void build(lli pos, lli l, lli r)
{
    if( l==r ) ST[pos] = arr[l];
    else
    {
        lli half = l + (r-l)/2;
        build(2*pos+1, l, half);
        build(2*pos+2, half+1, r);
        ST[pos] = ST[2*pos+1] + ST[2*pos + 2];
    }
}

lli query(lli start, lli end,lli pos, lli l, lli r)
{
    if( end < l | start > r) return 0;
    else if (  start <= l && r<= end) return ST[pos];
    else
    {
        lli half = l + (r-l)/2;
        return query(start, end, 2*pos+1, l, half) + query(start, end, 2*pos+2, half+1, r);
    }
}

void update(lli l, lli r, lli value, lli target, lli id)
{
    if(l == r) ST[id] = value;
    else
    {
        lli mid = l + (r-l)/2;
        if(target <= mid)
        {
            update(l, mid, value, target, 2*id + 1);
        }
        else
        {
            update(mid+1, r, value, target, 2*id + 2);
        }
        ST[id] = ST[2*id + 1] + ST[2*id + 2];
    }

}



int main()
{
    lli n; cin>>n;
    arr.resize(n);
    ST.resize(2*n+1, 0);
    for(auto &x: arr)
    {
        cin>>x;
    }
    build(0, 0, n-1);
    while(true)
    {
        for(auto x: ST)
        {
            cout<<x<<" ";
        }
        cout<<endl;
        lli pos, value; cin>>pos>>value;
        update(0, n-1, value, pos, 0 );
        
    }
        




    return 0;
}