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

const int MAXT = 1e6+1;
const int MAXSUM = 30+1;
int unluck[MAXT + 1];

void prec() {
    auto get_unluck = [&](int x) {
        int right = (x % 10 + (x / 10) % 10 + (x / 100) % 10);
        int left = ((x / 1000) % 10 + (x / 10000) % 10 + (x / 100000) % 10);
        return abs(left - right);
    };

    forn(i, MAXT) {
        unluck[i] = get_unluck(i);
    }
}


int bit[MAXSUM+1];

void update(int x, int pos) {
    for(pos++; pos < MAXSUM; pos += pos & (-pos))
        bit[pos] += x;
}

int query(int pos) {
    int ans = 0;
    for(pos++; pos > 0; pos -= pos & (-pos))
        ans += bit[pos];
    return ans;
}



vector<int> queries[MAXT+1];
int main () {
	// fastIO();
    prec();

    int n; cin>>n;

    forn(i, n) {
        string s; cin>>s;
        int x = stoll(s);
        queries[x].push_back(i);
    }

    vector<int> ans(n);
    for(int i = 0; i < MAXT; i++) {
        for(auto v: queries[i]) {
            ans[v] = query(unluck[i] - 1);
        }

        update(1, unluck[i]);
    }


    for(auto x: ans) cout << x << endl;
    cout << endl;


	return 0;
}

