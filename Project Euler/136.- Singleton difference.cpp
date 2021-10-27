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

const int maxN = 5e7;

int main () {
	//fastIO();
    time_t begin = clock();

    vector< lli > fr(maxN+5);

    for(int d = 1; d*d<=3*maxN; d++)
    {
        for(int i = 1; i*d <= maxN; i++)
        {
            lli n = i*d;
            lli a = n/d;
            if((a+d)%4 == 0 && d*d < 3*n )
            {
                //lli k = (a+d)/4;
                fr[n]++;
            }
        }
    }
    
    lli ans = count(all(fr), 1);
    cout << ans << endl;

    cout << "Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}

