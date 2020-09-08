#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        lli a, b; cin>>a>>b;
        if(~a&1 and ~b&1)
        {
            cout<<"abdullah\n";
        }
        else
        {
            cout<<"hasan\n";
        }
    }
    
    

    return 0;
}