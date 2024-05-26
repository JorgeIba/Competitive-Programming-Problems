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


void main_(){

    int n; cin>>n;
    vector<int> nums(n+1);

    forr(i, 1, n) cin>>nums[i];


    vector<int> prefix(n+2), suffix(n+2);
    for(int i = n-1; i >= 1; i--){
        suffix[i] = suffix[i+1];
        suffix[i] += (nums[i] >= nums[i+1]);
    }

    vector<int> prefix_decrease(n+2);
    vector<int> decrease(n+2), taking(n+2, 1);

    for(int i = 1; i <= n-1;){
        if(nums[i] > nums[i+1]) {
            int j = i;
            decrease[i+1] = 1;

            while(j <= n-1 && nums[j] > nums[j+1]) {
                taking[j] = taking[j+1] = -1;
                j++;
            }

            i = j;
        } else {
            i++;
        }
    }

    for(int i = 1; i <= n; i++) prefix_decrease[i] = prefix_decrease[i-1] + decrease[i];
    for(int i = 1; i <= n; i++) prefix[i] = prefix[i-1] + (taking[i] == 1);
 

    int ans = n;
    for(int i = 1; i <= n; i++){
        // cout << i << " --> " << prefix[i] << " -- " << suffix[i] << " -- " << prefix_decrease[i] << endl;
        // debugg(i-1);
        ans = min(ans, prefix[i-1] + suffix[i] + prefix_decrease[i]);
    }

    cout << ans << endl;


}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

