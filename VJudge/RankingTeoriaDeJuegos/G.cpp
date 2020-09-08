#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; 
    while(cin>>n)
    {   
        if(n==0)
        {
            return;
        }
        vector<lli> pilas(n);
        lli res = 0;
        for(int i = 0; i<n; i++)
        {
            cin>>pilas[i];
            res ^= pilas[i];
        }
        if(res==0)
        {
            cout<<0<<endl;
        }
        else
        {
            //cout<<res<<" ";
            lli aux = 0;
            for(auto x: pilas)
            {
                lli necesito = x ^ res;
                if (necesito <= x)
                {
                    aux++;
                }
            }
            cout<<aux<<endl;
        }
    }
        

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}