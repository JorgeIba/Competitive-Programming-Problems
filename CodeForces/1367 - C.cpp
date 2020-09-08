#include <bits/stdc++.h>
//Don't hack me plz :((
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n, k; cin>>n>>k;
    string s; cin>>s;
    vector< lli > canBe(n);
    lli cont = 0;
    for(int i = 0; i<n; i++)
    {
        if(s[i] == '1')
        {
            canBe[i] = -1;
            cont = k;
            continue;
        }
        else
        {
            if(cont <= 0)
            {
                canBe[i] = 1;
            }
            else
            {
                canBe[i] = -1;
            }
            cont--;
        }
    }


    for(int i = n-1; i>=0; i--)
    {
        if(s[i] == '1')
        {
            canBe[i] = -1;
            cont = k;
            continue;
        }
        else
        {
            if(canBe[i] == -1) continue;
            if(cont <= 0)
            {
                canBe[i] = 1;
            }
            else
            {
                canBe[i] = -1;
            }
            cont--;
        }
    }
  
    lli ans = 0;
    for(int i = 0; i<n; i++)
    {
        if(canBe[i] == 1)
        {
            ans++;
            i = i+k;
        }
    }
    cout<<ans<<endl;
}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}