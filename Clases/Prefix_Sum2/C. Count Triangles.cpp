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


const int maxD = 1e6 + 10;

int main () {
	//fastIO();
    int A, B, C, D; cin>>A>>B>>C>>D;

    //min y = B
    //max y = C

    vector<lli> marquitas(maxD);

    for(int x = A; x<=B; x++)
    {
        marquitas[x+B] += 1;
        marquitas[x+C+1] -= 1;
    }

    vector<lli> fr(maxD);
    int bolita = 0;
    for(int i = 1; i<maxD; i++)
    {
        bolita += marquitas[i];
        fr[i] = bolita;
    }


    vector<lli> suffix_sum(maxD);
    for(int i = maxD-1; i>=1; i--)
    {
        suffix_sum[i] = suffix_sum[i+1] + fr[i];
    }

    lli ans = 0;
    for(int z = C; z<=D; z++)
    {
        ans += suffix_sum[z+1];
    }

    cout << ans << endl;

	return 0;
}