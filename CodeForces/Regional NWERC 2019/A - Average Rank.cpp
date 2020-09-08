#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;
const int maxN = 1e6 + 100;

lli points[maxN], ranking[maxN], prefix_sum[maxN], last[maxN], prev_sum[maxN], sum[maxN];


int main () {
	//fastIO();
    lli n, w; cin>>n>>w;
    
    for(int i = 0; i<maxN; i++) ranking[i] = 1;

    for(int i = 0; i< w; i++)
    {
        int k; cin>>k;
        for(int j = 0; j<k; j++)
        {
            lli x; cin>>x;
            lli &p = points[x];

            prefix_sum[p] += (i - last[p])*ranking[p];
            last[p] = i;
            sum[x] += prefix_sum[p] - prev_sum[x];

            ranking[p]++;

            p++;
            prefix_sum[p] += (i-last[p])*ranking[p];
            last[p] = i;
            prev_sum[x] = prefix_sum[p];
        }
    }

    for(int i = 1; i<=n; i++)
    {
        lli &p = points[i];
        prefix_sum[p] += ((w) - last[p])*ranking[p];
        last[p] = w;
        sum[i] += prefix_sum[p] - prev_sum[i];
        //cerr << sum[i] << endl;
    }

    cout<<fixed<<setprecision(10);
    for(int i = 1; i<=n; i++) cout << ((ld)sum[i])/w << "\n";

	
	return 0;
}