#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


int main () {
	//fastIO();

    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<int> not_learned(n-1);
    for(auto &x: not_learned) cin>>x;

    for(int i = 0; i < n; i++) {
        bool flag = false;
        for(int j = 0; j < n-1; j++) {
            flag |= (nums[i] == not_learned[j]);
        }
        if(!flag) {
            cout << nums[i] << endl;
            break;
        }
    }

	return 0;
}

