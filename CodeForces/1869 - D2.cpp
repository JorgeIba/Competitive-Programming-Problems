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


bool isPowerofTwo(lli s){ return (s & (s-1)) == 0; }
int MSB(int x) { return 31 - __builtin_clz(x); }

const int LOG = 32;

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
            if(isPowerofTwo(x + (1LL << i))) {
                return {(1LL << i), x + (1LL << i)};
            }
        }
        return {-1, -1};
    };


    lli K = sum / n;

    vector<int> needing(LOG);
    vector< pair<lli,int> > powers;


    for(auto x: nums){

        if(isPowerofTwo(abs(x - K))) {
            if(x > K){
                powers.push_back({x - K, 1});
            } else if( x < K){
                powers.push_back({K - x, -1});
            }
            continue;
        }


        if(x > K){
            auto [income, outcome] = get_needings(x - K);

            if(income == -1){
                cout << "No" << endl;
                return;
            }

            needing[MSB(outcome)]++;
            needing[MSB(income)]--;
        } else if(x < K){
            auto [outcome, income] = get_needings(K - x);

            if(income == -1){
                cout << "No" << endl;
                return;
            }
            needing[MSB(outcome)]++;
            needing[MSB(income)]--;
        }
    }

    sort(all(powers));
    reverse(all(powers));

    for(auto [needs, typee]: powers){
        int x = MSB(needs);
        if(typee == 1){
            if(needing[x+1] < 0){
                needing[x+1]++;
                needing[x]--;
            } else {
                needing[x]++;
            }
        } else {
            if(needing[x+1] > 0){
                needing[x+1]--;
                needing[x]++;
            } else {
                needing[x]--;
            }
        }
    }

    forn(i, LOG){
        if(needing[i]){
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