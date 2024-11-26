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

int query(int u, int v) {
    cout << "? " << u << " " << v << endl;
    cout.flush();
    int x; cin>>x;
    return x;
}

void print_ans(int x) {
    cout << "! " << x << endl;
    cout.flush();
    return;
}

void main_() {
    int n; cin>>n;
    vector<int> cand(n);
    iota(all(cand), 1);

    while(SZ(cand) > 1) {
        auto u = cand.back(); cand.pop_back();
        auto v = cand.back(); cand.pop_back();

        if(query(u, v) != query(v, u)) {
            int other = -1;
            forr(i, 1, n) if(i != u && i != v) {
                other = i;
                break;
            }

            assert(other != -1);

            if(query(u, other) != query(other, u)) {
                print_ans(u);
            } else {
                print_ans(v);
            }
            return;
        }
    }

    if(SZ(cand) == 1) {
        print_ans(cand.back());
        return;
    }
}

int main () {
	// fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

