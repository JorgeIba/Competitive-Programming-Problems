#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

const int MAXN = 1e6 + 100;

const string BRUCE = "Bruce";

int main () {
	//fastIO();

    string first; cin>>first;

    int a, b, c, q; cin>>a>>b>>c>>q;

    vector<int> dp(MAXN, -1);
    auto f = [&](const auto &f, int balloons){
        if(balloons == 0) return 0;

        int &ans = dp[balloons];
        if(ans != -1) return ans;

        bitset<10> states;
        if(balloons >= a){
            int gr_1 = f(f, balloons - a);
            states[gr_1] = 1;
        }
        if(balloons >= b) {
            int gr_2 = f(f, balloons - b);
            states[gr_2] = 1;
        }
        if(balloons >= c) {
            int gr_3 = f(f, balloons - c);
            states[gr_3] = 1;
        }

        int mex = 0;
        while(states[mex]) mex++;
        return ans = mex;
    };

    while(q--){
        int k; cin>>k;
        int ans = 0;
        forn(i, k){
            int x; cin>>x;
            ans ^= f(f, x);
        }

        // debugg(ans);

        if(ans != 0){
            if(first == BRUCE) {
                cout << "Happy Bruce" << endl;
            } else {
                cout << "Sad Arthur" << endl;
            }
        } else {
            if(first == BRUCE) {
                cout << "Sad Arthur" << endl;
            } else {
                cout << "Happy Bruce" << endl;
            }
        }
    }



	return 0;
}

