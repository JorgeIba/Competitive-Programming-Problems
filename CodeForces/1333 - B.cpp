#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

void solve()
{
    lli n; cin>>n;
    vector< lli > a(n);
    vector< lli > b(n);
    vector<bool> op(n, false);
    // 0 -> se puede sumar, 1-> se puede restar
    for(auto &x: a)
    {
        cin>>x;
    }
    for(auto &x: b)
    {
        cin>>x;
    }

    bool sum = false, res = false;

    for(int i = 0; i<n; i++)
    {
        if(a[i] != b[i])
        {
            if( a[i] < b[i])
            {
                if(sum == false)
                {
                    cout<<"NO\n";
                    return;
                }
            }
            else
            {
                if(res == false)
                {
                    cout<<"NO\n";
                    return;
                }
            }
        }
    
        if(a[i]==1)
        {
            sum = true;
        }
        else if(a[i] == -1)
        {
            res = true;
        }
    }
    cout<<"YES\n";


}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    lli t; cin>>t;
    while(t--) solve();
    return 0;
}