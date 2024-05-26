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


lli isPowerofTwo(lli s){ return s & (s-1); }

const int LOG = 50;

void main_(){
    int n; cin>>n;
    vector<lli> nums(n);
    lli sum = 0;
    for(auto &x: nums) {
        cin>>x;
        sum += x;
    }

    if(sum % n != 0) {
        cout << "No" << endl;
        return;
    }

    auto get_needings = [&](lli x) -> pair<lli,lli> {
        for(int i = 0; i < LOG; i++) {
            if(!isPowerofTwo(x + (1LL << i))) {
                return {(1LL << i), x + (1LL << i)};
            }
        }
        return {-1, -1};
    };


    lli K = sum / n;

    map< lli, lli > needing;

    for(auto x: nums){
        if(x > K){
            auto [income, outcome] = get_needings(x - K);

            if(income == -1){
                cout << "No" << endl;
                return;
            }

            needing[outcome]++;
            needing[income]--;

        } else if(x < K){
            auto [outcome, income] = get_needings(K - x);

            if(income == -1){
                cout << "No" << endl;
                return;
            }

            needing[outcome]++;
            needing[income]--;
        }
    }

    for(auto [x, needs]: needing) {
        if(needs > 0 && isPowerofTwo(x)) {
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}