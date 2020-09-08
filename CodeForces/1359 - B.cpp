#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n, m, x, y; cin>>n>>m>>x>>y;
    vector< string > mat(n);
    forn(i,0,n)
        cin>>mat[i];

    lli price = 0;
    if(2*x <= y)
    {
        forn(i,0,n)
        {
            forn(j,0,m)
            {
                if(mat[i][j] == '.')
                    price += x;
            }
        }
    } 
    else
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<m; j++)
            {
                if(mat[i][j] == '.')
                {
                    if(j + 1 < m && mat[i][j+1] == '.')
                    {
                        price += y;
                        j++;
                    }
                    else
                    {
                        price+=x;
                    }
                }
            }
        }
    }
    cout<<price<<endl;
}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}