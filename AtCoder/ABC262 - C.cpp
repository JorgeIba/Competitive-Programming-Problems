#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;



int main () {
	//fastIO();

    int n; cin>>n;

    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];

    lli same_pos = 0;
    lli ans = 0;
    for(int i = 1; i <= n; i++){
        if(nums[i] == i) ans += same_pos;
        else if(nums[i] < i && nums[nums[i]] == i) ans++;

        same_pos += (nums[i] == i);
    }

    cout << ans << endl;


	return 0;
}

