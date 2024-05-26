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

    vector<int> h(3), w(3);

    for(auto &x: h) cin>>x;
    for(auto &x: w) cin>>x;

    lli ans = 0;
    for(int a = 1; a <= 30; a++) {
        for(int b = 1; b <= 30; b++) {
            for(int c = 1; c <= 30; c++) {
                for(int d = 1; d <= 30; d++) {
                    int x1 = w[1] - a - c;
                    int x2 = w[2] - b - d;

                    int y1 = h[1] - a - b;
                    int y2 = h[2] - c - d;


                    int z = h[0] - x1 - x2;

                    if(x1 > 0 && x2 > 0 && y1 > 0 && y2 > 0 && z > 0)
                    {
                        if(
                            z + x1 + x2 == h[0] && 
                            y1 + a + b  == h[1] && 
                            y2 + c + d  == h[2] &&

                            z + y1 + y2 == w[0] &&
                            x1 + a + c  == w[1] &&
                            x2 + b + d  == w[2] 
                        ) ans++;
                    }
                }
            }
        }
    }
	
    cout << ans << endl;

	return 0;
}

