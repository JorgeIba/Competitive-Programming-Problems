#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n; cin>>n;
    map<lli,lli> socks;
    lli res = -1;
    for(int i = 0; i < 2*n; i++)
    {
        lli x; cin>>x;
        socks[x]++;
        if(socks[x]==2)
        {
            socks.erase(x);
        }
        res = max(res, (lli)socks.size() );
    }
    cout<<res<<endl;
    return 0;
}