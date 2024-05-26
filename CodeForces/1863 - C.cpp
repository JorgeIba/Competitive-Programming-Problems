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
    int k; cin>>k;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<int> frq(n+1);
    for(auto x: nums) frq[x]++;

    int left = 0;
    while(frq[left]) left++;

    nums.push_back(left);

    int idx_start = 1LL * k * n % (n+1);

    for(int i = 0, j = idx_start; i < n; i++, j = (j+1)%(n+1)){
        cout << nums[j] << " ";
    }
    cout << endl;

}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

