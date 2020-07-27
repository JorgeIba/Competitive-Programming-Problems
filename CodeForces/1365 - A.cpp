#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n,m; cin>>n>>m;
    vector < vector<bool> > mat(n, vector<bool>(m));
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            lli aux; cin>>aux;
            mat[i][j] = aux;
        }
    }

    lli countM = 0;
    for(int i = 0; i<n; i++)
    {
        bool flag = true;
        for(int j = 0; j<m; j++)
        {
            if(mat[i][j] == 1)
            {
                flag = false;
                break;
            }
        }
        countM+=flag;
    }

    lli countR = 0;
    for(int j = 0; j<m; j++)
    {
        bool flag = true;
        for(int i = 0; i<n; i++)
        {
            if(mat[i][j] == 1)
            {
                flag = false;
                break;
            }
        }
        countR+=flag;
    }

    lli aux = min(countM, countR);
    if(aux&1)
    {
        cout<<"Ashish\n";
    }
    else
    {
        cout<<"Vivek\n";
    }


   


}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}