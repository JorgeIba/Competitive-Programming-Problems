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
    lli n, x; cin>>n>>x;

    vector< pair<lli,lli> > ranges(n);

    for(int i = 0; i<n; i++)
    {
        lli s, t; cin>>s>>t;
        ranges[i] = {s, s+t};
    }
	
    const lli INF = 1e9;

    lli ans = INF, time_ans = 0;

    for(lli i = 0; i<=480; i++)
    {

        //cout << i << ":" << endl;
        lli conflict = 0;
        for(auto r: ranges)
        {
            lli D = r.first, T = r.second;

            if(T < i) continue;

            lli k_1 = ceil((ld) (D-i) / x );
            lli k_2 = floor((ld) (T-i) / x);

            k_1 = max(k_1, 0LL);

            conflict += (k_2-k_1+1);

            //cout << D << "-" << T << "  " << k_1 << " " << k_2 << endl;

            
        }
        //cout << "conflicts: " << conflict << endl;
        if(conflict < ans)
        {
            ans = conflict;
            time_ans = i;
        }
    }


    cout << time_ans << " " << ans << endl;
    


	return 0;
}

