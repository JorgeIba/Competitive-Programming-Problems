#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli t; cin>>t;
    while(t--)
    {
        lli h,m; cin>>h>>m;
        lli curr = h*60 + m;
        lli res = 24*60 - curr;
        cout<<res<<endl;
    }
    return 0;
}