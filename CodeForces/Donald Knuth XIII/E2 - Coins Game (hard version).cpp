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

    lli new_mask = mask ^ ((1 << (kth-1)));
 
    return ans = 1 + f(new_mask);
}


int main () {
	//fastIO();
    lli n; cin>>n;

    lli num = n*(n+1);
    lli den = 2*2;

    lli gcd = __gcd(num, den);

    cout << num/gcd << "/" << den/gcd << endl;

    //GG oeis

	return 0;
}

