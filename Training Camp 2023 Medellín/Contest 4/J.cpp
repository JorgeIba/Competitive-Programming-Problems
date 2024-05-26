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
    vector<lli> nums(n);

    for(auto &x: nums) cin>>x;

    lli sum = 0;
    for(auto x: nums) sum += x;

    ld prom = (ld)sum / (n+1);
        
    cout << fixed << setprecision(10);
    cout << 2*prom << " ";
    forn(i, n-1) cout << prom << " ";

    // auto simulate = [&](){
        
    //     vector<ld> oiriginal = nums;
    //     forn(i, n){
    //         ld half = (ld)nums[i]/2;
    //         nums[(i+1)%n] += half;
    //         nums[i] -= half;
    //     }
    // };

    // forn(i, 1000){
    //     cout << i << ": " << endl;
    //     for(auto x: nums) cout << fixed << setprecision(10) << x << " ";
    //     cout << endl;

    //     // cout << i << ": " << endl;
    //     // for(auto x: aux) cout << fixed << setprecision(10) << x << " ";
    //     // cout << endl;

    //     simulate();
    // }



	return 0;
}

