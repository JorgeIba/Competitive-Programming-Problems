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

vector< vector<int> > mat;
vector<int> sizesShips;
int n, k;

bool inside(lli x, lli y)
{
    if(x >= n || x < 0 || y < 0 || y >= n) return false;
    return true;
}

bool canVertical(lli x, lli y, lli large)
{
    for(int i = 0; i<large; i++)
    {
        if(inside(x+i, y) && mat[x+i][y] == '.') continue;
        else return false;
    }
    return true;
}

bool canHorizontal(lli x, lli y, lli large)
{
    for(int i = 0; i<large; i++)
    {
        if(inside(x, y+i) && mat[x][y+i] == '.') continue;
        else return false;
    }
    return true;
}

bool isValid()
{
    forn(i,n){
		forn(j,n){
			//if(!grid[i][j] && M[i][j] == 'O')
			if(!(grid[i] >> j & 1) && M[i][j] == 'O')
				return false;
			//if(grid[i][j] && M[i][j] == 'X')
			if((grid[i] >> j & 1) && M[i][j] == 'X')
				return false;
		}
	}
	return true;
}

lli fun(lli x, lli y, lli ship)
{
    if(ship == k)
    {
        return isValid();
    }

}


int main () {
	//fastIO();
    cin>>n;
    mat.resize(n);

    forn(i, n) cin>>mat[i];
    cin>>k;
    sizesShips.resize(k);
    forn(i,k) cin>> sizesShips[i];

    cout << fun(0, 0, 0) << endl;
	return 0;
}