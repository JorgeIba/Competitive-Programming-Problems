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
    vector< int > nums(n-1);

    for(auto &x: nums) cin>>x;

    vector<int> fr(n+1);
    for(auto x: nums) fr[x]++;

    set<int> A;
    forr(i, 1, n) if(!fr[i]) {
        A.insert(i);
    }

    cout << nums[0] << endl;
    for(int i = SZ(nums)-1; i >= 0; i--) {
        int x = nums[i];
        int lowest = *A.begin(); A.erase(lowest);

        cout << x << " " << lowest << endl;

        fr[x]--;
        if(!fr[x]) A.insert(x);
    }

	return 0;
}

