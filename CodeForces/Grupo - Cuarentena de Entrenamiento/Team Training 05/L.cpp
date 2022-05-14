#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

vector< vector< lli > > mat;
lli ans = 0;
lli n, m;

void contar(lli x, lli y)
{
    lli num = mat[x][y];
    bool izq = true, der = true, aba = true, arr = true;
    for(int i = x-1; i>=0; i--)
    {
        if(mat[i][y] >= num)
        {
            //cout << i << " " << y << endl;
            arr = false;
        } 
    }
    for(int i = x+1; i<n; i++)
    {
        if(mat[i][y] >= num) aba = false;
    }
    for(int j = y-1; j>=0; j--)
    {
        if(mat[x][j] >= num) izq = false;
    }
    for(int j = y+1; j<m; j++)
    {
        if(mat[x][j] >= num) der = false;
    }
    ans += aba + arr + izq + der;
    //cerr << ans << endl;
}


int main () {
	//fastIO();
    ifstream cin("lucky.in");
	ofstream cout("lucky.out");
    cin>>n>>m;
    mat.assign(n, vector< lli >(m));
    for(auto &v: mat)
    {
        for(auto &x: v) cin>>x;
    }

    //contar(0,0);

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            contar(i, j);
        }
    }
    cout << ans << endl;

	return 0;
}