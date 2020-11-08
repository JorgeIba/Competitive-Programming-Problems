#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

vector< string > matrix;
vector< vector<int> > spots;

int n, m, t; 
vector< pair<int,int> > moves = {{1,0}, {-1, 0}, {0, -1}, {0, 1}};

bool isValid(int i, int j)
{
    if(i<0 || j<0 || i>=n || j>=m) return false;
    return true;
}


void markSpots()
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            for(auto move: moves)
            {
                if(isValid(i + move.first, j + move.second) && matrix[i][j] == matrix[i+move.first][j+move.second])
                {
                    spots[i][j] = spots[i+move.first][j+move.second] = 1;
                }
            }
        }
    }
}

vector< vector<int> > distances;

void bfs()
{
    queue<pair<int,int>> q;
    distances.assign(n, vector<int>(m, -1));
    forn(i,n) 
        forn(j, m)
            if(spots[i][j])
            {
                q.push({i,j});
                distances[i][j] = 0;
            }
    
    while(!q.empty())
    {
        auto u = q.front(); q.pop();
        for(auto move: moves)
        {
            pair<int,int> v = {u.first + move.first, u.second + move.second};
            if(isValid(v.first, v.second) && distances[v.first][v.second] == -1)
            {
                q.push(v);
                distances[v.first][v.second] = distances[u.first][u.second] + 1;
            }
        }
    }
}

char change(char a)
{
    if(a == '1') return '0';
    return '1';
}


int main () {
	fastIO();
    cin>>n>>m>>t;
    matrix.resize(n);
    spots.assign(n, vector<int>(m));

    for(int i = 0; i<n; i++)
    {
        cin>>matrix[i];
    }

    markSpots();
    bfs();

    while(t--)
    {
        lli x, y, p; cin>>x>>y>>p;
        assert(p >= 0);
        x--,y--;
        if(distances[x][y] >= p || distances[x][y] == -1) cout << matrix[x][y] << endl;
        else
        {
            p -= distances[x][y];
            if(p&1) cout << change(matrix[x][y]) << endl;
            else cout << matrix[x][y] << endl;
        }
    }
	return 0;
}