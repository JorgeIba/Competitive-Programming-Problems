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


int main () {
	//fastIO();
    int rows, cols; cin>>rows>>cols;
    vector< vector<int> > matriz(rows, vector<int>(cols));

    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cin>>matriz[i][j];
        }
    }


    vector< vector<int> > prefix_sum(rows, vector<int>(cols));

    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            int izquierda=0, arriba=0, diagonal=0;
            if(i > 0) arriba = prefix_sum[i-1][j];
            if(j > 0) izquierda = prefix_sum[i][j-1];
            if(i > 0 && j > 0) diagonal = prefix_sum[i-1][j-1];

            prefix_sum[i][j] = izquierda + arriba - diagonal + matriz[i][j];
        }
    }

    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << prefix_sum[i][j] << " ";
        }
        cout << endl;
    }


    while(true)
    {
        lli row1, col1; cin>>row1>>col1; //inferior izq
        lli row2, col2; cin>>row2>>col2; //superior der

        cout << prefix_sum[row1][col2] - (col1 > 0? prefix_sum[row1][col1-1] : 0) - (row2 > 0 ? prefix_sum[row2-1][col2] : 0) +
                                        (row2 > 0 && col1 > 0 ? prefix_sum[row2-1][col1-1] : 0) << endl;

    }

	return 0;
}