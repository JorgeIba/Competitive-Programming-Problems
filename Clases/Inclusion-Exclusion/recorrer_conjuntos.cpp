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
    vector<lli> nums = {1, 2, 3, 4, 5};
    lli n = SZ(nums);
    for(lli mask = 0; mask < (1<<n); mask++)
    {
        vector<lli> subconjunto;
        for(lli j = 0; j<n; j++)
        {
            if( mask & (1<<j)  )
            {
                subconjunto.push_back(nums[j]);
            }
        }
        for(auto elemento: subconjunto) cout << elemento << " ";
        cout << endl;
    }

	return 0;
}