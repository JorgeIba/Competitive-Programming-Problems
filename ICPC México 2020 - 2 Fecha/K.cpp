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

const int maxN = 105;

void GaussJordan(vector< bitset<maxN> > &equations, vector<int> &ans)
{
	int rows = maxN, cols = maxN;
	for(int i = 0, j = 0; (i < rows) && (j < cols); j++)
	{
		int selected = -1;
		
		for(int k = i; k<rows; k++)
			if(equations[k][j])
				selected = k;
		
		if(selected == -1) continue;
		
		swap(equations[i], equations[selected]);
		swap(ans[i], ans[selected]);

		for(int k = 0; k<rows; k++)
		{
			if(k != i && equations[k][j])
			{
				equations[k] ^= equations[i];
				ans[k] ^= ans[i];
			}
		}
		i++;
	}
}



int main () {
	//fastIO();
	int n, m; cin>>n>>m;
	vector< vector< bool > > adjMatrix(maxN, vector<bool>(maxN));
	for(int i = 0; i<m; i++)
	{
		int u, v; cin>>u>>v; u--, v--;
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 1;
	}

	vector< bitset<maxN> > equations(maxN);
	vector<int> ans(maxN);

	for(int i = 0; i<maxN; i++)
	{
		for(int j = 0; j<maxN; j++)
		{
			if(adjMatrix[i][j])
				equations[i][j] = 1;
		}
		int howMany = equations[i].count();
		if(~howMany & 1 && (howMany > 0))
		{
			ans[i] = 1;
		}
		else
		{
			equations[i][i] = 1;
			ans[i] = 0;
		}
	}
	
	GaussJordan(equations, ans);


	for(int i = 0; i<maxN; i++)
	{
		if((equations[i].count()==0) && ans[i])
		{
			cout << "N" << endl; return 0;
		}
	}
	cout << "Y" << endl;
	
    
	return 0;
}