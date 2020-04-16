#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector<lli> a(n);
    vector<lli> b(n);
    vector<lli> need(n);
    for(auto &x: a)
    {
        cin>>x;
    }
    for(auto &x: b)
    {
        cin>>x;
    }
    for(int i = 0; i < n; i++)
    {
        need[i] = b[i] + 1 - a[i];
    }
    
    sort(need.begin(), need.end());

    lli l = 0, r = n-1, res = 0;
    while(l<r)
    {
        if(  need[l] + need[r]  <= 1 )
        {
            res += (r-l);
            l++;
        }
        else
        {
            r--;
        }
    }

    cout<<res<<endl;

    return 0;
}