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
	//fastIO();
    lli n, A, B; cin>>n>>A>>B;
    vector<ld> dp(n+2);    
    ld L = B-A+1;
    ld acum = 0;

    ld mult = 1;
    if(A == 0)
    {
        mult = (ld) L / (L-1); A = 1;
    } 

    for(int l = -B, r = -A, i = 1 ; i<=n; i++)
    {
        while(r < i-A)
        {
            r++;
            acum += (r>=0? dp[r]: 0);
        }
        while(l < i-B)
        {
            acum -= (l>=0? dp[l]: 0);
            l++;
        }
        dp[i] = (ld)mult*(1.0 + (ld)(acum/L)); 
        //cout << i << " " << l << " " << r << endl;
    }
    cout << fixed << setprecision(10) <<  dp[n] << endl;    

	return 0;
}