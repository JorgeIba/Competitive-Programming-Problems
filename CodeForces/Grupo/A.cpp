#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    lli res = 0;
    while(n--)
    {
        lli x; cin>>x;
        res = max(res,x);
    }
    cout<<res<<endl;

    return 0;
}