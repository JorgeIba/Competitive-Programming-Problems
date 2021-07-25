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


vector< string > mat;
int n, m; 

const int maxN = 1e3+20;

bool visited[maxN][maxN][4][4];
/*
    0 -> der
    1 -> arr
    2 -> izq
    3 -> aba
*/

vector< pair<int,int> > dir = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };


int i_start, j_start, i_end, j_end;

bool is_possible(int i, int j)
{
    if(i < 0 || j < 0 || i >= n || j >= m || mat[i][j] == '*') return false;
    return true;
}


int opposite(int dir_idx)
{
    switch(dir_idx)
    {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 0;
        case 3:
            return 1;
        default:
            assert(false);
    }
    return 0;
}


void fun(int i, int j, int dir_idx, int turns)
{
    if(turns > 2) return;
    if(i == i_start && j == j_start)
    {
        cout << "YES\n";
        exit(0);
    } 

    //if(visited[i][j][dir_idx][turns]) return;

    for(int k = 0; k < 4; k++)
    {
        if(opposite(dir_idx) == k) continue;

        int dx = dir[k].first, dy = dir[k].second;
        
        if(is_possible(i+dx, j+dy))
            fun(i + dx, j + dy, k, turns + (k != dir_idx));
    }
    //visited[i][j][dir_idx][turns] = true;
}




int main () {
	//fastIO();

    cin>>n>>m;
    mat.resize(n);
    for(int i = 0; i<n; i++) cin>>mat[i];

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            if(mat[i][j] == 'T')
            {
                tie(i_end, j_end) = {i, j};
            }
            else if(mat[i][j] == 'S')
            {
                tie(i_start, j_start) = {i, j};
            }
        }
    }
    
    for(int i = 0; i<4; i++) fun(i_end, j_end, i, 0);
    
    cout << "NO\n";
    
    //cout << ans << endl;

	return 0;
}

