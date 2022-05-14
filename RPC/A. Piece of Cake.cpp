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


typedef pair<ld,ld> point;

#define x first
#define y second


ld cross(point a, point b) {
    return a.x*b.y - a.y*b.x;
}

const lli maxN = 2500;
//15
ld nCr[maxN+5][maxN+5];
void prec()
{
    nCr[0][0] = 1;
    for(int i = 1; i<=maxN; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            if(j==0 || j == i) nCr[i][j] = 1;
            else{
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]);
            }
        }
    }
}


void printPoint(point a) {
    cerr << " [" << a.x << ", " << a.y << "]";
}


int main () {
	//fastIO();

    prec();
    lli n, k; cin>>n>>k;

    vector<point> points(n);
    for(auto &a: points) cin>>a.x>>a.y;

    reverse(all(points));


    ld E = 0;
    for(int i = 0; i < n; i++) {
        int total_left = n - 1;
        // cerr << "Para " << i << " tenemos " << total_left << endl;
        
        for(int j = 0, rem = total_left; rem >= 1; j++, rem--) {
            int how_many_left = (n-j-2);
            ld prob = nCr[how_many_left][k-2] / nCr[n][k];
            ld cross_result = cross(points[i], points[(i+j+1)%n]);
            E += cross_result * prob;
            // cerr << "El cross de "; printPoint(points[i]); cerr << " con "; printPoint(points[(i+j+1)%n]); cerr << " aparece: " << nCr[how_many_left][k-2] << " con prob " << prob << endl;
            // cerr << "Cuando tengo a " << i << " y a " << j << " tengo a la izq " << how_many_left << endl;
        }
    }

    cout << fixed << setprecision(10) << E/2 << endl;

	return 0;
}

