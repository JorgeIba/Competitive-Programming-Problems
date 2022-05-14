#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    if(n==2) cout<<"1\n2\n";
    else if (n==3) cout<<"1\n3\n";
    else
    {
        vector<lli> res;
        if(n%2)
        {
            while(n>3)
            {
                res.push_back(2);
                n-=2;
            }
            res.push_back(3);
        }
        else
        {
            while(n)
            {
                res.push_back(2);
                n-=2;
            }
        }
        cout<<res.size()<<endl;;
        for(auto x:res)
        {
            cout<<x<<" ";
        }
    }
    
    return 0;   
}