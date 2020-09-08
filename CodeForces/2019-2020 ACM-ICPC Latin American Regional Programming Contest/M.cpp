#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main () {
	//fastIO();
    lli n, m; cin>>n>>m;
    vector< lli > nums(n);
    for(auto &x: nums) cin>>x;
    lli ans = 0;
    for(int i = 0; i<n; i++)
    {
        lli last = nums[i], aux = 0;
        for(int j = i; j<n; j++)
        {
            if((nums[j] - last) <= m)
            {
                aux++;
                last = nums[j];
            }
            else break;
        }
        ans = max(ans, aux);
    }
    cout << ans << endl;

	return 0;
}