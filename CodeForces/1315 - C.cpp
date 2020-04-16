#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

void solve()
{
    lli n; cin>>n;
    lli arr[2*n+2];
    memset(arr, 0, sizeof(arr));

    set<lli> numRes;
    for(int i=1; i<=2*n; i++)
    {
        numRes.insert(i);
    }

    for(int i=1; i<2*n; i+=2)
    {
        cin>>arr[i];
        numRes.erase(arr[i]);
    }

    for(int i=2; i<=2*n; i+=2)
    {
        lli num = arr[i-1];
        auto upper = numRes.upper_bound(num);
        arr[i] = *upper;
        if(arr[i] < arr[i-1])
        {
            continue;
        }
        else
        {
            numRes.erase(*upper);
        }
    }

    if(numRes.size() == 0)
    {
        for(int i=1; i<=2*n; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        cout<<-1<<endl;
    }

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
