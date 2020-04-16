#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

void solve()
{
    lli n, p; cin>>n>>p;
    vector<lli> nums(n);
    vector<bool> check(n, false);
    for(auto &x: nums)
    {
        cin>>x;
    }
    vector<lli> aux = nums;
    for(lli i = 0; i<p; i++)
    {
        lli x; cin>>x;
        check[x-1] = true;
    }
    
    sort(aux.begin(), aux.end());

    for(int i = 0; i<n; i++)
    {
        if(nums[i] != aux[i])
        {
            lli buscar = -1;
            for(int j = 0; j<n; j++)
            {
                if(aux[j] == nums[i])
                {
                    buscar = j;
                    break;
                }
            }
            if(buscar > i)
            {
                for(int j = i; j<buscar; j++)
                {
                    if(!check[j])
                    {
                        //cout<<i<<" "<<j<<" "<<buscar<<endl;
                        //cout<<"NO\n";
                        return;
                    }
                }
            }
            else if(buscar < i)
            {
                for(int j = i-1; j>=buscar; j--)
                {
                    if(!check[j])
                    {
                        cout<<"NO\n";
                        return;
                    }
                }
            }
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
    while(t--)
    {
        solve();
    }
    return 0;
}