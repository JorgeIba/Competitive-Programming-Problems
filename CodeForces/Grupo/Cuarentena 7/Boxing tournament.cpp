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
    //fastIO();
    lli n; cin>>n;
    vector< vector<double> > mat(n, vector<double>(n));
    forn(i, 0, n)
    {
        forn(j,0,n)
        {
            cin>>mat[i][j];
        }
    }

    forn(i, 0, n)
    {
        double prob = 1;
        forn(j,0,n)
        {
            if(i!=j)
            {
                prob = mat[i][j] * prob;
            }
        }
        cout<<prob<<" ";
    }

    return 0;
}