#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void main_(){
	vector<lli> nums(3);
    cin>>nums[0]>>nums[1]>>nums[2];

    lli k; cin>>k;

    sort(all(nums));
    nums[2] *= (1LL << k);
    
    cout << nums[0] + nums[1] + nums[2] << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	while(t--) 
		main_();


	return 0;
}

