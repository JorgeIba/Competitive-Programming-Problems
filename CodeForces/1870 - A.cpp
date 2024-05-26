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
	int n, k, x; cin>>n>>k>>x;

    if(!(n >= k && x >= k-1)) {
        cout << -1 << endl;
        return;
    }


    vector<int> nums(n);
    iota(all(nums), 0);
    
    int last = (x == k ? x-1 : x);
    for(int j = k; j < n; j++) {
        nums[j] = last;
    }

    int sum = 0;
    for(auto x: nums) {
        sum += x;
    }

    cout << sum << endl;
}



int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

