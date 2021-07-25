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


ld brute(vector<lli> nums)
{
    lli n = SZ(nums);
    ld ans = 1.0/n;
    for(int l = 0; l<n; l++)
    {
        for(int r = l+1; r<n; r++)
        {
            set<lli> unique;
            for(int i = l; i<=r; i++)
            {
                unique.insert(nums[i]);
            }
            ans += (2.0/(n*n))*SZ(unique);
        }
    }
    return ans;
}



int main () {
	fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<lli> last(n);
    map<lli,lli> idx_last;

    for(int i = 0; i<n; i++)
    {
        last[i] = idx_last[nums[i]];
        idx_last[nums[i]] = i+1;
    }


    lli sum = 0;

    for(int i = 0; i<n; i++)
    {
        lli izq = i+1 - last[i];
        lli der = (n-i);
        //cerr << izq << "---" << der << "   ";
        lli aparece = izq*der-1;
        //cout << aparece << " ";
        sum += aparece;
    }

    ld ans = (1.0/n) + (2.0/(n*n))*sum;

    cout << fixed << setprecision(10) << ans << endl;
    //cout << fixed << setprecision(10) << ans << " " << brute(nums) << endl;

	return 0;
}

