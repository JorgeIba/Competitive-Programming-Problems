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
	fastIO();

    const lli N = 1e6;
    lli best_num = 0, best_den = 1;
    for(int i = 1; i <= N; i++)
    {
        lli l = 1, r = N, ans = 0;
        while(l <= r)
        {
            lli mid = (l+r)/2;
            if(7*mid < 3*i){
                ans = mid;
                l = mid+1;
            } else r = mid-1;
        }

        if( ans*best_den >= best_num * i){
            best_num = ans, best_den = i;
        }
    }

    cout << best_num << " " << best_den << endl;


	return 0;
}

