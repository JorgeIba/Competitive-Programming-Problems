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

    auto solve_3 = [&](const vector<int> &cand){
        auto [a, b, c] = array<int,3>{cand[0], cand[1], cand[2]};

        if(query(a, b) != query(b, a)) {
            if(query(a, c) != query(c, a)) {
                print_ans(a);
            } else {
                print_ans(b);
            }
        } else {
            print_ans(c);
        }
        return;
    };

    auto solve_4 = [&](const vector<int> &cand) {
        auto [a, b, c, d] = array<int,4>{cand[0], cand[1], cand[2], cand[3]};

        if(query(a, b) != query(b, a)) {
            if(query(a, c) != query(c, a)) {
                print_ans(a);
            } else {
                print_ans(b);
            }
        } else {
            if(query(c, a) != query(a, c)) {
                print_ans(c);
            } else {
                print_ans(d);
            }
        }
        return;
    };

    auto solve_5 = [&](const vector<int> &cand) {
        auto [a, b, c, d, e] = array<int,5>{cand[0], cand[1], cand[2], cand[3], cand[4]};
        int x_1 = query(a, b);
        int x_2 = query(b, c);
        int x_3 = query(c, a);
        if((x_1 ^ x_2 ^ x_3) == 1) {
            if(query(a, d) != query(d, a)) {
                print_ans(d);
            } else {
                print_ans(e);
            }
            return;
        }

        int x_4 = query(b, a);
        int x_5 = query(a, c);

        bool diff_ab = x_1 != x_4;
        bool diff_ac = x_3 != x_5;

        if(diff_ab && diff_ac) {
            print_ans(a);
        } else if(!diff_ab && diff_ac) {
            print_ans(c);
        } else if(diff_ab && !diff_ac) {
            print_ans(b);
        } else {
            assert(false);
        }
        return;
    };


    vector<int> cand(n);
    iota(all(cand), 1);


    if(n == 3) {
        solve_3(cand);
        return;
    }

    while(SZ(cand) > 4) {
        if(SZ(cand) == 5) {
            solve_5(cand);
            return;
        }

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

    assert(SZ(cand) == 4);
    solve_4(cand);
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

