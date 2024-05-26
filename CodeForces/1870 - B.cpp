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
	int n, m; cin>>n>>m;

    vector<int> nums(n), opt(m);
    int all_xor = 0, all_opt = 0;
    for(auto &x: nums){
        cin>>x;
        all_xor = all_xor ^ x;
    }

    for(auto &x: opt){
        cin>>x;
        all_opt = all_opt | x;
    }

    if(n % 2 == 0){
        int mn = 0, mx = all_xor;
        for(auto &x: nums){
            x |= all_opt;
            mn = mn^x;
        }
        cout << mn << " " << mx << endl;
    } else{
        int mn = 0, mx = all_xor;
        for(auto &x: nums){
            x |= all_opt;
            mn = mn^x;
        }
        cout << mx << " " << mn << endl;
    }

}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

