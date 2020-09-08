#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
vector< vector< lli > > board;
lli n, m, x, y; 
lli cont = 1;

bool isInside(lli x, lli y)
{
    if(x >= 1 && y>=1 && x<=n && y<=m) return true;
    else return false;
}

void dfs1(lli x, lli y, lli dy)
{
    if(x > n) return;
    if(board[x][y] == 0) board[x][y] = cont++;
    if(!isInside(x, y + dy))
    {
        if(dy == 1) // derecha
        {
            dfs1(x+1, y, -1);
        }
        else
        {
            dfs1(x + 1, y, 1);
        }
    }
    else
    {
        dfs1(x, y+dy, dy);
    }
    
}

void printMat()
{
    for(int i = 1; i<=n; i++)
    {
        for(int j = 1; j<=m; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main () 
{
	//fastIO();
    cin>>n>>m>>x>>y;
    x, y;
    board.assign(n+1, vector<lli> (m+1));

    for(int i = x; i>=1; i--)
    {
        if(board[i][y] == 0) board[i][y] = cont++;
    }
    for(int i = y; i>=1; i--)
    {
        if(board[1][i] == 0) board[1][i] = cont++;
    }
    dfs1(1, 1, 1);
    //printMat();

    vector< pair< lli, pair< lli ,lli > > > ans;
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=m; j++)
        {
            ans.push_back({board[i][j], {i, j}});
        }
    sort(all(ans));
    for(auto x: ans)
    {
        cout << x.second.first << " " << x.second.second << endl;
    }
	return 0;
}