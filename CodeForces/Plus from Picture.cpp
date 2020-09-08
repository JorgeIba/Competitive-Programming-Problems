#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector<char> > mat;
vector< vector<bool> > check;
lli n, m; 

void dfs(lli i, lli j, lli dx, lli dy)
{
    if(i< 0 || j<0 || j>=m || i>=n) return;
    if(mat[i][j] != '*') return;
    check[i][j] = false;
    dfs(i+dy, j+dx, dx, dy);
}

int main()
{
    fastIO();
    cin>>n>>m;
    mat.resize(n, vector<char> (m));
    check.resize(n, vector<bool> (m));
    forn(i, 0, n)
    {
        forn(j, 0, m)
        {
            cin>>mat[i][j];
            if(mat[i][j] == '*') check[i][j] = true;
        }
    }

    bool flag = false, breaking = false;
    forn(i, 1, n-1)
    {
        forn(j, 1, m-1)
        {
            if(mat[i][j]=='*' and mat[i-1][j] == '*' and mat[i+1][j] == '*' and mat[i][j-1] == '*' and mat[i][j+1]=='*')
            {
                check[i][j] = false;
                dfs(i,j-1, -1, 0);
                dfs(i,j+1, 1, 0);
                dfs(i+1,j, 0, 1);
                dfs(i-1,j, 0, -1);
                flag = true;
                breaking = true;
                break;
            }
        }
        if(breaking) break;
    }

    if(flag)
    {
        forn(i, 0, n)
        {
            forn(j, 0, m)
            {
                if(check[i][j])
                {
                    cout<<"NO\n";
                    return 0;
                }
            }
        }
        cout<<"YES\n";
    }
    else
    {
        cout<<"NO\n";
    }

    return 0;
}