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
    lli n; cin>>n;
    vector<lli> adj[n+1];
    vector<lli> disrespect(n+1, 0);
    forn(i,1,n+1)
    {
        lli pi, ci; cin>>pi>>ci;
        if(pi!=-1)
        {
            adj[pi].push_back(i);
            disrespect[i] = ci;
        }
        
    }
    bool almenos = false;
    forn(i, 1, n+1)
    {
        bool flag = true;
        if(disrespect[i])
        {
            for(auto x: adj[i])
            {
                if(!disrespect[x])
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                cout<<i<<" ";
                almenos=true;
            } 
        }
    }
    if(!almenos)
    {
        cout<<-1;
    }
    cout<<endl;

    return 0;
}