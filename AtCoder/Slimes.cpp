#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = numeric_limits<lli>::max();

int main()
{
    fastIO();
    lli n; cin>>n;
    vector<lli> slimes(n);
    for(auto &x: slimes)
    {
        cin>>x;
    }
    vector<lli> prefix(n);
    prefix[0] = slimes[0];
    forn(i, 1, n)
    {
        prefix[i] = prefix[i-1] + slimes[i];
        //cout<<prefix[i]<<" ";
    }

    vector< vector<lli> > dp(n, vector<lli>(n, INF));
    for(int L = n-1; L>=0; L--)
    {
        for(int R = L; R<n; R++)
        {
            if(L==R) //Unico elemento
            {
                dp[L][R] = 0;
                continue;
            }
            lli suma = prefix[R] - (L<=0?0: prefix[L-1]);
            //cout<<suma<<endl;
            for(int pivot = L; pivot<R; pivot++)
            {
                dp[L][R] = min(dp[L][R], dp[L][pivot] + dp[pivot+1][R] + suma);
            }
        }
    }
    cout<<dp[0][n-1]<<endl;


    return 0;
}