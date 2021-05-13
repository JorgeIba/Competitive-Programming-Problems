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


const int maxP = 100 + 10;
const int maxT = 10 + 5;

int plano[maxP][maxP][maxT]; //plano[i][j][t] = brillo en tiempo t en la coordenada i, j
int prefix_sum[maxP][maxP][maxT]; 
bool theres_star[maxP][maxP];

int main () {
	fastIO();
    lli n, q, c; cin>>n>>q>>c;

    for(int i = 0; i<n; i++)
    {
        int x, y, s; cin>>x>>y>>s;
        plano[x][y][0] = s;
        theres_star[x][y] = 1;
    }

    for(int i = 1; i<maxP; i++)
    {
        for(int j = 1; j<maxP; j++)
        {
            for(int t = 1; t<maxT; t++)
            {
                if(theres_star[i][j])
                    plano[i][j][t] = (plano[i][j][t-1] + 1) % (c+1);
            }
        }
    }

    /*
    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
        {
            cout << plano[i][j][0] << " ";
        }
        cout << endl;
    }

    cout << "//////////////////////////" << endl;

    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
        {
            cout << plano[i][j][2] << " ";
        }
        cout << endl;
    }
    */



    for(int t = 0; t<maxT; t++)
    {
        for(int i = 1; i<maxP; i++)
        {
            for(int j = 1; j <maxP; j++)
            {
                prefix_sum[i][j][t] = prefix_sum[i][j-1][t]  + prefix_sum[i-1][j][t] - prefix_sum[i-1][j-1][t] + plano[i][j][t];
            }
        }
    }

    while(q--)
    {
        int t, x1, y1, x2, y2; cin>>t>>x1>>y1>>x2>>y2;

        //(x1, y1) izq superior
        //(x2, y2) der inferior

        int real_time = t % (c+1);
        cout << prefix_sum[x2][y2][real_time] - prefix_sum[x1-1][y2][real_time] - prefix_sum[x2][y1-1][real_time] + prefix_sum[x1-1][y1-1][real_time] << endl;
    }

    

	return 0;
}