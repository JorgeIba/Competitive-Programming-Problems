#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n, m, k; cin>>n>>m>>k;
    lli cuant=0;
    bool maximo = false;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
        if(x>m)
        {
            cuant++;
        }
        if(x==m) maximo = true;
    }

    if(k==0)
    {
        if(cuant == 0 && maximo)
        {
            cout<<"YES\n";
            return 0;
        }
        cout<<"NO\n";
        return 0;
    }

    if(cuant > k)
    {
        cout<<"NO\n";
    }
    else
    {
        cout<<"YES\n";
    }
    
    
    

    return 0;
}