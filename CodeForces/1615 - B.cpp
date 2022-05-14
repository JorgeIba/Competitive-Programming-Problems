
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


const lli maxN = 2e5+10;
const lli maxK = 20;

lli bits[maxN][maxK];

int main () {
	fastIO();

    for(int i = 1; i< maxN; i++)
    {
        for(int k = 0; k < maxK; k++)
        {
            lli adding = (i & (1LL << k)) != 0;
            bits[i][k] = bits[i-1][k] + adding;
        }
    }





    lli t; cin>>t;
    while(t--)
    {
        lli l, r; cin>>l>>r;
         lli ans = 1e18;



        for(int k = 0; k < maxK; k++)
        {
            lli how_many_in_range = bits[r][k] - bits[l-1][k];
            lli not_having = (r - l + 1) - how_many_in_range;
            ans = min(ans, not_having);
            //cout << "for bit " <<k << " " << how_many_in_range << " " <<  not_having << endl;
        }

        cout << ans << endl;

    }
    

	return 0;
}

