#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< string > mat;
lli n, m; 
vector< vector<bool> > visited;
vector< vector<bool> > canI;

void block(lli i, lli j)
{
    if(i>0 && mat[i-1][j] == '.') mat[i-1][j] = '#';
    if(i<n-1 && mat[i+1][j] == '.') mat[i+1][j] = '#';
    if(j>0 && mat[i][j-1] == '.') mat[i][j-1] = '#';
    if(j<m-1 && mat[i][j+1] == '.') mat[i][j+1] = '#';
}

vector< pair<lli,lli> > dir = { {0,1}, {0,-1}, {1,0}, {-1,0}  };

bool isValid(lli i, lli j)
{
    if(i<0 || i>=n || j<0 || j>=m || mat[i][j]=='#') return false;
    return true;
}
bool flag;

lli dfs(lli i, lli j)
{
    if(mat[i][j] == 'B')
    {
        flag = false;
        return 0;
    }
    visited[i][j] = true;
    lli ans = (mat[i][j] == 'G');
    for(auto p: dir)
    {
        lli dx = p.first, dy = p.second;
        if(isValid(i+dx,j+dy) && !visited[i+dx][j+dy])
        {
            ans += dfs(i+dx,j+dy);
        }
    }
    return ans;
}




void solve()
{
    cin>>n>>m;
    mat.clear(); mat.resize(n); 
    visited.clear(); visited.assign(n, vector<bool>(m));
    canI.clear(); canI.assign(n, vector<bool>(m));
    flag = true;
    lli countG = 0, countB = 0;
    for(int i = 0; i<n; i++)
    {
        cin>>mat[i];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            if(mat[i][j] == 'B')
            {
                countB++;
                block(i,j);
            }
            else if(mat[i][j] == 'G')
            {
                countG++;
            }
        }
    }

    lli ans = dfs(n-1,m-1);
    if( countG == 0  || (countG == ans && flag))
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
    

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