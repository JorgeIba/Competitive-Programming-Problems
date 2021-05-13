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

lli _lcm(lli a, lli b)
{
    return (a / __gcd(a,b) ) * b;
}


int main () {
	//fastIO();

    lli n, m;
    
    while(cin>>n>>m)
    {
        vector<lli> nums(m);
        
        for(auto &x: nums) cin>>x;

        lli chivas = 0;
        for(lli mask = 1; mask < (1<<m); mask++)
        {
            lli lcm = 1; 
            for(lli j = 0; j<m; j++)
            {
                if(mask & (1<<j))
                {
                    lcm = _lcm(lcm, nums[j]);
                }
            }
            lli sz_sub = n / lcm;
            if(__builtin_popcountl(mask) % 2 == 1) //Cuenta cuantos bits
            {
                chivas += sz_sub;
            }
            else
            {
                chivas -= sz_sub;
            }
        }
        cout << n - chivas << endl;
    }
    

	return 0;
}