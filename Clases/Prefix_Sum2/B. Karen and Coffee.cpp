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


const int maxT = 2e5 + 10;

int main () {
	fastIO();
    int n, k, q; cin>>n>>k>>q;

    vector<lli> marquitas(maxT);

    for(int i = 0; i<n; i++)
    {
        int l, r; cin>>l>>r;
        marquitas[l] += 1;
        marquitas[r+1] -= 1;
    }

    vector<lli> cuantos_recomiendan(maxT);
    lli bolita = 0;

    for(int i = 1; i<maxT; i++)
    {
        bolita += marquitas[i];
        cuantos_recomiendan[i] = bolita;
    }

    vector<lli> cumplen(maxT);

    for(int i = 1; i<maxT; i++)
    {
        cumplen[i] = (cuantos_recomiendan[i] >= k? 1 : 0);
    }

    vector<lli> prefix_sum(maxT);
    for(int i = 1; i<maxT; i++)
    {
        prefix_sum[i] = prefix_sum[i-1] + cumplen[i];
    }

    while(q--)
    {
        int l, r; cin>>l>>r;
        cout << prefix_sum[r] - prefix_sum[l-1] << endl;
    }


	return 0;
}