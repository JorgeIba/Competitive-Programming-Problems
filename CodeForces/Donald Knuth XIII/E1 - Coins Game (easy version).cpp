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



const lli maxN = 20;
lli dp[ (1 << maxN) + 10];


lli f(lli mask)
{
    if(mask == 0) return 0;


    lli &ans = dp[mask];
    if(ans != -1) return ans;
    ans = 0;

    lli kth = __builtin_popcount(mask);

    //bitset<3> aux = mask;
    //bitset<3> cambiar = (1 << (kth-1));
    //cout << aux.to_string() << " " <<  mask << " " << kth-1 << " " << cambiar.to_string() << " " ;

    //cout << mask << " " << !(1 << (kth-1)) << endl;

    lli new_mask = mask ^ ((1 << (kth-1)));
    //bitset<3> cambiado = new_mask;
    //cout << cambiado.to_string() << endl;

    
    return ans = 1 + f(new_mask);
}


int main () {
	//fastIO();
    int n; cin>>n;
	
    memset(dp, -1, sizeof(dp));

    lli ans = 0;
    for(int i = 0; i<(1<<n); i++)
    {
        //cout << i << endl;
        ans += f(i);
    }

    //cout << ans << endl;

    lli den = (1<<n);
    lli gcd = __gcd(ans, den);

    cout << ans/gcd << "/" << den/gcd << endl;


	return 0;
}

