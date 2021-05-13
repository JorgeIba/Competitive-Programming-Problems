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

const int maxN = 1e6 + 10;

int main () {
	//fastIO();
    lli A, B, C, D; cin>>A>>B>>C>>D;

    vector<int> marquitas(maxN);

    for(int i = A; i<=B; i++)
    {
        marquitas[i+B] += 1;
        marquitas[i+C+1] -= 1;
    }

    vector<lli> fr(maxN);
    int bolita = 0;
    for(int i = 1; i<maxN; i++)
    {
        fr[i] = bolita + marquitas[i];
        bolita += marquitas[i];
    }

    vector<lli> suffix_sum(maxN);
    for(int i = maxN-1; i>=1; i--)
    {
        suffix_sum[i] += suffix_sum[i+1] + fr[i];
    }

    lli ans = 0;
    for(int i = C; i<=D; i++) ans += suffix_sum[i+1];

    cout << ans << endl;



	return 0;
}