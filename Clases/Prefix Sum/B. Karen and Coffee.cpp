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


const int maxN = 2e5 + 10;


int main () {
	fastIO();
    int n, k, q; cin>>n>>k>>q;
    vector<lli> marquitas(maxN);

    for(int i = 0; i<n; i++)
    {
        int l, r; cin>>l>>r;
        marquitas[l] += 1;
        marquitas[r+1] -= 1;
    }

    vector<lli> cuantos_recomiendan(maxN);

    int bolita = 0;

    for(int i = 0; i<maxN; i++)
    {
        cuantos_recomiendan[i] = bolita + marquitas[i];
        bolita += marquitas[i];
    }

    /*
    for(int i = 90; i<=100; i++) cout << marquitas[i] << " ";
    cout << endl;

    for(int i = 90; i<=100; i++) cout << cuantos_recomiendan[i] << " ";
    cout << endl;
    */
    
    vector<lli> cumplen(maxN);
    for(int i = 0; i<maxN; i++)
    {
        cumplen[i] = (cuantos_recomiendan[i] >= k? 1 : 0);
    }

    vector<lli> prefix_sum(maxN);
    for(int i = 0; i<maxN; i++)
    {
        prefix_sum[i] = (i>0? prefix_sum[i-1] : 0) + cumplen[i];
    }

    while(q--)
    {
        int l, r; cin>>l>>r;
        cout << prefix_sum[r] - prefix_sum[l-1] << endl;
    }



	return 0;
}