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

lli n, c, t;
vector<int> nums;

bool check(lli mid)
{
    auto aux = nums;
    lli vueltas = 1;
    lli remain = t*mid;

    for(int i = 0; i<n; i++)
    {
        if(t*mid < aux[i]) return false;
        if(remain < aux[i])
        {
            vueltas++;
            remain = t*mid;
        }
        remain -= aux[i];
    }
    //cerr << vueltas << endl;
    return vueltas <= c;
}


int main () {
	fastIO();
    cin>>n>>c>>t;
    nums.resize(n);
    for(auto &x: nums) cin>>x;

    //cout << check(6) << endl;

    
    lli l = 1, r = 1e15, ans = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else
        {
            l = mid + 1;
        }
    }
    
    cout << ans << endl;
    
    
    
	return 0;
}