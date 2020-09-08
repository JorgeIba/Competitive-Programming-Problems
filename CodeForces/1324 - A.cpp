#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli t; cin>>t;
    while(t--)
    {
        lli n; cin>>n;
        vector<lli> nums(n);
        bool flag = true;
        lli minimo = 100000000LL;
        for(auto &x: nums)
        {
            cin>>x;
            minimo = min(minimo, x);
        }

//        cout<<minimo<<endl;
        for(auto &x: nums)
        {
            x -= minimo;
            if(x&1)
            {
                flag = false;
            }
        }

        if(flag)
        {
            cout<<"YES\n";
        }
        else
        {
            cout<<"NO\n";
        }
        
    }

    return 0;
}